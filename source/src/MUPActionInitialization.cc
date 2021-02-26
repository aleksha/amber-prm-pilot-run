//------------------------------------------------------------------------------
#include "MUPActionInitialization.hh"
#include "MUPPrimaryGeneratorAction.hh"
#include "MUPRunAction.hh"
#include "MUPEventAction.hh"
#include "MUPSteppingAction.hh"
//------------------------------------------------------------------------------
MUPActionInitialization::MUPActionInitialization()
 : G4VUserActionInitialization()
{}
//------------------------------------------------------------------------------
MUPActionInitialization::~MUPActionInitialization(){}
//------------------------------------------------------------------------------
void MUPActionInitialization::BuildForMaster() const
{
  MUPRunAction* runAction = new MUPRunAction;
  SetUserAction(runAction);
}
//------------------------------------------------------------------------------
void MUPActionInitialization::Build() const
{
  SetUserAction(new MUPPrimaryGeneratorAction);

  MUPRunAction* runAction = new MUPRunAction;
  SetUserAction(runAction);

  MUPEventAction* eventAction = new MUPEventAction(runAction);
  SetUserAction(eventAction);
  SetUserAction(new MUPSteppingAction(eventAction));
}
//------------------------------------------------------------------------------
