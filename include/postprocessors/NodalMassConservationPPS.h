#ifndef NODALMASSCONSERVATIONPPS_H
#define NODALMASSCONSERVATIONPPS_H

#include "NodalPostprocessor.h"

class NodalMassConservationPPS;

template<>
InputParameters validParams<NodalMassConservationPPS>();

/**
 * Computes \int{\Gamma} \rho \vec u \hat n \d\Gamma at nodes
 *
 * NOTES:
 * - nodal normals has to be turned on
 * - will work only with nodal shape functions (i.e. like LAGRANGE)
 */
class NodalMassConservationPPS : public NodalPostprocessor
{
public:
  NodalMassConservationPPS(const InputParameters & parameters);
  virtual ~NodalMassConservationPPS();

  virtual void initialize();
  virtual void execute();
  virtual PostprocessorValue getValue();
  virtual void threadJoin(const UserObject & uo);

protected:
  Real _value;
  /// Components of nodal normals
  const VariableValue & _nx;
  const VariableValue & _ny;
  const VariableValue & _nz;
  /// Components of momentum vector
  const VariableValue & _rho_u;
  const VariableValue & _rho_v;
  const VariableValue & _rho_w;
};

#endif /* NODALMASSCONSERVATIONPPS_H */
