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

#ifndef PRESSUREAUX_H
#define PRESSUREAUX_H

#include "AuxKernel.h"
#include "EquationOfState.h"

//Forward Declarations
class PressureAux;

template<>
InputParameters validParams<PressureAux>();

class PressureAux : public AuxKernel
{
public:

  PressureAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  const VariableValue & _rhoA;
  const VariableValue & _rhouA_x;
  const VariableValue & _rhouA_y;
  const VariableValue & _rhouA_z;
  const VariableValue & _rhoEA;
  const VariableValue & _area;
  const EquationOfState & _eos;
};

#endif //PRESSUREAUX_H
