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

#ifndef ONEDENERGY_H
#define ONEDENERGY_H

#include "Kernel.h"
#include "OneDEquationOfState.h"

// Forward Declarations
class OneDEnergy;

template<>
InputParameters validParams<OneDEnergy>();

class OneDEnergy : public Kernel
{
public:

  OneDEnergy(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian( unsigned int _jvar);

private:
  const VariableValue & _rhoA;
  const VariableValue & _rhouA;
  const VariableValue & _area;
  
  const OneDEquationOfState & _eos;
};

#endif // ONEDENERGY_H
