#include "MUPPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "G4VPrimaryGenerator.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


//==============================================================================
// HERE IS PRIMARY GENERATOR CLASS FIRST
//==============================================================================


class PrimaryGenerator : public G4VPrimaryGenerator
{
  public:
    PrimaryGenerator();
   ~PrimaryGenerator();

  public:
    virtual void GeneratePrimaryVertex(G4Event*);

  private:
    G4double fXpos, fYpos, fZpos;      //solid angle
    double fX, fY, fZ, fAX, fAY, fMom;
    int pcode;

    std::ifstream in_file ;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGenerator::PrimaryGenerator()
: G4VPrimaryGenerator()
{ 
  in_file.open("input_g4.txt", std::ios::in);
}

PrimaryGenerator::~PrimaryGenerator()
{ 
  in_file.close();
}

void PrimaryGenerator::GeneratePrimaryVertex(G4Event* event)
{
  in_file  >> pcode >> fX >> fY >> fZ >> fAX >> fAY >> fMom;

  G4ParticleDefinition* particleDefGamma    = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  G4ParticleDefinition* particleDefMup      = G4ParticleTable::GetParticleTable()->FindParticle("mu+");
  G4ParticleDefinition* particleDefMum      = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
  G4ParticleDefinition* particleDefEm       = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  G4ParticleDefinition* particleDefEp       = G4ParticleTable::GetParticleTable()->FindParticle("e+");
  G4ParticleDefinition* particleDefPim      = G4ParticleTable::GetParticleTable()->FindParticle("pi-");
  G4ParticleDefinition* particleDefPip      = G4ParticleTable::GetParticleTable()->FindParticle("pi+");
  G4ParticleDefinition* particleDefProton   = G4ParticleTable::GetParticleTable()->FindParticle("proton");
  G4ParticleDefinition* particleDefDeuteron = G4ParticleTable::GetParticleTable()->FindParticle("deuteron");  
  G4ParticleDefinition* particleDefAlpha    = G4ParticleTable::GetParticleTable()->FindParticle("alpha");  
  G4PrimaryParticle* particle1;

  switch(pcode) {
    case 22:
      particle1 = new G4PrimaryParticle(particleDefGamma);
      break;    
    case 11:
      particle1 = new G4PrimaryParticle(particleDefEm);
      break;
    case -11:
      particle1 = new G4PrimaryParticle(particleDefEp);
      break;
    case 13:
      particle1 = new G4PrimaryParticle(particleDefMum);
 //     G4cout  << "mu-" << G4endl;
      break;
    case -13:
      particle1 = new G4PrimaryParticle(particleDefMup);
      break;
    case -211:
      particle1 = new G4PrimaryParticle(particleDefPim);
      break;
    case 211:
      particle1 = new G4PrimaryParticle(particleDefPip);
      break;
    case 2212:
      particle1 = new G4PrimaryParticle(particleDefProton);
      break;    
    case 1000010020:
      particle1 = new G4PrimaryParticle(particleDefDeuteron);
      break;
    case 1000020040:
      particle1 = new G4PrimaryParticle(particleDefAlpha);
      break;
    default:
      particle1 = new G4PrimaryParticle(particleDefMum);
      break;    
  }
  
  
  G4double p_mu = fMom*GeV;
  fXpos = fX*mm;  fYpos = fY*mm;  fZpos = fZ*mm;
  G4ThreeVector positionB( fXpos, fYpos, fZpos );

  particle1->SetMomentum( 0.001*fAX*p_mu, 0.001*fAY*p_mu, p_mu );

  G4PrimaryVertex* vertexB = new G4PrimaryVertex(positionB, 0);
  vertexB->SetPrimary(particle1);

  event->AddPrimaryVertex(vertexB);
}

//------------------------------------------------------------------------------
MUPPrimaryGeneratorAction::MUPPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fPrimaryGenerator(0)
{
  fPrimaryGenerator = new PrimaryGenerator();
}
//------------------------------------------------------------------------------
MUPPrimaryGeneratorAction::~MUPPrimaryGeneratorAction(){ delete fPrimaryGenerator; }
//------------------------------------------------------------------------------
void MUPPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fPrimaryGenerator->GeneratePrimaryVertex(anEvent);
}
//------------------------------------------------------------------------------

