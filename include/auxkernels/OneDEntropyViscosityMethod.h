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

#ifndef ONEDENTROPYVISCOSITYMETHOD_H
#define ONEDENTROPYVISCOSITYMETHOD_H

#include "AuxKernel.h"
#include "OneDEquationOfState.h"

//Forward Declarations
class OneDEntropyViscosityMethod;

template<>
InputParameters validParams<OneDEntropyViscosityMethod>();

class OneDEntropyViscosityMethod : public AuxKernel
{
public:

  OneDEntropyViscosityMethod(const InputParameters & parameters);

protected:
  virtual Real computeValue();
  virtual void compute();

  const VariableValue & _rhoA;
  const VariableValue & _rhouA;
  const VariableValue & _rhoEA;
  
  const VariableValue & _press;
  const VariableValue & _press_old;
  const VariableValue & _press_older;
  const VariableGradient & _press_grad;
  
  const VariableValue & _rho;
  const VariableValue & _rho_old;
  const VariableValue & _rho_older;
  const VariableGradient & _rho_grad;
  
  const VariableValue & _press_jump;
  const VariableValue & _rho_jump;
  
  const VariableValue & _area;

  const OneDEquationOfState & _eos;
  
  const std::string _vel_average;
  
  const Real _Cejump;
  const Real _Ce;
  const Real _Cmax;
  
  const bool _norm_type;
};

#endif // ONEDENTROPYVISCOSITYMETHOD_H
