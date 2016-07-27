#ifndef ONEDSTIFFENEDGASEQUATIONOFSTATE_H
#define ONEDSTIFFENEDGASEQUATIONOFSTATE_H

#include "OneDEquationOfState.h"

// Forward Declarations
class OneDStiffenedGasEquationOfState;

template<>
InputParameters validParams<OneDStiffenedGasEquationOfState>();

class OneDStiffenedGasEquationOfState : public OneDEquationOfState
{
public:
  OneDStiffenedGasEquationOfState(const InputParameters & parameters);
  
  virtual ~OneDStiffenedGasEquationOfState();

  virtual void execute() {};
  virtual void initialize(){};
  virtual void destroy();
  virtual void finalize() {};

  virtual Real pressure(Real rho=0., Real rhou=0., Real rhoE=0.) const;
  virtual Real rho_from_press_T(Real press=0., Real T=0.) const;
  virtual Real e_from_press_rho(Real press=0., Real rho=0.) const;
  virtual Real c2(Real rho=0., Real rhou=0., Real rhoE=0.) const;

protected:
    Real _gamma;
    Real _Pinf;
    Real _qcoeff;
    Real _qcoeff_prime;
    Real _Cv;
};


#endif // ONEDSTIFFENEDGASEQUATIONOFSTATE_H
