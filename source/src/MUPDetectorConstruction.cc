//------------------------------------------------------------------------------
#include "MUPDetectorConstruction.hh"
//------------------------------------------------------------------------------
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
//------------------------------------------------------------------------------
MUPDetectorConstruction::MUPDetectorConstruction()
: G4VUserDetectorConstruction(),
  fLV00(0), fLV01(0), fLV02(0), fLV03(0), fLV04(0), fLV05(0), fLV06(0), fLV07(0)
{ }
//------------------------------------------------------------------------------
MUPDetectorConstruction::~MUPDetectorConstruction(){ }
//------------------------------------------------------------------------------
G4VPhysicalVolume* MUPDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;
  G4NistManager* nist = G4NistManager::Instance();

  G4String name;
  //G4double z, a, density;
  //G4double temperature, pressure;
  //G4int ncomponents, natoms;
  //G4double fractionmass;

  // Elements
  //G4Element* H  = new G4Element("Hydrogen", "H",  z=  1, a= 1.008*g/mole);
  //#G4Element* C  = new G4Element("Carbon",   "C",  z=  6, a= 12.00*g/mole);
  //G4Element* N  = new G4Element("Nitrogen", "N",  z=  7, a= 14.01*g/mole);
  //G4Element* O  = new G4Element("Oxygen",   "O",  z=  8, a= 16.00*g/mole);
  //G4Element* Al = new G4Element("Aluminium","Al", z= 13, a= 26.9815385*g/mole);
  //G4Element* Ar = new G4Element("Argon",    "Ar", z= 18, a= 39.95*g/mole);
  //G4Element* Cu = new G4Element("Copper",   "Cu", z= 29, a= 63.546*g/mole);

  //G4Material* scinc = new G4Material(name="scinc", density = 1.032*g/cm3, ncomponents=2);
  //scinc->AddElement(C, natoms=9);
  //scinc->AddElement(H, natoms=10);

  //Gases
  //G4Material* CH4Gas = new G4Material(name="CH4Gas",density=13.661*kg/m3,ncomponents=2);
  //CH4Gas->AddElement(H,4);
  //CH4Gas->AddElement(C,1);
  //G4Material *ArGas   = new G4Material("ArGas"  , 18, 39.948*g/mole, 33.213 *kg/m3 );
  // Use 95% Ar, 5% Methane for electron detector gas. Percentage per volume
  //G4Material* ArCH4 = new G4Material(name="ArCH4"  , density = 32.2354*kg/m3, ncomponents=2);
  //ArCH4->AddMaterial (  ArGas,  fractionmass = 0.978811);
  //ArCH4->AddMaterial( CH4Gas,  fractionmass = 0.021189);
  //Solids
  //G4Material *SiSolid = new G4Material("SiSolid", 14, 28.0855   *g/mole,  2.33  * g/cm3 );
  //G4Material *AlSolid = new G4Material("AlSolid", 13, 26.9815385*g/mole,  2.700 * g/cm3 );
  //G4Material *CuSolid = new G4Material("CuSolid", 29, 63.543    *g/mole,  8.96  * g/cm3 );
  //G4Material* Mylar = new G4Material(name="Mylar", 1.39*g/cm3, 3);
  //Mylar->AddElement(O,2);
  //Mylar->AddElement(C,5);
  //Mylar->AddElement(H,4);

  //G4Material* CarbonFiber = new G4Material(name="CarbonFiber",0.145*g/cm3, 1);
  //CarbonFiber->AddElement(C,1);


//------------------------------------------
//   World
//------------------------------------------
  G4double w_xy =   220.0*mm;
  G4double w_z  = 12600.0*mm;

  G4Material* w_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* w_mat = nist->FindOrBuildMaterial("G4_He");

//  bool NoMaterial = true ;
//  G4Material* no_mat = nist->FindOrBuildMaterial("G4_Galactic");

//------------------------------------------
//   Si layers
//------------------------------------------

  // Geometrical parameters of Si layers
  G4double l_xy  =  200.000*mm;
  G4double lSi_z =    0.250*mm;
  // z-pozitiion of Si layers
  G4double l00_z = -5825.000*mm + 0.5 * lSi_z;
  G4double l01_z = - 825.000*mm + 0.5 * lSi_z;
  G4double l02_z =   825.000*mm - 0.5 * lSi_z;
  G4double l03_z =  5825.000*mm - 0.5 * lSi_z;
  G4double l04_z = -5900.000*mm + 0.5 * lSi_z;
  G4double l05_z = - 900.000*mm + 0.5 * lSi_z;
  G4double l06_z =   900.000*mm - 0.5 * lSi_z;
  G4double l07_z =  5900.000*mm - 0.5 * lSi_z;

