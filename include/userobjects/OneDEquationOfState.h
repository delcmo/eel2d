#ifndef ONEDEQUATIONOFSTATE_H
#define ONEDEQUATIONOFSTATE_H

#include "GeneralUserObject.h"

// Forward Declarations
class OneDEquationOfState;

template<>
InputParameters validParams<OneDEquationOfState>();

class OneDEquationOfState : public GeneralUserObject
{
public:
  // Constructor
  OneDEquationOfState(const InputParameters & parameters);

  // Destructor  
  virtual ~OneDEquationOfState();

  virtual void execute() {};
  virtual void initialize(){};
  virtual void destroy();
  virtual void finalize(){};

  virtual Real pressure(Real rho=0., Real rhou=0., Real rhoE=0.) const;
  virtual Real rho_from_press_T(Real press=0., Real T=0.) const;
  virtual Real e_from_press_rho(Real press=0., Real rho=0.) const;
  virtual Real c2(Real rho=0., Real rhou=0., Real rhoE=0.) const;
  
protected:
  void error_not_implemented(std::string method_name) const;
};

#endif // ONEDEQUATIONOFSTATE_H
