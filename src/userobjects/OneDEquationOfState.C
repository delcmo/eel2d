#include "OneDEquationOfState.h"
#include "MooseError.h"

template<>
InputParameters validParams<OneDEquationOfState>()
{
  InputParameters params = validParams<UserObject>();
  return params;
}

OneDEquationOfState::OneDEquationOfState(const InputParameters & parameters) :
  GeneralUserObject(parameters)
{}

OneDEquationOfState::~OneDEquationOfState()
{
}

void
OneDEquationOfState::destroy()
{
}

Real OneDEquationOfState::pressure(Real rho, Real vel_norm, Real rhoE) const
{
    this->error_not_implemented("pressure");
    return 0.;
}

Real OneDEquationOfState::rho_from_press_T(Real press, Real T) const
{
  this->error_not_implemented("rho_from_press_T");
  return 0.;
}

Real OneDEquationOfState::e_from_press_rho(Real press, Real rho) const
{
  this->error_not_implemented("e_from_press_rho");
  return 0.;
}

Real OneDEquationOfState::c2(Real rho, Real vel_norm, Real rhoE) const
{
  this->error_not_implemented("speed of sound");
  return 0.;
}

//Real OneDEquationOfState::gamma() const
//{
//    return _gamma;
//}
//
//Real OneDEquationOfState::Pinf() const
//{
//    return _Pinf;
//}
//
//Real OneDEquationOfState::qcoeff() const
//{
//    return _qcoeff;
//}
//
//Real OneDEquationOfState::qcoeff_prime() const
//{
//    return _qcoeff_prime;
//}
//
//Real OneDEquationOfState::Cv() const
//{
//    return _Cv;
//}

void OneDEquationOfState::error_not_implemented(std::string method_name) const
{}
