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

#ifndef ONEDFIRSTORDERVISCOSITYCOEFFICIENT_H
#define ONEDFIRSTORDERVISCOSITYCOEFFICIENT_H

#include "AuxKernel.h"
#include "OneDEquationOfState.h"

//Forward Declarations
class OneDFirstOrderViscosityCoefficient;

template<>
InputParameters validParams<OneDFirstOrderViscosityCoefficient>();

class OneDFirstOrderViscosityCoefficient : public AuxKernel
{
public:

  OneDFirstOrderViscosityCoefficient(const InputParameters & parameters);

protected:
  virtual Real computeValue();
  virtual void compute();

  const VariableValue & _rhoA;
  const VariableValue & _rhouA;
  const VariableValue & _rhoEA;
  const VariableValue & _area;

  const OneDEquationOfState & _eos;
};

#endif // ONEDFIRSTORDERVISCOSITYCOEFFICIENT_H
