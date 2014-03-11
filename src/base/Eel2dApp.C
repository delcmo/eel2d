#include "Eel2dApp.h"
#include "Eel2d.h"
#include "Moose.h"
//#include "Elk.h"

template<>
InputParameters validParams<Eel2dApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

Eel2dApp::Eel2dApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(libMesh::processor_id());
  
  Moose::registerObjects(_factory);
  //Elk::registerObjects(_factory);
  Eel2d::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  //Elk::associateSyntax(_syntax, _action_factory);
  Eel2d::associateSyntax(_syntax, _action_factory);
}

Eel2dApp::~Eel2dApp()
{
}

