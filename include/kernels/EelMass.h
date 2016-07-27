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

#ifndef EELMASS_H
#define EELMASS_H

#include "Kernel.h"

class EelMass;

template<>
InputParameters validParams<EelMass>();
class EelMass : public Kernel
{
public:

  EelMass(const InputParameters & parameters);

protected:
 
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian( unsigned int jvar );

private:
    // Coupled variables:
    const VariableValue & _rhouA_x;
    const VariableValue & _rhouA_y;
    const VariableValue & _rhouA_z;
    
    // Parameters for jacobian:
    unsigned int _rhouA_x_nb;
    unsigned int _rhouA_y_nb;
    unsigned int _rhouA_z_nb;
};

#endif // EelMass_H
