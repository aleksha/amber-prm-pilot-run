#ifndef MUPEventAction_h
#define MUPEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class MUPRunAction;

/// Event action class
///

class MUPEventAction : public G4UserEventAction
{
  public:
    MUPEventAction(MUPRunAction* runAction);
    virtual ~MUPEventAction();
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
  private:
    MUPRunAction* fRunAction;
};
//------------------------------------------------------------------------------
#endif

