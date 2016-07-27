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

#ifndef ONEDDENSITYAUX_H
#define ONEDDENSITYAUX_H

#include "AuxKernel.h"

class OneDDensityAux;

template<>
InputParameters validParams<OneDDensityAux>();

class OneDDensityAux : public AuxKernel
{
public:

  OneDDensityAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  const VariableValue & _rhoA;
  const VariableValue & _area;
};

#endif // ONEDDENSITYAUX_H
