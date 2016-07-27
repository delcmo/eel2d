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

/**
This AuxKernel computes the first-order viscosity coefficient in 1-D.
**/

#include "OneDEntropyViscosityMethod.h"
#include "libmesh/quadrature.h"

template<>
InputParameters validParams<OneDEntropyViscosityMethod>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("rhoA", "density");
  params.addRequiredCoupledVar("rhouA", "momentum");
  params.addRequiredCoupledVar("rhoEA", "energy");
  params.addRequiredCoupledVar("rho", "rho");
  params.addRequiredCoupledVar("pressure", "pressure");
  params.addCoupledVar("press_jump", 0., "jump of pressure gradient");
  params.addCoupledVar("rho_jump", 0., "jump of density gradient");
  params.addCoupledVar("area", 1., "area");
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");
  params.addRequiredParam<std::string>("velocity_average", "name of the pps computing rho*vel*vel");
  params.addParam<Real>("Cejump", 1., "Constant multiplying the entropy residual and jumps.");
  params.addParam<Real>("Ce", 1., "Constant multiplying the entropy residual.");
  params.addParam<bool>("norm_type", false, "Boolean for choosing normalization type.");
  return params;
}

OneDEntropyViscosityMethod::OneDEntropyViscosityMethod(const InputParameters & parameters) :
    AuxKernel(parameters),
    _rhoA(coupledValue("rhoA")),
    _rhouA(coupledValue("rhouA")),
    _rhoEA(coupledValue("rhoEA")),
    _press(coupledValue("pressure")),
    _press_old(coupledValueOld("pressure")),
    _press_older(coupledValueOlder("pressure")),
    _press_grad(coupledGradient("pressure")),
    _rho(coupledValue("rho")),
    _rho_old(coupledValueOld("rho")),
    _rho_older(coupledValueOlder("rho")),
    _rho_grad(coupledGradient("rho")),
    _press_jump(coupledValue("press_jump")),
    _rho_jump(coupledValue("rho_jump")),
    _area(coupledValue("area")),
    _eos(getUserObject<OneDEquationOfState>("eos")),
    _vel_average(getParam<std::string>("velocity_average")),
    _Cejump(getParam<Real>("Cejump")),
    _Ce(getParam<Real>("Ce")),
    _norm_type(getParam<bool>("norm_type"))
{}

Real
OneDEntropyViscosityMethod::computeValue()
{
  Real h=_current_elem->volume();
  Real rho=_rhoA[_qp]/_area[_qp];
  Real rhou=_rhouA[_qp]/_area[_qp];
  Real rhoE=_rhoEA[_qp]/_area[_qp];
  Real vel=rhou/rho;
  Real c=std::sqrt(_eos.c2(rho, rhou, rhoE));
  Real visc_max=0.5*h*(std::fabs(vel)+c);
  
  Real vel_avg = std::max(getPostprocessorValueByName(_vel_average), 1.e-6);
  
  Real norm = _norm_type ? 0.5*rho*c*c : 0.5*rho*std::max( vel_avg*vel_avg, vel*vel );
  
  Real press_res=(_press[_qp]-_press_old[_qp])/_dt+vel*_press_grad[_qp](0);
  Real rho_res=(_rho[_qp]-_rho_old[_qp])/_dt+vel*_rho_grad[_qp](0);
  
  Real vel_abs = std::fabs(vel);
  
  Real res = ( _Ce*std::fabs(press_res-c*c*rho_res)+vel_abs*_press_jump[_qp] ) / norm;
  res += vel_abs*_rho_jump[_qp] / _rho[_qp];
  
//  Real res = h*h*( _Ce*std::fabs(press_res-c*c*rho_res)+_press_jump[_qp]+c*c*_rho_jump[_qp] );

//  Real res = h*h*( std::max(_press_jump[_qp], c*c*_rho_jump[_qp]) );
//  Real res = h*h*( _press_jump[_qp]+c*c*_rho_jump[_qp] );
  
  Real visc = _Cejump*h*h*res;

  return _t_step <= 1 ? visc_max : std::min(visc_max, visc);
}

void
OneDEntropyViscosityMethod::compute()
{
  Real value = 0;
  for (_qp=0; _qp<_qrule->n_points(); _qp++)
    value += _JxW[_qp]*_coord[_qp]*computeValue();
  
  if ( value < 0 )
    mooseError("The viscosity coefficient is locally negative.");
  
  value /= (_bnd ? _current_side_volume : _current_elem_volume);
  _var.setNodalValue(value);
}