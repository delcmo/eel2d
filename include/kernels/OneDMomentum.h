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

#ifndef ONEDMOMENTUM_H
#define ONEDMOMENTUM_H

#include "Kernel.h"
#include "OneDEquationOfState.h"

class OneDMomentum;

template<>
InputParameters validParams<OneDMomentum>();

class OneDMomentum : public Kernel
{
public:

  OneDMomentum(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian( unsigned int jvar );

private:
  const VariableValue & _rhoA;
  const VariableValue & _rhoEA;
  const VariableValue & _area;
  const VariableGradient & _grad_area;

  const OneDEquationOfState & _eos;
};

#endif // ONEDMOMENTUM_H
