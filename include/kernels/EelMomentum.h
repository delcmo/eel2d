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

#ifndef EELMOMENTUM_H
#define EELMOMENTUM_H

#include "Kernel.h"
#include "EquationOfState.h"

// Forward Declarations
class EelMomentum;

template<>
InputParameters validParams<EelMomentum>();

class EelMomentum : public Kernel
{
public:

  EelMomentum(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian( unsigned int jvar );

private:
    // Aux variables:
    const VariableValue & _rhouA_x;
    const VariableValue & _rhouA_y;
    const VariableValue & _rhouA_z;
    const VariableValue & _pressure;
    const VariableValue & _rhoA;
    const VariableValue & _rhoEA;
    const VariableValue & _area;
    const VariableGradient & _grad_area;
    
    // Equation of state:
    const EquationOfState & _eos;
    
    // Parameters:
    int _component;
    Real _friction;
    Real _Dh;
    RealVectorValue _gravity;
    
    // Parameters for jacobian:
    unsigned int _rhoA_nb;
    unsigned int _rhouA_x_nb;
    unsigned int _rhouA_y_nb;
    unsigned int _rhouA_z_nb;
    unsigned int _rhoEA_nb;
};

#endif // EELMOMENTUM_H
