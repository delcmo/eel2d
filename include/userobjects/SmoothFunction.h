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

#ifndef SMOOTHFUNCTION_H
#define SMOOTHFUNCTION_H

#include "InternalSideUserObject.h"

class SmoothFunction;

template<>
InputParameters validParams<SmoothFunction>();

/**
 *
 */
class SmoothFunction : public InternalSideUserObject
{
public:
  SmoothFunction(const InputParameters & parameters);
  virtual ~SmoothFunction();

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
    const VariableValue & _u;
    const VariableValue & _u_neighbor;
    // Name of the const Variable storing the jump:
    std::string _var_name;
    // Temporary const Variable:
    Real _value;
};

#endif /* SMOOTHFUNCTION_H */
