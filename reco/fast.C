#include <fstream>
#include <iostream>
#include <iomanip>

#include "fadc.cc"
#include "histo_funcs.cc"

#include "TGraph.h"
#include "TH1F.h"
#include "TH1S.h"
#include "TH2S.h"
#include "TF1.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TVector3.h"
#include "TStyle.h"
#include "TLatex.h"



TH1F* hFADC[9];
TH1F* hDIFF[9];
TH1F* dDIFF[9];
TH1F* sDIFF[9];
TH1F* hTEMP[9];
TH1F* hDEMP[9];

TH1F* tMax[9];
TH1F* tStart[9];
TH1F* tEnergy[9];
TH1F* tTotal;
TH1F* tMeV;
TH1F* tA2;
TH1F* tA3;
TH1F* tA4;
TH1F* tA5;

TH1F* hd1;
TTree* out;

TFile *tfile;





void fast( float z_anod  = -400., bool backwd = true, int Evts=MY_EVTS, bool AddNoise=ADD_NOISE ){


//==============================================================================
// read digitization
//==============================================================================

    int ev, vol;
    double dE,x,y,z,t;
    // initial and final space-time points for a step
    double xi,yi,zi,ti,xf,yf,zf,tf;
    double dx, dy, dz, dt;
    double xd, yd; // smeared by transverse diffusion
    double hyd_dE=0;

    int EVENT=0;
    int tEv=0;
    int nToys=0;

    int fpad,dpad;

    int EvtCntr=0;

    std::ifstream fOUT("../run_prot/tpc.data" , std::ios::in);
    std::ifstream fNOI("../noise/noise.data"  , std::ios::in);

    TString pFADC,pDIFF,pTEMP,pDEMP;
    TString pdDIFF, psDIFF;
    TString pMax, pStart, pEnergy;


    out = new TTree("out","out");

    Float_t energy0; out->Branch("energy0"  ,&energy0 ,"energy0/F" );
    Float_t energy1; out->Branch("energy1"  ,&energy1 ,"energy1/F" );
    Float_t energy2; out->Branch("energy2"  ,&energy2 ,"energy2/F" );
    Float_t energy3; out->Branch("energy3"  ,&energy3 ,"energy3/F" );
    Float_t energy4; out->Branch("energy4"  ,&energy4 ,"energy4/F" );
    Float_t energy5; out->Branch("energy5"  ,&energy5 ,"energy5/F" );
    Float_t energy6; out->Branch("energy6"  ,&energy6 ,"energy6/F" );
    Float_t energy7; out->Branch("energy7"  ,&energy7 ,"energy7/F" );
    Float_t energy8; out->Branch("energy8"  ,&energy8 ,"energy8/F" );
    Float_t energy ; out->Branch("energy"   ,&energy  ,"energy/F"  );

    Bool_t fired0; out->Branch("fired0"  ,&fired0 ,"fired0/B" );
    Bool_t fired1; out->Branch("fired2"  ,&fired1 ,"fired1/B" );
    Bool_t fired2; out->Branch("fired2"  ,&fired2 ,"fired2/B" );
    Bool_t fired3; out->Branch("fired3"  ,&fired3 ,"fired3/B" );
    Bool_t fired4; out->Branch("fired4"  ,&fired4 ,"fired4/B" );
    Bool_t fired5; out->Branch("fired5"  ,&fired5 ,"fired5/B" );
    Bool_t fired6; out->Branch("fired6"  ,&fired6 ,"fired6/B" );
    Bool_t fired7; out->Branch("fired7"  ,&fired7 ,"fired7/B" );
    Bool_t fired8; out->Branch("fired8"  ,&fired8 ,"fired8/B" );

    Float_t start0; out->Branch("start0"  ,&start0 ,"start0/F" );
    Float_t start1; out->Branch("start1"  ,&start1 ,"start1/F" );
    Float_t start2; out->Branch("start2"  ,&start2 ,"start2/F" );
    Float_t start3; out->Branch("start3"  ,&start3 ,"start3/F" );
    Float_t start4; out->Branch("start4"  ,&start4 ,"start4/F" );
    Float_t start5; out->Branch("start5"  ,&start5 ,"start5/F" );
    Float_t start6; out->Branch("start6"  ,&start6 ,"start6/F" );
    Float_t start7; out->Branch("start7"  ,&start7 ,"start7/F" );
    Float_t start8; out->Branch("start8"  ,&start8 ,"start8/F" );

    Float_t peak0; out->Branch("peak0"  ,&peak0 ,"peak0/F" );
    Float_t peak1; out->Branch("peak1"  ,&peak1 ,"peak1/F" );
    Float_t peak2; out->Branch("peak2"  ,&peak2 ,"peak2/F" );
    Float_t peak3; out->Branch("peak3"  ,&peak3 ,"peak3/F" );
    Float_t peak4; out->Branch("peak4"  ,&peak4 ,"peak4/F" );
    Float_t peak5; out->Branch("peak5"  ,&peak5 ,"peak5/F" );
    Float_t peak6; out->Branch("peak6"  ,&peak6 ,"peak6/F" );
    Float_t peak7; out->Branch("peak7"  ,&peak7 ,"peak7/F" );
    Float_t peak8; out->Branch("peak8"  ,&peak8 ,"peak8/F" );

    Float_t end0; out->Branch("end0"  ,&end0 ,"end0/F" );
    Float_t end1; out->Branch("end1"  ,&end1 ,"end1/F" );
    Float_t end2; out->Branch("end2"  ,&end2 ,"end2/F" );
    Float_t end3; out->Branch("end3"  ,&end3 ,"end3/F" );
    Float_t end4; out->Branch("end4"  ,&end4 ,"end4/F" );
    Float_t end5; out->Branch("end5"  ,&end5 ,"end5/F" );
    Float_t end6; out->Branch("end6"  ,&end6 ,"end6/F" );
    Float_t end7; out->Branch("end7"  ,&end7 ,"end7/F" );
    Float_t end8; out->Branch("end8"  ,&end8 ,"end8/F" );


    for(int pad=0;pad<9;pad++){
        if(pad<10){
            pFADC.Form ("hFADS_0%d", pad);
            pDIFF.Form ("hDIFF_0%d", pad);
            pdDIFF.Form ("dDIFF_0%d", pad);
            psDIFF.Form ("sDIFF_0%d", pad);
            pTEMP.Form ("hTEPM_0%d", pad);
            pDEMP.Form ("hDEMP_0%d", pad);
            pMax.Form ("tMax_0%d", pad);
            pEnergy.Form ("tEnergy_0%d", pad);
            pStart.Form ("tStart_0%d", pad);
        }
        else{
            pFADC.Form ("hFADS_%d", pad);
            pDIFF.Form ("hDIFF_%d", pad);
            pdDIFF.Form ("dDIFF_%d", pad);
            psDIFF.Form ("sDIFF_%d", pad);
            pTEMP.Form ("hTEPM_%d", pad);
            pDEMP.Form ("hDEMP_%d", pad);
            pMax.Form ("tMax_%d", pad);
            pEnergy.Form ("tEnergy_%d", pad);
            pStart.Form ("tStart_%d", pad);
        }

        hFADC[pad] = new TH1F( pFADC," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );
        hDIFF[pad] = new TH1F( pDIFF," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );
        dDIFF[pad] = new TH1F(pdDIFF," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );
        sDIFF[pad] = new TH1F(psDIFF," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );

        tMax   [pad] = new TH1F(pMax   ," ;time, ns; evts", 700, 47000, 54000 );
        tStart [pad] = new TH1F(pStart ," ;time, ns; evts", 700, 47000, 54000 );
        tEnergy[pad] = new TH1F(pEnergy," ;energy, a.u.; evts", 1300, 0, 130000 );

        hDIFF[pad]->SetLineColor(2);
    }
    tTotal = new TH1F("tTotal"," ;energy, a.u.; evts", 10000, 0, 1000000 );

    tMeV   = new TH1F("tMeV"  ," ;energy, MeV; evts",120, 4.4, 5.6 );
    tA2    = new TH1F("tA2"  ," ;energy, MeV; evts", 120, 4.4, 5.6 );
    tA3    = new TH1F("tA3"  ," ;energy, MeV; evts", 120, 4.4, 5.6 );
    tA4    = new TH1F("tA4"  ," ;energy, MeV; evts", 120, 4.4, 5.6 );
    tA5    = new TH1F("tA5"  ," ;energy, MeV; evts", 120, 4.4, 5.6 );

    tA3->SetLineColor(2);
    tA5->SetLineColor(2);

    hd1 = new TH1F("hd1","pad 1; signal length, ns; events",80,2500,2900);

    double Val;

    double Slope;
    int MaxDervBin;

    double cp[1000],fp[1000],mp[1000],ep[1000], sp[1000];
    double TotalE=0;




    tfile = new TFile("out.root","RECREATE");
    out->Write();
    tfile->Write();
    tfile->Close();


    TCanvas* canv = new TCanvas("canv","canv",1200,300);
    gStyle->SetOptStat(0);
    for(int p=0;p<9;p++){
//        hFADC[p]->SetFillColor(1);
//        hFADC[p]->GetXaxis()->SetRangeUser(47000,50000);
        hFADC[p]->Draw("hist");
        hDIFF[p]->Draw("same");
        if(p<10){pFADC.Form("FADS_0%d.png",p);}
        else{ pFADC.Form("FADS_%d.png",p);}
        canv->Print( pFADC );
    }
    canv->Close();




}
