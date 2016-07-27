#ifndef MOMENTUMFREESLIPBC_H
#define MOMENTUMFREESLIPBC_H

#include "NodalNormalBC.h"

class MomentumFreeSlipBC;

template<>
InputParameters validParams<MomentumFreeSlipBC>();

/**
 *
 */
class MomentumFreeSlipBC : public NodalNormalBC
{
public:
  MomentumFreeSlipBC(const InputParameters & parameters);
  virtual ~MomentumFreeSlipBC();

  virtual void computeResidual(NumericVector<Number> & residual);
  virtual bool shouldApply();

protected:
  virtual Real computeQpResidual();

  const unsigned int _mesh_dimension;
  
  const VariableValue & _rho_u;
  const VariableValue & _rho_v;
  const VariableValue & _rho_w;
};


#endif /* MOMENTUMFREESLIPBC_H_ */
