#ifndef EEL2D_H
#define EEL2D_H

class Factory;
class ActionFactory;
class Syntax;

namespace Eel2d
{
  /**
   * Register this application and any it depends on.
   */
  void registerApps();

  /**
   * Registers all Kernels and BCs, etc.
   */
  void registerObjects(Factory & factory);

  /**
   * Register syntax and Action objects.
   */
  void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
}

#endif //EEL2D_H
