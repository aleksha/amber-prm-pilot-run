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

  protected:
    G4LogicalVolume*  fLV00;
    G4LogicalVolume*  fLV01;
    G4LogicalVolume*  fLV02;
    G4LogicalVolume*  fLV03;
};

#endif

