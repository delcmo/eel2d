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

#include "OneDFirstOrderViscosityCoefficient.h"
#include "libmesh/quadrature.h"

template<>
InputParameters validParams<OneDFirstOrderViscosityCoefficient>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("rhoA", "rhoA");
  params.addRequiredCoupledVar("rhouA", "rhouA");
  params.addRequiredCoupledVar("rhoEA", "rhoEA");
  params.addCoupledVar("area", 1., "area");
  params.addRequiredParam<UserObjectName>("eos", "Equation of state");
  return params;
}

OneDFirstOrderViscosityCoefficient::OneDFirstOrderViscosityCoefficient(const InputParameters & parameters) :
    AuxKernel(parameters),
    _rhoA(coupledValue("rhoA")),
    _rhouA(coupledValue("rhouA")),
    _rhoEA(coupledValue("rhoEA")),
    _area(coupledValue("area")),
    _eos(getUserObject<OneDEquationOfState>("eos"))
{}

Real
OneDFirstOrderViscosityCoefficient::computeValue()
{
  Real rho=_rhoA[_qp]/_area[_qp];
  Real rhou=_rhouA[_qp]/_area[_qp];
  Real rhoE=_rhoEA[_qp]/_area[_qp];
  Real vel=rhou/rho;
  Real c=std::sqrt(_eos.c2(rho, rhou, rhoE));

  Real h=_current_elem->volume();
  
  return 0.5*h*(std::fabs(vel)+c);
}

void
OneDFirstOrderViscosityCoefficient::compute()
{
  Real value = 0;
  for (_qp=0; _qp<_qrule->n_points(); _qp++)
    value += _JxW[_qp]*_coord[_qp]*computeValue();
  
  if ( value < 0 )
    mooseError("The first-order viscosity coefficient is locally negative.");
  
  value /= (_bnd ? _current_side_volume : _current_elem_volume);
  _var.setNodalValue(value);
}