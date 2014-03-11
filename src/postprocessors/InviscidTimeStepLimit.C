#include "InviscidTimeStepLimit.h"
#include "EquationOfState.h"

template<>
InputParameters validParams<InviscidTimeStepLimit>()
{
  InputParameters params = validParams<ElementPostprocessor>();
  // Coupled variables
  params.addRequiredCoupledVar("pressure", "pressure");
  params.addRequiredCoupledVar("density", "density");
  params.addRequiredCoupledVar("norm_velocity", "norm of the velocity");
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");
  params.addParam<Real>("beta", 0.8, "User supplied constant");

  return params;
}

InviscidTimeStepLimit::InviscidTimeStepLimit(const std::string & name, InputParameters parameters) :
    ElementPostprocessor(name, parameters),
    _pressure(coupledValue("pressure")),
    _rho(coupledValue("density")),
    _norm_vel(coupledValue("norm_velocity")),
    _eos(getUserObject<EquationOfState>("eos")),
    _beta(getParam<Real>("beta"))
{
}

InviscidTimeStepLimit::~InviscidTimeStepLimit()
{
}

void
InviscidTimeStepLimit::initialize()
{
  _value = std::numeric_limits<Real>::max();
}

void
InviscidTimeStepLimit::execute()
{
  Real c = 0.;
  Real h_min = _current_elem->hmin();
    for (unsigned qp = 0; qp < _qrule->n_points(); ++qp) {
    c = std::sqrt(_eos.c2_from_p_rho(_rho[qp], _pressure[qp]));
    _value = std::min(_value, _beta * h_min / (_norm_vel[qp] + c));
    }
}

Real
InviscidTimeStepLimit::getValue()
{
  Parallel::min(_value);
  return _value;
}

void
InviscidTimeStepLimit::threadJoin(const UserObject & uo)
{
  const InviscidTimeStepLimit & pps = dynamic_cast<const InviscidTimeStepLimit &>(uo);
  _value = std::min(_value, pps._value);
}
