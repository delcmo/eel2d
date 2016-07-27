#ifndef ONEDTIMESTEPCFL_H
#define ONEDTIMESTEPCFL_H

#include "ElementPostprocessor.h"
#include "OnedEquationOfState.h"

class OneDTimeStepCFL;

template<>
InputParameters validParams<OneDTimeStepCFL>();

class OneDTimeStepCFL : public ElementPostprocessor
{
public:
  OneDTimeStepCFL(const InputParameters & parameters);
  virtual ~OneDTimeStepCFL();

  virtual void initialize();
  virtual void execute();
  virtual Real getValue();
  virtual void threadJoin(const UserObject & uo);

protected:

  const VariableValue & _rhoA;
  const VariableValue & _rhouA;
  const VariableValue & _rhoEA;
  const VariableValue & _area;

  const OneDEquationOfState & _eos;

  const Real & _cfl;
  Real _value;
};


#endif // ONEDTIMESTEPCFL_H
