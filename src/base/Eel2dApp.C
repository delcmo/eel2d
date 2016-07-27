#include "Eel2dApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

// 1-D kernels
#include "OneDMass.h"
#include "OneDMomentum.h"
#include "OneDEnergy.h"
#include "OneDStabilization.h"

// 1-D auxkernels
#include "OneDPressureAux.h"
#include "OneDVelocityAux.h"
#include "OneDDensityAux.h"
#include "OneDInternalEnergyAux.h"
#include "OneDFirstOrderViscosityCoefficient.h"

// 1-D userobjects
#include "OneDEquationOfState.h"
#include "OneDStiffenedGasEquationOfState.h"
#include "OneDEntropyViscosityMethod.h"
#include "OneDJumpInterfaceGradient.h"

// 1-D postprocessors
#include "OneDTimeStepCFL.h"

// 1-D ics
#include "OneDInitialConditionsPressTempVel.h"

// 1-D bcs
#include "OneDMomentumWallBC.h"

// Kernels
#include "EelTimeDerivative.h"
#include "EelMass.h"
#include "EelMomentum.h"
#include "EelEnergy.h"
#include "EelArtificialVisc.h"
#include "EelCMethod.h"
#include "EelPressureBasedVisc.h"
#include "EelFannoFlow.h"
#include "LowMachPreconditioner.h"
#include "MassMatrix.h"
// Auxkernels
#include "AreaAux.h"
#include "PressureAux.h"
#include "DensityAux.h"
#include "MachNumberAux.h"
#include "VelocityAux.h"
#include "TotalEnergyAux.h"
#include "InternalEnergyAux.h"
#include "TemperatureAux.h"
#include "NormVectorAux.h"
#include "DotProductAux.h"
#include "VariableTimesAreaAux.h"
// Materials
#include "ComputeViscCoeff.h"
// BCs
#include "EelStagnationPandTBC.h"
#include "EelStaticPandTBC.h"
#include "EelHRhoUBC.h"
#include "EelMomentumHRhoUDBC.h"
#include "EelWallBC.h"
#include "EelInfiniteBC.h"
#include "EelDBC.h"
#include "EelMassInflowBC.h"
#include "ScalarDirichletBC.h"
#include "EelFluxBC.h"
#include "MomentumFreeSlipBC.h"
// ICs
#include "ConservativeVariables1DXIC.h"
#include "ConservativeVariables1DYIC.h"
#include "ConservativeVariables2DIC.h"
#include "FourSquaresIC2D.h"
#include "DoubleMachReflectionIC.h"
//Functions
#include "AreaFunction.h"
#include "AreaFunction2D.h"
#include "ExactSolAreaVariable.h"
// PPs
#include "ElementMaxGradient.h"
#include "MaxAbsoluteValuePPS.h"
#include "NodalMassConservationPPS.h"
#include "InviscidTimeStepLimit.h"
#include "ElementAverageMultipleValues.h"
#include "ElementIntegralMultipleVariablesPostprocessor.h"
#include "ElementAverageAbsValue.h"
#include "ElementIntegralAbsVariablePostprocessor.h"
#include "NodalMinValue.h"
#include "NodalMinMultipleValues.h"
#include "NodalMaxMultipleValues.h"
#include "ElementMaxDuDtValue.h"
#include "ElementL1Error.h"

// UserObjects
#include "EquationOfState.h"
#include "StiffenedGasEquationOfState.h"
#include "TaitEOS.h"
#include "ModifiedTaitEOS.h"
#include "JumpGradientInterface.h"
#include "SmoothFunction.h"

template<>
InputParameters validParams<Eel2dApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

Eel2dApp::Eel2dApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  Eel2dApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  Eel2dApp::associateSyntax(_syntax, _action_factory);
}

Eel2dApp::~Eel2dApp()
{
}

// External entry point for dynamic application loading
extern "C" void Eel2dApp__registerApps() { Eel2dApp::registerApps(); }
void
Eel2dApp::registerApps()
{
  registerApp(Eel2dApp);
}

