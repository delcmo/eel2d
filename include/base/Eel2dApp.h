#ifndef EEL2DAPP_H
#define EEL2DAPP_H

#include "MooseApp.h"

class Eel2dApp;

template<>
InputParameters validParams<Eel2dApp>();

class Eel2dApp : public MooseApp
{
public:
  Eel2dApp(const std::string & name, InputParameters parameters);
  virtual ~Eel2dApp();
};

#endif /* EEL2DAPP_H */
