#include "Eel2d.h"
#include "Eel2dApp.h"
#include "Moose.h"
#include "Factory.h"
#include "AppFactory.h"
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

namespace Eel2d
{
  void registerApps()
  {
    registerApp(Eel2dApp);
  }

  void registerObjects(Factory & factory)
  {
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

  void associateSyntax(Syntax & syntax, ActionFactory & action_factory)
  {
  }
}
