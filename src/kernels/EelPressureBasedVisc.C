/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                               */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "EelPressureBasedVisc.h"

/**
This Kernel computes the pressure based viscosity: Jameson-Schmidt-Turkel (JST), Hassan-Morgan-Peraire (HMP) and Swanson-Turkel (ST).
*/
template<>
InputParameters validParams<EelPressureBasedVisc>()
{
  InputParameters params = validParams<Kernel>();
    // Aux variable:
    params.addRequiredCoupledVar("pressure", "pressure variables");
    // PPS names:
    params.addParam<std::string>("average_pressure_pps", "none", "name of the pps computing the average pressure.");
    params.addParam<std::string>("average_grad_pressure_pps", "none", "name of the pps computing the average pressure gradient.");
    // Parameter:
    params.addParam<Real>("alpha", 1., "coefficient alpha used in the definition of the pressure based viscosity: (0,1)");
    // Name of the pressure based viscosity type:
    params.addParam<std::string>("viscosity_name", "JST", "Name of the pressure-based viscosity to use.");
    // Userobject:
    params.addRequiredParam<UserObjectName>("eos", "Equation of state");
  return params;
}

EelPressureBasedVisc::EelPressureBasedVisc(const std::string & name,
                       InputParameters parameters) :
  Kernel(name, parameters),
// Name of the pressure-based viscosity type:
    _visc_name(getParam<std::string>("viscosity_name")),
    _visc_type("JST, HMP, ST, INVALID", "INVALID"),
    // Coupled aux variables
    _grad_press(coupledGradient("pressure")),
    // Name of the pps:
    _average_press_nm(getParam<std::string>("average_pressure_pps")),
    _average_grad_press_nm(getParam<std::string>("average_grad_pressure_pps")),
    // Parameter:
    _alpha(getParam<Real>("alpha"))
{
    _visc_type = _visc_name;
    // Check for value of alpha:
    if (_alpha < 0 || _alpha > 1) {
        mooseError("The value of alpha must be positive and smaller than one.");
    }
    // Warning:
    if (!isCoupled("viscosity_name")) {
        std::cout<<"WARNING:the viscosity type is not initialized. Default type: Jameson-Schmidt-Turket"<<std::endl;
    }
     //Check for coupling of one pps:
    //if ( isCoupled("average_pressure_pps")!=true && isCoupled("average_grad_pressure_pps")!=true ) {
    //    mooseError("ERROR: at leat one postprocessor must be initialized.");
    //}
}

Real EelPressureBasedVisc::computeQpResidual()
{
    Real _h = _current_elem->hmin();
    Real _eps = std::sqrt(std::numeric_limits<Real>::min());
    
    // Initialyze the pps:
    Real _average_press = getPostprocessorValueByName(_average_press_nm);
    Real _average_grad_press = getPostprocessorValueByName(_average_grad_press_nm);
    
    // Compute denominator:
    Real _den = 0.;
    switch (_visc_type) {
        case JST:
            _den = _average_press;
            break;
        case HMP:
            _den = (1-_alpha)*_h*_average_grad_press;
            break;
        case ST:
            _den = _alpha*_h*_average_grad_press + (1-_alpha)*_average_press;
        default:
            mooseError("Invalid viscosity type.");
            break;
    }
    //std::cout<<_den<<std::endl;
    //std::cout<<_grad_press[_qp](0)<<std::endl;
    // Return the weak form:
    return _u[_qp]*_test[_i][_qp] + _h*_grad_press[_qp]*_grad_test[_i][_qp] / _den;
}

Real EelPressureBasedVisc::computeQpJacobian()
{
  return ( 0 );
}

Real EelPressureBasedVisc::computeQpOffDiagJacobian( unsigned int _jvar)
{ 
    return ( 0 );
}
