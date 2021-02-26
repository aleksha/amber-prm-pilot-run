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
  fLV00(0), fLV01(0), fLV02(0), fLV03(0)
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
  G4double w_z  = 15000.0*mm;

  G4Material* w_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* w_mat = nist->FindOrBuildMaterial("G4_He");

//  bool NoMaterial = true ;
//  G4Material* no_mat = nist->FindOrBuildMaterial("G4_Galactic");

//------------------------------------------
//   Si layers
//------------------------------------------

  // Geometrical parameters of Si layers
  G4double l_xy  =  200.000*mm;
  G4double lSi_z =    0.400*mm;


  //G4Material* steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* SiSolid = nist->FindOrBuildMaterial("G4_Si");


//------------------------------------------
// H_2 gas, 20 atm.
//------------------------------------------

  G4double lUNIT_z   = 400.0*mm; // length of one TPC unit
  G4double lCENTER_z =  50.0*mm; // gap between central anodes

  G4double lH2_z = ( lUNIT_z*4 + lCENTER_z );

  // 20 atm --> 1.6347 kg/m3
  G4Material *H2Gas = new G4Material("H2Gas", 1, 1.008*g/mole, 1.6347*kg/m3 );

//------------------------------------------
// Be windows
//------------------------------------------
  //G4Material *BeSolid = new G4Material("BeSolid",  4,  9.01218  *g/mole,  1.848 * g/cm3 );
  G4Material* BeSolid = nist->FindOrBuildMaterial("G4_Be");


  G4double rBe_in  =  29.*mm;
  G4double rBe_out =  30.*mm;
  G4double dBeTPC  = 220.*mm;

  G4double l20_z = -0.5*lH2_z - dBeTPC - rBe_out;
  G4double l21_z =  0.5*lH2_z + dBeTPC + rBe_out;

  // z-pozitiion of Si layers
  G4double dBeSi = 20.*mm + rBe_out;
  G4double l01_z =  l20_z       + 0.5 * lSi_z - dBeSi;
  G4double l00_z = -5000.000*mm + 0.5 * lSi_z + l01_z;
  G4double l02_z =  l21_z       - 0.5 * lSi_z + dBeSi;
  G4double l03_z =  5000.000*mm - 0.5 * lSi_z + l02_z;

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
  G4double l41_z =            - 0.5*lKa_z - 0.5*lCENTER_z;
  G4double l42_z =              0.5*lKa_z + 0.5*lCENTER_z;
  G4double l43_z =  0.5*lH2_z - 0.5*lKa_z                ;

  G4double l50_z = -0.5*lH2_z + lKa_z + 0.5*lCu_z                ;
  G4double l51_z =            - lKa_z - 0.5*lCu_z - 0.5*lCENTER_z;
  G4double l52_z =              lKa_z + 0.5*lCu_z + 0.5*lCENTER_z;
  G4double l53_z =  0.5*lH2_z - lKa_z - 0.5*lCu_z                ;

  G4double l60_z = -0.5*lH2_z + lKa_z + lCu_z + lGAP_z + 0.5*lW_z                ;
  G4double l61_z =            - lKa_z - lCu_z - lGAP_z - 0.5*lW_z - 0.5*lCENTER_z;
  G4double l62_z =              lKa_z + lCu_z + lGAP_z + 0.5*lW_z + 0.5*lCENTER_z;
  G4double l63_z =  0.5*lH2_z - lKa_z - lCu_z - lGAP_z - 0.5*lW_z                ;

  G4double l70_z = -0.25*(lH2_z - lCENTER_z) - 0.5*lCENTER_z;
  G4double l71_z =  0.25*(lH2_z - lCENTER_z) + 0.5*lCENTER_z;

