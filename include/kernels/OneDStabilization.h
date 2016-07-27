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

#ifndef ONEDSTABILIZATION_H
#define ONEDSTABILIZATION_H

#include "Kernel.h"

class OneDStabilization;

template<>
InputParameters validParams<OneDStabilization>();

class OneDStabilization : public Kernel
{
public:

  OneDStabilization(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int _jvar);
    
private:
  enum EquationType
  {
    MASS = 0, MOMENTUM = 1, ENERGY = 2
  };

  std::string _equ_name;
  MooseEnum _equ_type;

  const VariableValue & _rho;
  const VariableGradient & _rho_grad;
  const VariableValue & _vel;
  const VariableGradient & _vel_grad;
  const VariableValue & _int_ener;
  const VariableGradient & _int_ener_grad;
  const VariableValue & _area;
  const VariableValue & _mu;
  const VariableValue & _kappa;
};

#endif // ONEDSTABILIZATION_H
