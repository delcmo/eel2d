/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "OneDStabilization.h"

/**
This kerncel computes the artificial viscous fluxes for 1-D Euler equations with two viscosity coefficients 'mu' and 'kappa'.
 */

template<>
InputParameters validParams<OneDStabilization>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<std::string>("equation_name", "INVALID", "Name of the equation.");
  params.addRequiredCoupledVar("rho", "rho");
  params.addRequiredCoupledVar("velocity", "velocity");
  params.addRequiredCoupledVar("internal_energy", "internal energy");
  params.addCoupledVar("area", 1., "cross section");
  params.addRequiredCoupledVar("mu", "viscosity coefficient in momentum and energy equations");
  params.addRequiredCoupledVar("kappa", "viscosity coefficient in mass, momentum and energy equations");
  return params;
}

OneDStabilization::OneDStabilization(const InputParameters & parameters) :
  Kernel(parameters),
    _equ_name(getParam<std::string>("equation_name")),
    _equ_type("MASS MOMENTUM ENERGY INVALID", _equ_name),

    _rho(coupledValue("rho")),
    _rho_grad(coupledGradient("rho")),
    _vel(coupledValue("velocity")),
    _vel_grad(coupledGradient("velocity")),
    _int_ener(coupledValue("internal_energy")),
    _int_ener_grad(coupledGradient("internal_energy")),
    _area(coupledValue("area")),
    _mu(coupledValue("mu")),
    _kappa(coupledValue("kappa"))
{
}

Real OneDStabilization::computeQpResidual()
{
//  Real isonbnd = 1.;
//  if (_mesh.isBoundaryNode(_current_elem->node(_i))==true) {
//      isonbnd = 0.;}

  Real f(0.), g(0.), h(0.);

  switch (_equ_type)
  {
    case MASS:
      f = _kappa[_qp]*_rho_grad[_qp](0);
      return _area[_qp]*f*_grad_test[_i][_qp](0); break;
    case MOMENTUM:
      f = _kappa[_qp]*_rho_grad[_qp](0);
      g = _mu[_qp]*_rho[_qp]*_vel_grad[_qp](0);
      return _area[_qp]*(_vel[_qp]*f+g)*_grad_test[_i][_qp](0); break;
    case ENERGY:
      f = _kappa[_qp]*_rho_grad[_qp](0);
      g = _mu[_qp]*_rho[_qp]*_vel_grad[_qp](0);
      h = _kappa[_qp]*_rho[_qp]*_int_ener_grad[_qp](0);
      return _area[_qp]*(h+0.5*_vel[_qp]*_vel[_qp]*f+_vel[_qp]*g+_int_ener[_qp]*f)*_grad_test[_i][_qp](0); break;
    default:
      mooseError("INVALID equation name.");
  }
}

Real OneDStabilization::computeQpJacobian()
{
  return 0.;
}

Real OneDStabilization::computeQpOffDiagJacobian( unsigned int _jvar)
{
  return 0.;
}
