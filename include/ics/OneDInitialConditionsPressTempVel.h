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

#ifndef ONEDINITIALCONDITIONSPRESSTEMPVEL_H
#define ONEDINITIALCONDITIONSPRESSTEMPVEL_H

// MOOSE Includes
#include "InitialCondition.h"
#include "OneDEquationOfState.h"
#include "AreaFunction.h"

// Forward Declarations
class OneDInitialConditionsPressTempVel;

template<>
InputParameters validParams<OneDInitialConditionsPressTempVel>();

/**
 * OneDInitialConditionsPressTempVel just returns a constant value.
 */
class OneDInitialConditionsPressTempVel : public InitialCondition
{
public:

  /**
   * Constructor: Same as the rest of the MOOSE Objects
   */
  OneDInitialConditionsPressTempVel(const InputParameters & parameters);

  /**
   * The value of the variable at a point.
   *
   * This must be overriden by derived classes.
   */
  virtual Real value(const Point & p);

private:
    // Function are
    Function & _area;
    // Initial conditions for left and right values:
    Real _p_left;
    Real _p_right;
    Real _v_left;
    Real _v_right;
    Real _t_left;
    Real _t_right;
    // Position of the membrane:
    Real _membrane;
    Real _length;
    // Name of the variable:
    std::string _name_var;
    // Equation of state:
    const OneDEquationOfState & _eos;

};

#endif // ONEDINITIALCONDITIONSPRESSTEMPVEL_H
