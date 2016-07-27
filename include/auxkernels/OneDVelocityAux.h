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

#ifndef ONEDVELOCITYAUX_H
#define ONEDVELOCITYAUX_H

#include "AuxKernel.h"

//Forward Declarations
class OneDVelocityAux;

template<>
InputParameters validParams<OneDVelocityAux>();

class OneDVelocityAux : public AuxKernel
{
public:

  OneDVelocityAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  const VariableValue & _rhoA;
  const VariableValue & _rhouA;
};

#endif // ONEDVELOCITYAUX_H
