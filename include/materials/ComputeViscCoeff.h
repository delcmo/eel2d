#ifndef COMPUTEVISCCOEFF_H
#define COMPUTEVISCCOEFF_H

#include "Material.h"
#include "MaterialProperty.h"
#include "EquationOfState.h"

//Forward Declarations
class ComputeViscCoeff;

template<>
InputParameters validParams<ComputeViscCoeff>();

class ComputeViscCoeff : public Material
{
public:
  ComputeViscCoeff(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

private:
    // Viscosity types
    enum ViscosityType
    {
        LAPIDUS = 0,
        FIRST_ORDER = 1,
        FIRST_ORDER_MACH = 2,
        ENTROPY = 3,
        PRESSURE_BASED = 4
    };
    std::string _visc_name;
    MooseEnum _visc_type;
    
    // Pressure-based viscosity:
    enum PBType
    {
        JST = 0,
        HMP = 1,
        ST = 2
    };
    const VariableValue & _PBVisc;
    std::string _norm_pbs_name;
    MooseEnum _norm_pbs_type;
    
    // Boolean for jump
    bool _isJumpOn;
    bool _isShock;
    
    // Coupled aux const Variables: velocity
    const VariableValue & _vel_x;
    const VariableValue & _vel_y;
    const VariableValue & _vel_z;
    const VariableGradient & _grad_vel_x;
    const VariableGradient & _grad_vel_y;
    const VariableGradient & _grad_vel_z;
    
    // Coupled aux const Variables: pressure
    const VariableValue & _pressure;
    const VariableValue & _pressure_old;
    const VariableValue & _pressure_older;
    const VariableGradient & _grad_press;
    
    // Coupled aux const Variable: density
    const VariableValue & _rho;
    const VariableValue & _rho_old;
    const VariableValue & _rho_older;
    const VariableGradient & _grad_rho;
    
    // Coupled aux const Variable: norm of velocity
    const VariableValue & _norm_vel;
    const VariableGradient & _grad_norm_vel;
    
    // Jump of pressure gradient:
    const VariableValue & _jump_grad_press;
    const VariableValue & _jump_grad_dens;
    
    // Jump cross section:
    const VariableValue & _area;
    const VariableGradient & _grad_area;
    
    // Material properties
    MaterialProperty<Real> & _mu;
    MaterialProperty<Real> & _mu_max;
    MaterialProperty<Real> & _kappa;
    MaterialProperty<Real> & _kappa_max;
    MaterialProperty<RealVectorValue> & _l;
    
//    MaterialProperty<Real> & _residual;
    // Wall heat transfer
    std::string _Hw_fn_name;
    std::string _Tw_fn_name;
    const Real & _Hw;
    const Real & _Tw;
    const Real & _aw;
    
    // Multiplicative coefficient for viscosity:
    double _Ce;
    double _Cjump;
    double _Cmax;
    
    // UserObject: equation of state
    const EquationOfState & _eos;
    
    // Name of the posprocessors for pressure, velocity and void fraction:
    std::string _rhov2_pps_name;
    std::string _rhoc2_pps_name;
    std::string _press_pps_name;
};

#endif //ComputeViscCoeff_H