//  G4double l00_z = -5850.000*mm + 0.5 * lSi_z;
//  G4double l01_z = - 850.000*mm + 0.5 * lSi_z;
//  G4double l02_z =   850.000*mm - 0.5 * lSi_z;
//  G4double l03_z =  5850.000*mm - 0.5 * lSi_z;

  //G4Material* steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* SiSolid = nist->FindOrBuildMaterial("G4_Si");


//------------------------------------------
// H_2 gas, 20 atm.
//------------------------------------------

  G4double lUNIT_z   = 400.0*mm; // length of one TPC unit

  G4double lH2_z =   lUNIT_z*2 ; // 2 anodes (1 cathode in the center)

  // 20 atm --> 1.6347 kg/m3
  G4Material *H2Gas = new G4Material("H2Gas", 1, 1.008*g/mole, 1.6347*kg/m3 );

//------------------------------------------
// Be windows
//------------------------------------------
  //G4Material *BeSolid = new G4Material("BeSolid",  4,  9.01218  *g/mole,  1.848 * g/cm3 );
  G4Material* BeSolid = nist->FindOrBuildMaterial("G4_Be");


  G4double rBe_in  = 29.*mm;
  G4double rBe_out = 30.*mm;
  G4double dBeTPC  = 20.*mm;

  G4double l20_z = -0.5*lH2_z - dBeTPC - rBe_out;
  G4double l21_z =  0.5*lH2_z + dBeTPC + rBe_out;

//------------------------------------------
// Anode + Cathode + Grid
//------------------------------------------

  G4double ll_xy =  199.000*mm;


  G4Material* AlSolid = nist->FindOrBuildMaterial("G4_Be");
  G4Material* CuSolid = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* WSolid  = nist->FindOrBuildMaterial("G4_W" );
  G4Material* Kapton  = nist->FindOrBuildMaterial("G4_KAPTON" );

  G4double lKa_z = 0.050*mm;
  G4double lCu_z = 0.010*mm;
  G4double lAl_z = 0.050*mm;
  G4double lGAP_z = 10.0*mm;

  G4double lW_z  = (3.14159265*0.05*0.05) * mm; // grid 1 mm / step, diameter 100um / 1 direction
//  G4double lW_z  = (3.14159265*0.025*0.025) * mm; // grid 1 mm / step, diameter 100um / 1 direction

  G4double l40_z = -0.5*lH2_z + 0.5*lKa_z                ;
  G4double l41_z =  0.5*lH2_z - 0.5*lKa_z                ;

  G4double l50_z = -0.5*lH2_z + lKa_z + 0.5*lCu_z                ;
  G4double l51_z =  0.5*lH2_z - lKa_z - 0.5*lCu_z                ;

  G4double l60_z = -0.5*lH2_z + lKa_z + lCu_z + lGAP_z + 0.5*lW_z                ;
  G4double l61_z =  0.5*lH2_z - lKa_z - lCu_z - lGAP_z - 0.5*lW_z                ;

  G4double l70_z =  0.0*mm; // Just one cathode in the center of TPC

