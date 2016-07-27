/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "OneDEnergy.h"

/**
This function computes the convective part of the total energy equation.
 */
template<>
InputParameters validParams<OneDEnergy>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("rhoA", "density");
  params.addRequiredCoupledVar("rhouA", "momentum");
  params.addCoupledVar("area", 1., "cross section");
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");
  return params;
}

OneDEnergy::OneDEnergy(const InputParameters & parameters) :
  Kernel(parameters),
  _rhoA(coupledValue("rhoA")),
  _rhouA(coupledValue("rhouA")),
  _area(coupledValue("area")),
  
  _eos(getUserObject<OneDEquationOfState>("eos"))
{
}

Real OneDEnergy::computeQpResidual()
{
  Real rho = _rhoA[_qp]/_area[_qp];
  Real rhou = _rhouA[_qp]/_area[_qp];
  Real rhoE = _u[_qp]/_area[_qp];
  Real pressure = _eos.pressure(rho, rhou, rhoE);
  
  return -_rhouA[_qp]/_rhoA[_qp]*(_u[_qp] + pressure*_area[_qp])*_grad_test[_i][_qp](0);
}

Real OneDEnergy::computeQpJacobian()
{
  return 0.;
}

Real OneDEnergy::computeQpOffDiagJacobian( unsigned int _jvar)
{
  return 0.;
}
