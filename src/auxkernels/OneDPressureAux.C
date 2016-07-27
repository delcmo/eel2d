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

/**
This AuxKernel computes the fluid pressure in 1-D
**/

#include "OneDPressureAux.h"

template<>
InputParameters validParams<OneDPressureAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("rhoA", "rhoA");
  params.addRequiredCoupledVar("rhouA", "rhouA");
  params.addRequiredCoupledVar("rhoEA", "rhoEA");
  params.addCoupledVar("area", 1., "area");
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");
  return params;
}

OneDPressureAux::OneDPressureAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    _rhoA(coupledValue("rhoA")),
    _rhouA(coupledValue("rhouA")),
    _rhoEA(coupledValue("rhoEA")),
    _area(coupledValue("area")),
    _eos(getUserObject<OneDEquationOfState>("eos"))
{}

Real
OneDPressureAux::computeValue()
{
  Real rho=_rhoA[_qp]/_area[_qp];
  Real rhou=_rhouA[_qp]/_area[_qp];
  Real rhoE=_rhoEA[_qp]/_area[_qp];
  
  return _eos.pressure(rho, rhou, rhoE);
}