// External entry point for dynamic object registration
extern "C" void Eel2dApp__registerObjects(Factory & factory) { Eel2dApp::registerObjects(factory); }
void
Eel2dApp::registerObjects(Factory & factory)
{
  // 1-D kernels
  registerKernel(OneDMass);
  registerKernel(OneDMomentum);
  registerKernel(OneDEnergy);
  registerKernel(OneDStabilization);
  
  // 1-D auxkernels
  registerAux(OneDPressureAux);
  registerAux(OneDVelocityAux);
  registerAux(OneDDensityAux);
  registerAux(OneDInternalEnergyAux);
  registerAux(OneDFirstOrderViscosityCoefficient);
  registerAux(OneDEntropyViscosityMethod);
  
  // 1-D userobjects
  registerUserObject(OneDEquationOfState);
  registerUserObject(OneDStiffenedGasEquationOfState);
  registerUserObject(OneDJumpInterfaceGradient);
  
  // 1-D postprocessors
  registerPostprocessor(OneDTimeStepCFL);
  
  // 1-D ics
  registerInitialCondition(OneDInitialConditionsPressTempVel);
  
  // 1-D bcs
  registerBoundaryCondition(OneDMomentumWallBC);
  
  // Kernels
  registerKernel(EelTimeDerivative);
  registerKernel(EelMass);
  registerKernel(EelMomentum);
  registerKernel(EelEnergy);
  registerKernel(EelArtificialVisc);
  registerKernel(EelCMethod);
  registerKernel(EelPressureBasedVisc);
  registerKernel(EelFannoFlow);
  registerKernel(LowMachPreconditioner);
  registerKernel(MassMatrix);
  
  // Auxkernels
  registerAux(AreaAux);
  registerAux(PressureAux);
  registerAux(DensityAux);
  registerAux(MachNumberAux);
  registerAux(VelocityAux);
  registerAux(TotalEnergyAux);
  registerAux(InternalEnergyAux);
  registerAux(TemperatureAux);
  registerAux(NormVectorAux);
  registerAux(DotProductAux);
  registerAux(VariableTimesAreaAux);
  // Materials
  registerMaterial(ComputeViscCoeff);
  // BCs
  registerBoundaryCondition(EelStagnationPandTBC);
  registerBoundaryCondition(EelStaticPandTBC);
  registerBoundaryCondition(EelHRhoUBC);
  registerBoundaryCondition(EelMomentumHRhoUDBC);
  registerBoundaryCondition(EelWallBC);
  registerBoundaryCondition(EelInfiniteBC);
  registerBoundaryCondition(EelDBC);
  registerBoundaryCondition(EelMassInflowBC);
  registerBoundaryCondition(ScalarDirichletBC);
  registerBoundaryCondition(EelFluxBC);
  registerBoundaryCondition(MomentumFreeSlipBC);
  // ICs
  registerInitialCondition(ConservativeVariables1DXIC);
  registerInitialCondition(ConservativeVariables1DYIC);
  registerInitialCondition(ConservativeVariables2DIC);
  registerInitialCondition(FourSquaresIC2D);
  registerInitialCondition(DoubleMachReflectionIC);
  // Functions
  registerFunction(AreaFunction);
  registerFunction(AreaFunction2D);
  registerFunction(ExactSolAreaVariable);
  // PPs
  registerPostprocessor(ElementMaxGradient);
  registerPostprocessor(MaxAbsoluteValuePPS);
  registerPostprocessor(NodalMassConservationPPS);
  registerPostprocessor(InviscidTimeStepLimit);
  registerPostprocessor(ElementAverageMultipleValues);
  registerPostprocessor(ElementIntegralMultipleVariablesPostprocessor);
  registerPostprocessor(ElementAverageAbsValue);
  registerPostprocessor(ElementIntegralAbsVariablePostprocessor);
  registerPostprocessor(NodalMinValue);
  registerPostprocessor(NodalMinMultipleValues);
  registerPostprocessor(NodalMaxMultipleValues);
  registerPostprocessor(ElementMaxDuDtValue);
  registerPostprocessor(ElementL1Error);
  //UserObjects
  registerUserObject(EquationOfState);
  registerUserObject(StiffenedGasEquationOfState);
  registerUserObject(TaitEOS);
  registerUserObject(ModifiedTaitEOS);
  registerUserObject(JumpGradientInterface);
  registerUserObject(SmoothFunction);
}

// External entry point for dynamic syntax association
extern "C" void Eel2dApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { Eel2dApp::associateSyntax(syntax, action_factory); }
void
Eel2dApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
