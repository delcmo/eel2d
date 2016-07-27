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
This AuxKernel computes the fluid velocity in 1-D
**/

#include "OneDVelocityAux.h"

template<>
InputParameters validParams<OneDVelocityAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("rhoA", "rhoA");
  params.addRequiredCoupledVar("rhouA", "rhouA");
  return params;
}

OneDVelocityAux::OneDVelocityAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    _rhoA(coupledValue("rhoA")),
    _rhouA(coupledValue("rhouA"))
{}

Real
OneDVelocityAux::computeValue()
{
  return _rhouA[_qp]/_rhoA[_qp];
}
