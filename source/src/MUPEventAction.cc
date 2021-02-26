#include "MUPEventAction.hh"
#include "MUPRunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
//------------------------------------------------------------------------------
MUPEventAction::MUPEventAction(MUPRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}
//------------------------------------------------------------------------------
MUPEventAction::~MUPEventAction(){}
//------------------------------------------------------------------------------
void MUPEventAction::BeginOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
void MUPEventAction::EndOfEventAction(const G4Event*){}
//------------------------------------------------------------------------------
