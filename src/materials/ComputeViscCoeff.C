#include "ComputeViscCoeff.h"

template<>
InputParameters validParams<ComputeViscCoeff>()
{
  InputParameters params = validParams<Material>();
    params.addParam<std::string>("viscosity_name", "FIRST_ORDER", "Name of the viscosity definition to use: set to LAPIDUS by default.");
    params.addCoupledVar("PBVisc", "Pressure-based variable.");
    params.addParam<bool>("isJumpOn", true, "Is jump on?.");
    params.addRequiredCoupledVar("velocity_x", "x component of the velocity");
    params.addCoupledVar("velocity_y", "y component of the velocity");
    params.addCoupledVar("velocity_z", "z component of the velocity");
    params.addRequiredCoupledVar("pressure", "pressure of the fluid");
    params.addRequiredCoupledVar("density", "density of the fluid: rho");
    params.addRequiredCoupledVar("norm_velocity", "norm of the velocity vector");
    params.addCoupledVar("jump_grad_press", "jump of pressure gradient");
    params.addCoupledVar("jump_grad_dens", "jump of density gradient");
    params.addCoupledVar("jump_grad_area", "jump of cross-section gradient");
    params.addCoupledVar("area", "cross-section");
    // Wall heat tranfer
    params.addParam<std::string>("Hw_fn_name", "Function name for the wall heat transfer.");
    params.addParam<std::string>("Tw_fn_name", "Function name for the wall temperature.");
    params.addParam<Real>("Hw", 0., "Wall heat transfer.");
    params.addParam<Real>("Tw", 0., "Wall temperature.");
    params.addParam<Real>("aw", 0., "Wall heat surface.");
    // Cconstant parameter:
    params.addParam<double>("Ce", 1., "Coefficient for viscosity");
    params.addParam<double>("Cjump_press", 1., "Coefficient for pressure");
    params.addParam<double>("Cjump_density", "Coefficient for density jump");
    // Userobject:
    params.addRequiredParam<UserObjectName>("eos", "Equation of state");
    // PPS names:
    params.addParam<std::string>("rhov2_PPS_name", "name of the pps computing rho*vel*vel");
    params.addParam<std::string>("rhocv_PPS_name", "name of the pps computing rho*c*vel");
    params.addParam<std::string>("rhoc2_PPS_name", "name of the pps computing rho*c*c");
    params.addParam<std::string>("press_PPS_name", "name of the pps computing pressure");
    return params;
}

