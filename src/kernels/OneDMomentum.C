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

#include "OneDMomentum.h"

/**
This kernel computes the 1-D advection term of the momentum equation
 */

template<>
InputParameters validParams<OneDMomentum>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("rhoA", "density");
  params.addRequiredCoupledVar("rhoEA", "total energy");
  params.addCoupledVar("area", 1., "cross section");
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");
  return params;
}

OneDMomentum::OneDMomentum(const InputParameters & parameters) :
  Kernel(parameters),
    _rhoA(coupledValue("rhoA")),
    _rhoEA(coupledValue("rhoEA")),
    _area(coupledValue("area")),
    _grad_area(coupledGradient("area")),

    _eos(getUserObject<OneDEquationOfState>("eos"))
{
}

Real OneDMomentum::computeQpResidual()
{
  Real rho = _rhoA[_qp]/_area[_qp];
  Real rhou = _u[_qp]/_area[_qp];
  Real rhoE = _rhoEA[_qp]/_area[_qp];
  Real pressure = _eos.pressure(rho, rhou, rhoE);
  
  Real convection = _u[_qp]*_u[_qp]/_rhoA[_qp];
  
  Real xs_source = pressure*_grad_area[_qp](0);
  
  return -(convection + pressure*_area[_qp])*_grad_test[_i][_qp](0) - xs_source*_test[_i][_qp];
}

Real OneDMomentum::computeQpJacobian()
{
  return 0.;
}

Real OneDMomentum::computeQpOffDiagJacobian( unsigned int _jvar)
{
  return 0.;
}
