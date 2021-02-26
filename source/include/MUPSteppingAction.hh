#ifndef MUPSteppingAction_h
#define MUPSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class MUPEventAction;

class G4LogicalVolume;

/// Stepping action class
///

class MUPSteppingAction : public G4UserSteppingAction
{
  public:
    MUPSteppingAction(MUPEventAction* eventAction);
    virtual ~MUPSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    MUPEventAction*  fEventAction;
    std::ofstream myOUT;

    G4LogicalVolume* fLV00;
    G4LogicalVolume* fLV01;
    G4LogicalVolume* fLV02;
    G4LogicalVolume* fLV03;
};
//------------------------------------------------------------------------------
#endif
