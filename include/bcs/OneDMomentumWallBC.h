#ifndef ONEDMOMENTUMWALLBC_H
#define ONEDMOMENTUMWALLBC_H

#include "IntegratedBC.h"
#include "OneDEquationOfState.h"

class OneDMomentumWallBC;

template<>
InputParameters validParams<OneDMomentumWallBC>();

class OneDMomentumWallBC : public IntegratedBC
{

public:
  OneDMomentumWallBC(const InputParameters & parameters);

  virtual ~OneDMomentumWallBC(){}

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);
    
  // Coupled aux const Variables
  const VariableValue & _rhoA;
  const VariableValue & _rhoEA;
  const VariableValue & _area;
    
  // Equation of state for jacobian matrix:
  const OneDEquationOfState & _eos;
};

#endif // ONEDMOMENTUMWALLBC_H
