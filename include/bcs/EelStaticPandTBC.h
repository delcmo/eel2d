#ifndef EELSTATICPANDTBC_H
#define EELSTATICPANDTBC_H

#include "IntegratedBC.h"
#include "EquationOfState.h"

// Forward Declarations
class EelStaticPandTBC;
class EquationOfState;

template<>
InputParameters validParams<EelStaticPandTBC>();

class EelStaticPandTBC : public IntegratedBC
{

public:
  EelStaticPandTBC(const InputParameters & parameters);

  virtual ~EelStaticPandTBC(){}

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);

  enum EFlowEquationType
  {
    CONTINUITY = 0,
    XMOMENTUM = 1,
    YMOMENTUM = 2,
    ENERGY = 3
  };

    // Eqn. name to be read from input file
    std::string _eqn_name;
    // which equation (mass/momentum/energy) this BC is acting on
    MooseEnum _eqn_type;
    // Coupled aux const Variables
    const VariableValue & _rhoA;
    const VariableValue & _rhouA_x;
    const VariableValue & _rhouA_y;
    const VariableValue & _rhoEA;
    const VariableValue & _rhoA_old;
    const VariableValue & _rhouA_x_old;
    const VariableValue & _rhouA_y_old;
    const VariableValue & _rhoEA_old;
    const VariableValue & _area;
    
    // Specified pressure
    Real _p_bc;
    
    // Specified temperature
    Real _T_bc;
    
    // Specified inflow angle
    Real _gamma_bc;
    
    // Equation of state
    const EquationOfState & _eos;
    
    // Parameters for jacobian matrix:
    unsigned int _rhoA_nb;
    unsigned int _rhouA_x_nb;
    unsigned int _rhouA_y_nb;
    unsigned int _rhoEA_nb;
};

#endif // EELSTATICPANDTBC_H

