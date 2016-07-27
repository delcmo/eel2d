#include "OneDMomentumWallBC.h"

template<>
InputParameters validParams<OneDMomentumWallBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredCoupledVar("rhoA", "density");
  params.addRequiredCoupledVar("rhoEA", "energy: rho*E*A");
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");
  params.addCoupledVar("area", 1., "area");
  return params;
}

OneDMomentumWallBC::OneDMomentumWallBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _rhoA(coupledValue("rhoA")),
    _rhoEA(coupledValue("rhoEA")),
    _area(coupledValue("area")),
    _eos(getUserObject<OneDEquationOfState>("eos"))
{
}

Real
OneDMomentumWallBC::computeQpResidual()
{
  // Compute the pressure:
  Real rho = _rhoA[_qp]/_area[_qp];
  Real rhou = _u[_qp]/_area[_qp];
  Real rhoE = _rhoEA[_qp]/_area[_qp];
  Real pressure = _eos.pressure(rho, rhou, rhoE);
  
  return pressure*_area[_qp]*_test[_i][_qp]*_normals[_qp](0);
}

Real
OneDMomentumWallBC::computeQpJacobian()
{
  return 0.;
}

Real
OneDMomentumWallBC::computeQpOffDiagJacobian(unsigned _jvar)
{
  return 0.;
}
