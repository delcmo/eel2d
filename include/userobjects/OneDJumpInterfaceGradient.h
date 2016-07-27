#ifndef OneDJumpInterfaceGradient_H
#define OneDJumpInterfaceGradient_H

#include "InternalSideUserObject.h"

class OneDJumpInterfaceGradient;

template<>
InputParameters validParams<OneDJumpInterfaceGradient>();

/**
 * This class computes the jump of the gradient of a given quantity when using CONTINUOUS finite element.
 * This class acts on the internal sides of the cell.
 */
class OneDJumpInterfaceGradient : public InternalSideUserObject
{
public:
  OneDJumpInterfaceGradient(const InputParameters & parameters);
  virtual ~OneDJumpInterfaceGradient();

  virtual void initialize();
  virtual void execute();
  virtual void destroy();
  virtual void finalize();
  virtual void threadJoin(const UserObject & uo);

  Real getValue() const { return _value; }

protected:
  // Auxiliary system variable:
  AuxiliarySystem & _aux;
  // Gradient value:
  const VariableGradient & _grad_u;
  const VariableGradient & _grad_u_neighbor;
  // Name of the variable storing the jump:
  std::string _jump_name;
  // Temporary variable:
  Real _value;
};


#endif /* OneDJumpInterfaceGradient_H */
