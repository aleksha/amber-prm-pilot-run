#ifndef MUPRunAction_h
#define MUPRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class

class MUPRunAction : public G4UserRunAction
{
  public:
    MUPRunAction();
    virtual ~MUPRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif

