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

#ifndef ONEDINTERNALENERGYAUX_H
#define ONEDINTERNALENERGYAUX_H

#include "AuxKernel.h"

//Forward Declarations
class OneDInternalEnergyAux;

template<>
InputParameters validParams<OneDInternalEnergyAux>();

class OneDInternalEnergyAux : public AuxKernel
{
public:

  OneDInternalEnergyAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  const VariableValue & _rhoA;
  const VariableValue & _rhouA;
  const VariableValue & _rhoEA;
  const VariableValue & _area;
};

#endif // ONEDINTERNALENERGYAUX_H
