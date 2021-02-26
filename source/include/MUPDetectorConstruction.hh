#ifndef MUPDetectorConstruction_h
#define MUPDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class MUPDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    MUPDetectorConstruction();
    virtual ~MUPDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetLV00() const { return fLV00; }
    G4LogicalVolume* GetLV01() const { return fLV01; }
    G4LogicalVolume* GetLV02() const { return fLV02; }
    G4LogicalVolume* GetLV03() const { return fLV03; }
    G4LogicalVolume* GetLV04() const { return fLV04; }
    G4LogicalVolume* GetLV05() const { return fLV05; }
    G4LogicalVolume* GetLV06() const { return fLV06; }
    G4LogicalVolume* GetLV07() const { return fLV07; }

  protected:
    G4LogicalVolume*  fLV00;
    G4LogicalVolume*  fLV01;
    G4LogicalVolume*  fLV02;
    G4LogicalVolume*  fLV03;
    G4LogicalVolume*  fLV04;
    G4LogicalVolume*  fLV05;
    G4LogicalVolume*  fLV06;
    G4LogicalVolume*  fLV07;
};

#endif

