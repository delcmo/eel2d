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

#ifndef VARIABLETIMESAREAAUX_H
#define VARIABLETIMESAREAAUX_H

#include "AuxKernel.h"

class VariableTimesAreaAux;

template<>
InputParameters validParams<VariableTimesAreaAux>();

class VariableTimesAreaAux : public AuxKernel
{
public:

  VariableTimesAreaAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

    const VariableValue & _var;
    const VariableValue & _area;
};

#endif //VariableTimesAreaAUX_H