//=====================================================================================

  G4Box* solidWorld = new G4Box("World", 0.5*w_xy, 0.5*w_xy, 0.5*w_z);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, w_mat, "World");

  // LVs
  G4Box* solidLV00 = new G4Box("LV00", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV01 = new G4Box("LV01", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV02 = new G4Box("LV02", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);
  G4Box* solidLV03 = new G4Box("LV03", 0.5*l_xy, 0.5*l_xy, 0.5*lSi_z);

  G4Box* solidLV10 = new G4Box("LV10", 0.5*l_xy, 0.5*l_xy, 0.5*lH2_z);

  G4Sphere* solidLV20 = new G4Sphere( "LV20", rBe_in, rBe_out, 0.0*deg, 360.0 *deg,  0.0*deg,  90.0*deg);
  G4Sphere* solidLV21 = new G4Sphere( "LV21", rBe_in, rBe_out, 0.0*deg, 360.0 *deg, 90.0*deg, 180.0*deg);


  G4Box* solidLV40 = new G4Box("LV40", 0.5*ll_xy, 0.5*ll_xy, 0.5*lKa_z);
  G4Box* solidLV41 = new G4Box("LV41", 0.5*ll_xy, 0.5*ll_xy, 0.5*lKa_z);
  G4Box* solidLV42 = new G4Box("LV42", 0.5*ll_xy, 0.5*ll_xy, 0.5*lKa_z);
  G4Box* solidLV43 = new G4Box("LV43", 0.5*ll_xy, 0.5*ll_xy, 0.5*lKa_z);

  G4Box* solidLV50 = new G4Box("LV50", 0.5*ll_xy, 0.5*ll_xy, 0.5*lCu_z);
  G4Box* solidLV51 = new G4Box("LV51", 0.5*ll_xy, 0.5*ll_xy, 0.5*lCu_z);
  G4Box* solidLV52 = new G4Box("LV52", 0.5*ll_xy, 0.5*ll_xy, 0.5*lCu_z);
  G4Box* solidLV53 = new G4Box("LV53", 0.5*ll_xy, 0.5*ll_xy, 0.5*lCu_z);

  G4Box* solidLV60 = new G4Box("LV60", 0.5*ll_xy, 0.5*ll_xy, 0.5*lW_z );
  G4Box* solidLV61 = new G4Box("LV61", 0.5*ll_xy, 0.5*ll_xy, 0.5*lW_z );
  G4Box* solidLV62 = new G4Box("LV62", 0.5*ll_xy, 0.5*ll_xy, 0.5*lW_z );
  G4Box* solidLV63 = new G4Box("LV63", 0.5*ll_xy, 0.5*ll_xy, 0.5*lW_z );

  G4Box* solidLV70 = new G4Box("LV70", 0.5*ll_xy, 0.5*ll_xy, 0.5*lAl_z);
  G4Box* solidLV71 = new G4Box("LV71", 0.5*ll_xy, 0.5*ll_xy, 0.5*lAl_z);


  G4LogicalVolume* logicLV00 = new G4LogicalVolume(solidLV00 , SiSolid, "LV00");
  G4LogicalVolume* logicLV01 = new G4LogicalVolume(solidLV01 , SiSolid, "LV01");
  G4LogicalVolume* logicLV02 = new G4LogicalVolume(solidLV02 , SiSolid, "LV02");
  G4LogicalVolume* logicLV03 = new G4LogicalVolume(solidLV03 , SiSolid, "LV03");
  G4LogicalVolume* logicLV10 = new G4LogicalVolume(solidLV10 , H2Gas  , "LV10");
//  G4LogicalVolume* logicLV10 = new G4LogicalVolume(solidLV10 , w_mat  , "LV10");
  G4LogicalVolume* logicLV20 = new G4LogicalVolume(solidLV20 , BeSolid, "LV20");
  G4LogicalVolume* logicLV21 = new G4LogicalVolume(solidLV21 , BeSolid, "LV21");
  G4LogicalVolume* logicLV40 = new G4LogicalVolume(solidLV40 ,  Kapton, "LV40");
  G4LogicalVolume* logicLV41 = new G4LogicalVolume(solidLV41 ,  Kapton, "LV41");
  G4LogicalVolume* logicLV42 = new G4LogicalVolume(solidLV42 ,  Kapton, "LV42");
  G4LogicalVolume* logicLV43 = new G4LogicalVolume(solidLV43 ,  Kapton, "LV43");
  G4LogicalVolume* logicLV50 = new G4LogicalVolume(solidLV50 , CuSolid, "LV50");
  G4LogicalVolume* logicLV51 = new G4LogicalVolume(solidLV51 , CuSolid, "LV51");
  G4LogicalVolume* logicLV52 = new G4LogicalVolume(solidLV52 , CuSolid, "LV52");
  G4LogicalVolume* logicLV53 = new G4LogicalVolume(solidLV53 , CuSolid, "LV53");
  G4LogicalVolume* logicLV60 = new G4LogicalVolume(solidLV60 , CuSolid, "LV60");
  G4LogicalVolume* logicLV61 = new G4LogicalVolume(solidLV61 , CuSolid, "LV61");
  G4LogicalVolume* logicLV62 = new G4LogicalVolume(solidLV62 , CuSolid, "LV62");
  G4LogicalVolume* logicLV63 = new G4LogicalVolume(solidLV63 , CuSolid, "LV63");
  G4LogicalVolume* logicLV70 = new G4LogicalVolume(solidLV70 , BeSolid, "LV70");
  G4LogicalVolume* logicLV71 = new G4LogicalVolume(solidLV71 , BeSolid, "LV71");

  //G4LogicalVolume* logicLV00 = new G4LogicalVolume(solidLV00 , w_mat, "LV00");
  //G4LogicalVolume* logicLV01 = new G4LogicalVolume(solidLV01 , w_mat, "LV01");
  //G4LogicalVolume* logicLV02 = new G4LogicalVolume(solidLV02 , w_mat, "LV02");
  //G4LogicalVolume* logicLV03 = new G4LogicalVolume(solidLV03 , w_mat, "LV03");
  //G4LogicalVolume* logicLV10 = new G4LogicalVolume(solidLV10 , w_mat, "LV10");
  //G4LogicalVolume* logicLV20 = new G4LogicalVolume(solidLV20 , w_mat, "LV20");
  //G4LogicalVolume* logicLV21 = new G4LogicalVolume(solidLV21 , w_mat, "LV21");
  //G4LogicalVolume* logicLV40 = new G4LogicalVolume(solidLV40 , w_mat, "LV40");
  //G4LogicalVolume* logicLV41 = new G4LogicalVolume(solidLV41 , w_mat, "LV41");
  //G4LogicalVolume* logicLV42 = new G4LogicalVolume(solidLV42 , w_mat, "LV42");
  //G4LogicalVolume* logicLV43 = new G4LogicalVolume(solidLV43 , w_mat, "LV43");
  //G4LogicalVolume* logicLV50 = new G4LogicalVolume(solidLV50 , w_mat, "LV50");
  //G4LogicalVolume* logicLV51 = new G4LogicalVolume(solidLV51 , w_mat, "LV51");
  //G4LogicalVolume* logicLV52 = new G4LogicalVolume(solidLV52 , w_mat, "LV52");
  //G4LogicalVolume* logicLV53 = new G4LogicalVolume(solidLV53 , w_mat, "LV53");
  //G4LogicalVolume* logicLV60 = new G4LogicalVolume(solidLV60 , w_mat, "LV60");
  //G4LogicalVolume* logicLV61 = new G4LogicalVolume(solidLV61 , w_mat, "LV61");
  //G4LogicalVolume* logicLV62 = new G4LogicalVolume(solidLV62 , w_mat, "LV62");
  //G4LogicalVolume* logicLV63 = new G4LogicalVolume(solidLV63 , w_mat, "LV63");
  //G4LogicalVolume* logicLV70 = new G4LogicalVolume(solidLV70 , w_mat, "LV70");
  //G4LogicalVolume* logicLV71 = new G4LogicalVolume(solidLV71 , w_mat, "LV71");


  G4ThreeVector l00_pos; l00_pos.set( 0, 0, l00_z ); // Si 1
  G4ThreeVector l01_pos; l01_pos.set( 0, 0, l01_z ); // Si 2
  G4ThreeVector l02_pos; l02_pos.set( 0, 0, l02_z ); // Si 3
  G4ThreeVector l03_pos; l03_pos.set( 0, 0, l03_z ); // Si 4
  G4ThreeVector l10_pos; l10_pos.set( 0, 0, 0     ); // H2 gas   -- TPC volume
  G4ThreeVector l20_pos; l20_pos.set( 0, 0, l20_z ); // Be       -- entrance window
  G4ThreeVector l21_pos; l21_pos.set( 0, 0, l21_z ); // Be       -- exit window
  G4ThreeVector l40_pos; l40_pos.set( 0, 0, l40_z ); // Kapton 1 -- anode
  G4ThreeVector l41_pos; l41_pos.set( 0, 0, l41_z ); // Kapton 2 -- anode
  G4ThreeVector l42_pos; l42_pos.set( 0, 0, l42_z ); // Kapton 3 -- anode
  G4ThreeVector l43_pos; l43_pos.set( 0, 0, l43_z ); // Kapton 4 -- anode
  G4ThreeVector l50_pos; l50_pos.set( 0, 0, l50_z ); // Cu 1     -- anode
  G4ThreeVector l51_pos; l51_pos.set( 0, 0, l51_z ); // Cu 2     -- anode
  G4ThreeVector l52_pos; l52_pos.set( 0, 0, l52_z ); // Cu 3     -- anode
  G4ThreeVector l53_pos; l53_pos.set( 0, 0, l53_z ); // Cu 4     -- anode
  G4ThreeVector l60_pos; l60_pos.set( 0, 0, l60_z ); // W 1      -- grid
  G4ThreeVector l61_pos; l61_pos.set( 0, 0, l61_z ); // W 2      -- grid
  G4ThreeVector l62_pos; l62_pos.set( 0, 0, l62_z ); // W 3      -- grid
  G4ThreeVector l63_pos; l63_pos.set( 0, 0, l63_z ); // W 4      -- grid
  G4ThreeVector l70_pos; l70_pos.set( 0, 0, l70_z ); // Al 1     -- cathode
  G4ThreeVector l71_pos; l71_pos.set( 0, 0, l71_z ); // Al 2     -- cathode

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0, G4ThreeVector(), logicWorld,
                         "World", 0, false, checkOverlaps);

  // - Si Trackers
  new G4PVPlacement(0, l00_pos, logicLV00, "LV00", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l01_pos, logicLV01, "LV01", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l02_pos, logicLV02, "LV02", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l03_pos, logicLV03, "LV03", logicWorld, false, 0, checkOverlaps);
  // - H2 TPC
  new G4PVPlacement(0, l10_pos, logicLV10, "LV10", logicWorld, false, 0, checkOverlaps);
  // - Be windows 
  new G4PVPlacement(0, l20_pos, logicLV20, "LV20", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l21_pos, logicLV21, "LV21", logicWorld, false, 0, checkOverlaps);
  // Kapton -- anode
  new G4PVPlacement(0, l40_pos, logicLV40, "LV40", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l41_pos, logicLV41, "LV41", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l42_pos, logicLV42, "LV42", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l43_pos, logicLV43, "LV43", logicLV10, false, 0, checkOverlaps);
  // Cu -- anode
  new G4PVPlacement(0, l50_pos, logicLV50, "LV50", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l51_pos, logicLV51, "LV51", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l52_pos, logicLV52, "LV52", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l53_pos, logicLV53, "LV53", logicLV10, false, 0, checkOverlaps);
  // W -- grid
  new G4PVPlacement(0, l60_pos, logicLV60, "LV60", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l61_pos, logicLV61, "LV61", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l62_pos, logicLV62, "LV62", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l63_pos, logicLV63, "LV63", logicLV10, false, 0, checkOverlaps);
  // Al -- cathode
  new G4PVPlacement(0, l70_pos, logicLV70, "LV70", logicLV10, false, 0, checkOverlaps);
  new G4PVPlacement(0, l71_pos, logicLV71, "LV71", logicLV10, false, 0, checkOverlaps);


  fLV00 = logicLV00;
  fLV01 = logicLV01;
  fLV02 = logicLV02;
  fLV03 = logicLV03;

  return physWorld;
}
//------------------------------------------------------------------------------