ComputeViscCoeff::ComputeViscCoeff(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    // Declare viscosity types
    _visc_name(getParam<std::string>("viscosity_name")),
    _visc_type("LAPIDUS, FIRST_ORDER, FIRST_ORDER_MACH, ENTROPY, PRESSURE_BASED, INVALID", "INVALID"),
    // Pressure-based variables:
    _PBVisc(isCoupled("PBVisc") ? coupledValue("PBVisc") : _zero),
    _isJumpOn(getParam<bool>("isJumpOn")),
    // Declare aux variables: velocity
    _vel_x(coupledValue("velocity_x")),
    _vel_y(_mesh.dimension()>=2 ? coupledValue("velocity_y") : _zero),
    _vel_z(_mesh.dimension()==3 ? coupledValue("velocity_z") : _zero),
    _grad_vel_x(coupledGradient("velocity_x")),
    _grad_vel_y(_mesh.dimension()>=2 ? coupledGradient("velocity_y") : _grad_zero),
    _grad_vel_z(_mesh.dimension()==3 ? coupledGradient("velocity_z") : _grad_zero),
    // Pressure:
    _pressure(coupledValue("pressure")),
    _pressure_old(coupledValueOld("pressure")),
    _pressure_older(coupledValueOlder("pressure")),
    _grad_press(coupledGradient("pressure")),
    // Density:
    _rho(coupledValue("density")),
    _rho_old(coupledValueOld("density")),
    _rho_older(coupledValueOlder("density")),
    _grad_rho(coupledGradient("density")),
    // Norm of velocity vector:
    _norm_vel(coupledValue("norm_velocity")),
    _grad_norm_vel(coupledGradient("norm_velocity")),
    // Jump of pressure and density gradients:
    _jump_grad_press(isCoupled("jump_grad_press") ? coupledValue("jump_grad_press") : _zero),
    _jump_grad_dens(isCoupled("jump_grad_dens") ? coupledValue("jump_grad_dens") : _zero),
    _area(isCoupled("area") ? coupledValue("area") : _zero),
    // Declare material properties
    _mu(declareProperty<Real>("mu")),
    _mu_max(declareProperty<Real>("mu_max")),
    _kappa(declareProperty<Real>("kappa")),
    _kappa_max(declareProperty<Real>("kappa_max")),
    _l(declareProperty<RealVectorValue>("l_unit_vector")),
//    _residual(declareProperty<Real>("residual")),
    // Wall heat transfer
    _Hw_fn_name(isParamValid("Hw_fn_name") ? getParam<std::string>("Hw_fn_name") : std::string(" ")),
    _Tw_fn_name(isParamValid("Tw_fn_name") ? getParam<std::string>("Tw_fn_name") : std::string(" ")),
    _Hw(getParam<Real>("Hw")),
    _Tw(getParam<Real>("Tw")),
    _aw(getParam<Real>("aw")),
    // Get parameter Ce
    _Ce(getParam<double>("Ce")),
    _Cjump_press(getParam<double>("Cjump_press")),
    _Cjump_rho(getParam<double>(isParamValid("Cjump_density") ? "Cjump_density" : "Cjump_press")),
    // UserObject:
    _eos(getUserObject<EquationOfState>("eos")),
    // PPS name:
    _rhov2_pps_name(getParam<std::string>("rhov2_PPS_name")),
    _rhocv_pps_name(getParam<std::string>("rhocv_PPS_name")),
    _rhoc2_pps_name(getParam<std::string>("rhoc2_PPS_name")),
    _press_pps_name(getParam<std::string>("press_PPS_name"))
{
    _visc_type = _visc_name;
    if (_Ce < 0.)
        mooseError("The coefficient Ce has to be positive and cannot be larger than 2.");
    if (isCoupled("PBVisc")==false && _visc_type==PRESSURE_BASED) {
        mooseError("The pressure-based option cannot be run without coupling the PBVisc variable.");
    }
}

void
ComputeViscCoeff::computeQpProperties()
{
    // Determine h (length used in definition of first and second order viscosities):
    Real _h = _current_elem->hmin() / _qrule->get_order();
    
    // Compute first order viscosity:
    Real c = std::sqrt(_eos.c2_from_p_rho(_rho[_qp], _pressure[_qp]));
    _mu_max[_qp] = 0.5*_h*_norm_vel[_qp];
    _kappa_max[_qp] = 0.5*_h*(_norm_vel[_qp] + c);
    
    // Epsilon value normalization of unit vectors:
    Real eps = std::sqrt(std::numeric_limits<Real>::min());
    
    // Compute Mach number and velocity variable to use in the noramlization parameter:
    Real Mach = std::min(1., _norm_vel[_qp] / c);
    Real rhov2_pps = std::max(getPostprocessorValueByName(_rhov2_pps_name), eps);// : _norm_vel[_qp];
    Real rhocv_pps = std::max(getPostprocessorValueByName(_rhocv_pps_name), eps);// : _norm_vel[_qp];
    Real rhoc2_pps = std::max(getPostprocessorValueByName(_rhoc2_pps_name), eps);// : _rho[_qp]*_c*_c;
    Real press_pps = std::max(getPostprocessorValueByName(_press_pps_name), eps);
    
    // Initialyze some vector, value, ..., used for LAPIDUS viscosity:
    _l[_qp](0)=_grad_norm_vel[_qp](0)/(_grad_norm_vel[_qp].size() + eps);
    _l[_qp](1)=_grad_norm_vel[_qp](1)/(_grad_norm_vel[_qp].size() + eps);
    _l[_qp](2)=_grad_norm_vel[_qp](2)/(_grad_norm_vel[_qp].size() + eps);
    //_l = _l / (_grad_norm_vel[_qp].size() + eps);
    TensorValue<Real> grad_vel(_grad_vel_x[_qp], _grad_vel_y[_qp], _grad_vel_z[_qp]);
    
    // Initialyze some vector, values, ... for entropy viscosity method:
    RealVectorValue vel(_vel_x[_qp], _vel_y[_qp], _vel_z[_qp]);
    
    Real D_stt = 0.; Real wht = 0.; Real temp = 0.;
    Real D_P = 0.; Real D_rho = 0.;
    Real norm_kappa = 0.; Real norm_mu = 0.;
    Real jump = 0.; Real residual = 0.;
    Real kappa_e = 0.; Real mu_e = 0.;
    Real weight0 = 0.; Real weight1 = 0.; Real weight2 = 0.;
    
    // Switch statement over viscosity type:
    switch (_visc_type) {
        case LAPIDUS: // mu = h^2*l \cdot (v \cdot l)
            // Set the viscosity coefficients:
            if (_t_step == 1) {
                _mu[_qp] = _kappa_max[_qp];
                _kappa[_qp] = _kappa_max[_qp];
            }
            else {
                _mu[_qp] = _Ce*_h*_h*std::fabs(_l[_qp]*(grad_vel*_l[_qp]));
                _kappa[_qp] = _mu[_qp];
            }
            break;
        case FIRST_ORDER:
            _mu[_qp] = _kappa_max[_qp];
            _kappa[_qp] = _kappa_max[_qp];
            break;
        case FIRST_ORDER_MACH:
            _mu[_qp] = Mach*_kappa_max[_qp];
            _kappa[_qp] = _kappa_max[_qp];
            break;
        case ENTROPY:
            // Compute the viscosity coefficients:
            if (_t_step == 1) {
                _mu[_qp] = _kappa_max[_qp];
                _kappa[_qp] = _kappa_max[_qp];
            }
            else {
                // Compute the weigth for BDF2
                weight0 = (2.*_dt+_dt_old)/(_dt*(_dt+_dt_old));
                weight1 = -(_dt+_dt_old)/(_dt*_dt_old);
                weight2 = _dt/(_dt_old*(_dt+_dt_old));

                // Compute the normalization parameters:
                // Works for Leblanc
                norm_mu = 0.5*rhocv_pps;
                norm_kappa = 0.5*((1.-Mach)*std::min(rhoc2_pps, press_pps)+Mach*rhocv_pps);
//                norm_mu = 0.5*((1.-Mach)*rhocv_pps + Mach*std::min(rhov2_pps,rhoc2_pps));
//                norm_kappa = 0.5*((1.-Mach)*rhoc2_pps + Mach*std::min(rhov2_pps,rhoc2_pps));
                
                // Compute the residual for the wall heat transfer:
                temp = _eos.temperature_from_p_rho(_pressure[_qp], _rho[_qp]);
                Real Hw_val = isParamValid("Hw_fn_name") ? getFunctionByName(_Hw_fn_name).value(_t, _q_point[_qp]) : _Hw;
                Real Tw_val = isParamValid("Tw_fn_name") ? getFunctionByName(_Tw_fn_name).value(_t, _q_point[_qp]) : _Tw;
                wht = 0.;//Hw_val*_aw*(temp-Tw_val);

                // Compute the characteristic equation u:
                D_stt = vel*_grad_press[_qp];
                D_P = (weight0*_pressure[_qp]+weight1*_pressure_old[_qp]+weight2*_pressure_older[_qp]) + D_stt;
                D_stt = vel*_grad_rho[_qp];
                D_rho = (weight0*_rho[_qp]+weight1*_rho_old[_qp]+weight2*_rho_older[_qp]) + D_stt;
                residual = std::fabs(D_P-c*c*D_rho);
                
                // Compute global jump:
                jump = _isJumpOn ? _norm_vel[_qp]*std::max( _Cjump_press*_jump_grad_press[_qp], _Cjump_rho*c*c*_jump_grad_dens[_qp] ) : 0.;
                
                // Compute second order viscosity coefficients:
                kappa_e = _Ce*_h*_h*( ( residual + std::fabs(wht) + jump ) / norm_kappa);
                mu_e = _Ce*_h*_h*( ( residual + std::fabs(wht) + jump ) / norm_mu);
                
//                _kappa[_qp] = std::min( _kappa_max[_qp], kappa_e );
                _kappa[_qp] = std::min( _kappa_max[_qp], mu_e );
                _mu[_qp] = std::min( _kappa_max[_qp], mu_e );
            }
            break;
        case PRESSURE_BASED:
            if (_t_step == 1) {
                _mu[_qp] = _kappa_max[_qp];
                _kappa[_qp] = _kappa_max[_qp];
            }
            else {
                _mu[_qp] = _Ce*_h*_h*(_norm_vel[_qp] + c)*std::fabs(_PBVisc[_qp]);
                _kappa[_qp] = _mu[_qp];
            }
            break;
        default:
            mooseError("The viscosity type entered in the input file is not implemented.");
            break;
    }
}
