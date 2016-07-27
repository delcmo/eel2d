#include "OneDStiffenedGasEquationOfState.h"

template<>
InputParameters validParams<OneDStiffenedGasEquationOfState>()
{
  InputParameters params = validParams<OneDEquationOfState>();
  params.addRequiredParam<Real>("gamma", "  gamma");
  params.addParam<Real>("Pinf", 0, "  P infinity");
  params.addParam<Real>("q", 0, "  q coefficient");
  params.addParam<Real>("q_prime", 0, "  q' coefficient");
  params.addParam<Real>("Cv", "heat capacity at constant volume");
  return params;
}

OneDStiffenedGasEquationOfState::OneDStiffenedGasEquationOfState(const InputParameters & parameters) :
  OneDEquationOfState(parameters),
    _gamma(getParam<Real>("gamma")),
    _Pinf(getParam<Real>("Pinf")),
    _qcoeff(getParam<Real>("q")),
    _qcoeff_prime(getParam<Real>("q_prime")),
    _Cv(isParamValid("Cv") ? getParam<Real>("Cv") : 1./(_gamma-1.))
{}

OneDStiffenedGasEquationOfState::~OneDStiffenedGasEquationOfState()
{
}

void
OneDStiffenedGasEquationOfState::destroy()
{
}

Real OneDStiffenedGasEquationOfState::pressure(Real rho, Real rhou, Real rhoE) const
{
  Real e = ( rhoE - 0.5*rhou*rhou / rho ) / rho;
  return ( (_gamma-1) * ( e - _qcoeff) * rho - _gamma * _Pinf );
}

Real OneDStiffenedGasEquationOfState::rho_from_press_T(Real press, Real T) const
{
  return (press+_Pinf) / ((_gamma-1.)*T*_Cv);
}

Real OneDStiffenedGasEquationOfState::e_from_press_rho(Real press, Real rho) const
{
  return (press+_gamma*_Pinf) / ((_gamma-1.)*rho) + _qcoeff;
}

Real OneDStiffenedGasEquationOfState::c2(Real rho, Real rhou, Real rhoE) const
{
  Real press = this->pressure(rho, rhou, rhoE);
  return _gamma*(press+_Pinf)/rho;
}
