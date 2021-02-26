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

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGenerator::PrimaryGenerator()
: G4VPrimaryGenerator()
{ }

PrimaryGenerator::~PrimaryGenerator()
{ }

void PrimaryGenerator::GeneratePrimaryVertex(G4Event* event)
{

//  G4ParticleDefinition* particleDefMu = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
  G4ParticleDefinition* particleDefMu = G4ParticleTable::GetParticleTable()->FindParticle("mu+");

  G4PrimaryParticle* particle1;
//  G4PrimaryParticle* particle2;

  particle1 = new G4PrimaryParticle(particleDefMu);
//  particle2 = new G4PrimaryParticle(particleDefMu);

  G4double p_mu = 100.*GeV;

 G4double pos  = -6299.0*mm; // for reso
//  G4double pos  = 1075.0*mm; // for reso
// G4double pos  =  -885.0*mm; // for thetaX LONG
// G4double pos  =  -(885.0-425.0)*mm; // for thetaX SHORT
//   G4double pos  =   790.0*mm; //
// G4double pos  =   750.0*mm; //

//  double theta = 0.0;
//  double theta = 0.00011;
//  double theta = 0.00033;
//  double theta = 0.002;

  fXpos = 0.*mm;  fYpos = 0.*mm;  fZpos = pos;
  if( false ){
    fXpos = (G4UniformRand() - 0.5)*29.*mm;
    fYpos = (G4UniformRand() - 0.5)*29.*mm;
//    fZpos = (380*G4UniformRand() + 10.)*mm;
//    fZpos = (380*G4UniformRand() + 35.)*mm;
    while( fXpos*fXpos + fYpos*fYpos > 29.*29. ){
      fXpos = (G4UniformRand() - 0.5)*29.*mm;
      fYpos = (G4UniformRand() - 0.5)*29.*mm;
    }
  }

  G4ThreeVector positionB( fXpos, fYpos, fZpos );
//  G4ThreeVector positionB( 0, 20.0*mm, pos ); // check edge of Be window
//  G4ThreeVector positionB( 0, 29.0*mm, pos ); // check edge of Be window

  particle1->SetMomentum( 0, 0,  p_mu );
//  particle1->SetMomentum( 0, theta*p_mu,  p_mu );
//  particle2->SetMomentum( 0,          0, -p_mu );

  G4PrimaryVertex* vertexB = new G4PrimaryVertex(positionB, 0);

  vertexB->SetPrimary(particle1);
//  vertexB->SetPrimary(particle2);
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

