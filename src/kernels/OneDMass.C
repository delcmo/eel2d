/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                               */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "OneDMass.h"

/**
This kernel computes the advection term of the mass equation.
*/
template<>
InputParameters validParams<OneDMass>()
{
  InputParameters params = validParams<Kernel>();
    params.addRequiredCoupledVar("rhouA", "momentum");
  return params;
}

OneDMass::OneDMass(const InputParameters & parameters) :
  Kernel(parameters),
    _rhouA(coupledValue("rhouA"))
{}

Real OneDMass::computeQpResidual()
{
  return -_rhouA[_qp] * _grad_test[_i][_qp](0);
}

Real OneDMass::computeQpJacobian()
{
  return 0.;
}

Real OneDMass::computeQpOffDiagJacobian( unsigned int _jvar)
{
  return 0.;
}
