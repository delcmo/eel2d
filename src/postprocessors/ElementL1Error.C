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

#include "ElementL1Error.h"
#include "Function.h"

template<>
InputParameters validParams<ElementL1Error>()
{
  InputParameters params = validParams<ElementIntegralVariablePostprocessor>();
  params.addRequiredParam<FunctionName>("function", "The analytic solution to compare against");
  return params;
}

ElementL1Error::ElementL1Error(const InputParameters & parameters) :
    ElementIntegralVariablePostprocessor(parameters),
//    FunctionInterface(parameters),
    _func(getFunction("function"))
{
}

Real
ElementL1Error::getValue()
{
  return std::sqrt(ElementIntegralPostprocessor::getValue());
}

Real
ElementL1Error::computeQpIntegral()
{
    Real diff = std::fabs(_u[_qp]-_func.value(_t, _q_point[_qp]));
  return diff;
}
