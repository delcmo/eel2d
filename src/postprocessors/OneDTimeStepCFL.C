#include "OneDTimeStepCFL.h"
#include "MooseMesh.h"
#include "libmesh/quadrature.h"

/**
This postprocessor computes the time step of the temporal discretization based on the cfl parameter.
**/

template<>
InputParameters validParams<OneDTimeStepCFL>()
{
  InputParameters params = validParams<ElementPostprocessor>();
  params.addRequiredCoupledVar("rhoA", "density");
  params.addRequiredCoupledVar("rhouA", "momentum");
  params.addRequiredCoupledVar("rhoEA", "energy");
  params.addCoupledVar("area", 1., "cross-section");
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");
  params.addParam<Real>("cfl", 1., "CFL number to supply by the user");
  return params;
}

OneDTimeStepCFL::OneDTimeStepCFL(const InputParameters & parameters) :
    ElementPostprocessor(parameters),
    _rhoA(coupledValue("rhoA")),
    _rhouA(coupledValue("rhouA")),
    _rhoEA(coupledValue("rhoEA")),
    _area(coupledValue("area")),

    _eos(getUserObject<OneDEquationOfState>("eos")),

    _cfl(getParam<Real>("cfl")),
    _value(0.)
{
}

OneDTimeStepCFL::~OneDTimeStepCFL()
{
}

void
OneDTimeStepCFL::initialize()
{
  _value = std::numeric_limits<Real>::max();
}

void
OneDTimeStepCFL::execute()
{
  Real h_cell = std::pow(_current_elem->volume(), 1./_mesh.dimension());

  for (unsigned qp = 0; qp < _qrule->n_points(); ++qp)
  {
    Real vel = _rhouA[qp] / _rhoA[qp];
    Real rho = _rhoA[qp]/_area[qp];
    Real rhou = _rhouA[qp]/_area[qp];
    Real rhoE = _rhoEA[qp]/_area[qp];
    Real eigen = std::fabs(vel)+std::sqrt(_eos.c2(rho, rhou, rhoE));
    Real dt = _cfl * h_cell / eigen;

    _value = std::min(_value, dt);
  }
}

Real
OneDTimeStepCFL::getValue()
{
  _communicator.min(_value);
  return _value;
}

void
OneDTimeStepCFL::threadJoin(const UserObject & uo)
{
  const OneDTimeStepCFL & pps = dynamic_cast<const OneDTimeStepCFL &>(uo);
  _value = std::min(_value, pps._value);
}