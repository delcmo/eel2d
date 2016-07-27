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
This AuxKernel computes the fluid internal energy in 1-D
**/

#include "OneDInternalEnergyAux.h"

template<>
InputParameters validParams<OneDInternalEnergyAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("rhoA", "rhoA");
  params.addRequiredCoupledVar("rhouA", "rhouA");
  params.addRequiredCoupledVar("rhoEA", "rhoEA");
  params.addCoupledVar("area", 1., "area");
  return params;
}

OneDInternalEnergyAux::OneDInternalEnergyAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    _rhoA(coupledValue("rhoA")),
    _rhouA(coupledValue("rhouA")),
    _rhoEA(coupledValue("rhoEA")),
    _area(coupledValue("area"))
{}

Real
OneDInternalEnergyAux::computeValue()
{
  Real rho=_rhoA[_qp]/_area[_qp];
  Real rhou=_rhouA[_qp]/_area[_qp];
  Real rhoE=_rhoEA[_qp]/_area[_qp];
  
  return (rhoE-0.5*rhou*rhou/rho)/rho;
}