//=====================================================================================

  G4Box* solidWorld = new G4Box("World", 0.5*w_xy, 0.5*w_xy, 0.5*w_z);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, w_mat, "World");

  // LVs
  G4Box* solidLV00 = new G4Box("LV00", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV01 = new G4Box("LV01", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV02 = new G4Box("LV02", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV03 = new G4Box("LV03", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV04 = new G4Box("LV04", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV05 = new G4Box("LV05", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV06 = new G4Box("LV06", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV07 = new G4Box("LV07", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);

  G4Box* solidLV10 = new G4Box("LV10", 0.5*l_xy, 0.5*l_xy, 0.5*lH2_z);

  G4Sphere* solidLV20 = new G4Sphere( "LV20", rBe_in, rBe_out, 0.0*deg, 360.0 *deg,  0.0*deg,  90.0*deg);
  G4Sphere* solidLV21 = new G4Sphere( "LV21", rBe_in, rBe_out, 0.0*deg, 360.0 *deg, 90.0*deg, 180.0*deg);


  G4Box* solidLV40 = new G4Box("LV40", 0.5*ll_xy, 0.5*ll_xy, 0.5*lKa_z);
  G4Box* solidLV41 = new G4Box("LV41", 0.5*ll_xy, 0.5*ll_xy, 0.5*lKa_z);

  G4Box* solidLV50 = new G4Box("LV50", 0.5*ll_xy, 0.5*ll_xy, 0.5*lCu_z);
  G4Box* solidLV51 = new G4Box("LV51", 0.5*ll_xy, 0.5*ll_xy, 0.5*lCu_z);

  G4Box* solidLV60 = new G4Box("LV60", 0.5*ll_xy, 0.5*ll_xy, 0.5*lW_z );
  G4Box* solidLV61 = new G4Box("LV61", 0.5*ll_xy, 0.5*ll_xy, 0.5*lW_z );

  G4Box* solidLV70 = new G4Box("LV70", 0.5*ll_xy, 0.5*ll_xy, 0.5*lAl_z);


  G4LogicalVolume* logicLV00 = new G4LogicalVolume(solidLV00 , SiSolid, "LV00");
  G4LogicalVolume* logicLV01 = new G4LogicalVolume(solidLV01 , SiSolid, "LV01");
  G4LogicalVolume* logicLV02 = new G4LogicalVolume(solidLV02 , SiSolid, "LV02");
  G4LogicalVolume* logicLV03 = new G4LogicalVolume(solidLV03 , SiSolid, "LV03");
  G4LogicalVolume* logicLV04 = new G4LogicalVolume(solidLV04 , SiSolid, "LV04");
  G4LogicalVolume* logicLV05 = new G4LogicalVolume(solidLV05 , SiSolid, "LV05");
  G4LogicalVolume* logicLV06 = new G4LogicalVolume(solidLV06 , SiSolid, "LV06");
  G4LogicalVolume* logicLV07 = new G4LogicalVolume(solidLV07 , SiSolid, "LV07");
//---
  G4LogicalVolume* logicLV10 = new G4LogicalVolume(solidLV10 , H2Gas  , "LV10");
//  G4LogicalVolume* logicLV10 = new G4LogicalVolume(solidLV10 , w_mat  , "LV10");
  G4LogicalVolume* logicLV20 = new G4LogicalVolume(solidLV20 , BeSolid, "LV20");
  G4LogicalVolume* logicLV21 = new G4LogicalVolume(solidLV21 , BeSolid, "LV21");
  G4LogicalVolume* logicLV40 = new G4LogicalVolume(solidLV40 ,  Kapton, "LV40");
  G4LogicalVolume* logicLV41 = new G4LogicalVolume(solidLV41 ,  Kapton, "LV41");
  G4LogicalVolume* logicLV50 = new G4LogicalVolume(solidLV50 , CuSolid, "LV50");
  G4LogicalVolume* logicLV51 = new G4LogicalVolume(solidLV51 , CuSolid, "LV51");
  G4LogicalVolume* logicLV60 = new G4LogicalVolume(solidLV60 , CuSolid, "LV60");
  G4LogicalVolume* logicLV61 = new G4LogicalVolume(solidLV61 , CuSolid, "LV61");
  G4LogicalVolume* logicLV70 = new G4LogicalVolume(solidLV70 , BeSolid, "LV70");

  //G4LogicalVolume* logicLV00 = new G4LogicalVolume(solidLV00 , w_mat, "LV00");
  //G4LogicalVolume* logicLV01 = new G4LogicalVolume(solidLV01 , w_mat, "LV01");
  //G4LogicalVolume* logicLV02 = new G4LogicalVolume(solidLV02 , w_mat, "LV02");
  //G4LogicalVolume* logicLV03 = new G4LogicalVolume(solidLV03 , w_mat, "LV03");
  //G4LogicalVolume* logicLV04 = new G4LogicalVolume(solidLV04 , w_mat, "LV04");
  //G4LogicalVolume* logicLV05 = new G4LogicalVolume(solidLV05 , w_mat, "LV05");
  //G4LogicalVolume* logicLV06 = new G4LogicalVolume(solidLV06 , w_mat, "LV06");
  //G4LogicalVolume* logicLV07 = new G4LogicalVolume(solidLV07 , w_mat, "LV07");
  //G4LogicalVolume* logicLV10 = new G4LogicalVolume(solidLV10 , w_mat, "LV10");
  //G4LogicalVolume* logicLV20 = new G4LogicalVolume(solidLV20 , w_mat, "LV20");
  //G4LogicalVolume* logicLV21 = new G4LogicalVolume(solidLV21 , w_mat, "LV21");
  //G4LogicalVolume* logicLV40 = new G4LogicalVolume(solidLV40 , w_mat, "LV40");
  //G4LogicalVolume* logicLV41 = new G4LogicalVolume(solidLV41 , w_mat, "LV41");
  //G4LogicalVolume* logicLV50 = new G4LogicalVolume(solidLV50 , w_mat, "LV50");
  //G4LogicalVolume* logicLV51 = new G4LogicalVolume(solidLV51 , w_mat, "LV51");
  //G4LogicalVolume* logicLV60 = new G4LogicalVolume(solidLV60 , w_mat, "LV60");
  //G4LogicalVolume* logicLV63 = new G4LogicalVolume(solidLV63 , w_mat, "LV63");
  //G4LogicalVolume* logicLV70 = new G4LogicalVolume(solidLV70 , w_mat, "LV70");


  G4ThreeVector l00_pos; l00_pos.set( 0, 0, l00_z ); // Si 1
  G4ThreeVector l01_pos; l01_pos.set( 0, 0, l01_z ); // Si 2
  G4ThreeVector l02_pos; l02_pos.set( 0, 0, l02_z ); // Si 3
  G4ThreeVector l03_pos; l03_pos.set( 0, 0, l03_z ); // Si 4
  G4ThreeVector l04_pos; l04_pos.set( 0, 0, l04_z ); // Si 5
  G4ThreeVector l05_pos; l05_pos.set( 0, 0, l05_z ); // Si 6
  G4ThreeVector l06_pos; l06_pos.set( 0, 0, l06_z ); // Si 7
  G4ThreeVector l07_pos; l07_pos.set( 0, 0, l07_z ); // Si 8

  G4ThreeVector l10_pos; l10_pos.set( 0, 0, 0     ); // H2 gas   -- TPC volume
  G4ThreeVector l20_pos; l20_pos.set( 0, 0, l20_z ); // Be       -- entrance window
  G4ThreeVector l21_pos; l21_pos.set( 0, 0, l21_z ); // Be       -- exit window
  G4ThreeVector l40_pos; l40_pos.set( 0, 0, l40_z ); // Kapton 1 -- anode
  G4ThreeVector l41_pos; l41_pos.set( 0, 0, l41_z ); // Kapton 2 -- anode
  G4ThreeVector l50_pos; l50_pos.set( 0, 0, l50_z ); // Cu 1     -- anode
  G4ThreeVector l51_pos; l51_pos.set( 0, 0, l51_z ); // Cu 2     -- anode
  G4ThreeVector l60_pos; l60_pos.set( 0, 0, l60_z ); // W 1      -- grid
  G4ThreeVector l61_pos; l61_pos.set( 0, 0, l61_z ); // W 2      -- grid
  G4ThreeVector l70_pos; l70_pos.set( 0, 0, l70_z ); // Al 1     -- cathode

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0, G4ThreeVector(), logicWorld,
                         "World", 0, false, checkOverlaps);

  // - Si Trackers
  new G4PVPlacement(0, l00_pos, logicLV00, "LV00", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l01_pos, logicLV01, "LV01", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l02_pos, logicLV02, "LV02", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l03_pos, logicLV03, "LV03", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l04_pos, logicLV04, "LV04", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l05_pos, logicLV05, "LV05", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l06_pos, logicLV06, "LV06", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l07_pos, logicLV07, "LV07", logicWorld, false, 0, checkOverlaps);
  // - H2 TPC
  new G4PVPlacement(0, l10_pos, logicLV10, "LV10", logicWorld, false, 0, checkOverlaps);
  // - Be windows 
  new G4PVPlacement(0, l20_pos, logicLV20, "LV20", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l21_pos, logicLV21, "LV21", logicWorld, false, 0, checkOverlaps);
  // Kapton -- anode
  new G4PVPlacement(0, l40_pos, logicLV40, "LV40", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l41_pos, logicLV41, "LV41", logicLV10, false, 0, checkOverlaps);
  // Cu -- anode
  new G4PVPlacement(0, l50_pos, logicLV50, "LV50", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l51_pos, logicLV51, "LV51", logicLV10, false, 0, checkOverlaps);
  // W -- grid
  new G4PVPlacement(0, l60_pos, logicLV60, "LV60", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l61_pos, logicLV61, "LV61", logicLV10, false, 0, checkOverlaps);
  // Al -- cathode
  new G4PVPlacement(0, l70_pos, logicLV70, "LV70", logicLV10, false, 0, checkOverlaps);


  fLV00 = logicLV00;
  fLV01 = logicLV01;
  fLV02 = logicLV02;
  fLV03 = logicLV03;
  fLV04 = logicLV04;
  fLV05 = logicLV05;
  fLV06 = logicLV06;
  fLV07 = logicLV07;

  return physWorld;
}
//------------------------------------------------------------------------------
