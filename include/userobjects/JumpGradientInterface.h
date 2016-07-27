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

#ifndef JUMPGRADIENTINTERFACE_H
#define JUMPGRADIENTINTERFACE_H

#include "InternalSideUserObject.h"

class JumpGradientInterface;

template<>
InputParameters validParams<JumpGradientInterface>();

/**
 *
 */
class JumpGradientInterface : public InternalSideUserObject
{
public:
  JumpGradientInterface(const InputParameters & parameters);
  virtual ~JumpGradientInterface();

  virtual void initialize();
  virtual void execute();
  virtual void destroy();
  virtual void finalize();
  virtual void threadJoin(const UserObject & uo);

  Real getValue() const { return _value; }

protected:
    // Auxiliary system const Variable:
    AuxiliarySystem & _aux;
    // Gradient value:
    const VariableGradient & _grad_u;
    const VariableGradient & _grad_u_neighbor;
    // Name of the const Variable storing the jump:
    std::string _jump_name;
    // Temporary const Variable:
    Real _value;
};

#endif /* JUMPGRADIENTINTERFACE_H */
