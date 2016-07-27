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
This function computes the fluid density in 1-D
**/

#include "OneDDensityAux.h"

template<>
InputParameters validParams<OneDDensityAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("rhoA", "momentum");
  params.addCoupledVar("area", 1., "cross-section");
  return params;
}

OneDDensityAux::OneDDensityAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    _rhoA(coupledValue("rhoA")),
    _area(coupledValue("area"))
{}

Real
OneDDensityAux::computeValue()
{
  return _rhoA[_qp] / _area[_qp];
}
