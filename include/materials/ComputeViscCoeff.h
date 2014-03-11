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
  ComputeViscCoeff(const std::string & name, InputParameters parameters);

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
    // Artificial diffusion name
    std::string _visc_name;
    
    // Aritifical diffusion type
    MooseEnum _visc_type;
    
    // Pressure-based viscosity:
    VariableValue & _PBVisc;
    
    // Boolean for jump
    bool _isJumpOn;
    
    // Coupled aux variables: velocity
    VariableValue & _vel_x;
    VariableValue & _vel_y;
    VariableValue & _vel_z;
    VariableValue & _vel_x_old;
    VariableValue & _vel_y_old;
    VariableValue & _vel_z_old;
    VariableGradient & _grad_vel_x;
    VariableGradient & _grad_vel_y;
    VariableGradient & _grad_vel_z;
    
    // Coupled aux variables: pressure
    VariableValue & _pressure;
    VariableValue & _pressure_old;
    VariableValue & _pressure_older;
    VariableGradient & _grad_press;
    VariableGradient & _grad_press_old;
    
    // Coupled aux variable: density
    VariableValue & _rho;
    VariableValue & _rho_old;
    VariableValue & _rho_older;
    VariableGradient & _grad_rho;
    VariableGradient & _grad_rho_old;
    
    // Coupled aux variable: norm of velocity
    VariableValue & _norm_vel;
    VariableGradient & _grad_norm_vel;
    
    // Jump of pressure gradient:
    VariableValue & _jump_grad_press;
    VariableValue & _jump_grad_dens;
    
    // Jump cross section:
    VariableValue & _jump_grad_area;
    VariableValue & _area;
    
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
    const double & _Ce;
    const double & _Cjump;
    
    // UserObject: equation of state
    const EquationOfState & _eos;
    
    // Name of the posprocessors for pressure and velocity:
    std::string _velocity_pps_name;
    bool _useVelPps;
};

#endif //ComputeViscCoeff_H
