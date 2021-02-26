#ifndef MUPPrimaryGeneratorAction_h
#define MUPPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4Event;
class PrimaryGenerator;

/// The primary generator action class with particle gun.

class MUPPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    MUPPrimaryGeneratorAction();
    virtual ~MUPPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);

  private:
    PrimaryGenerator* fPrimaryGenerator; // pointer a to object of primary gen class

};
//------------------------------------------------------------------------------
#endif
