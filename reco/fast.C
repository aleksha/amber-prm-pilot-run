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

//bool ADD_NOISE = false;
bool ADD_NOISE = true;
int MY_EVTS    = 7000;
double Calib   = 200./151.;

int Ne_MAX = 100; // max nubmer of e- per substep
int Ll_MAX = 40 ; // um, length of substep

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

fadc_info info[9];


int get_pad2(double x, double y){
    // central pad R = 10 mm
    // other rinrs with width = 40 mm
    // numberinf inner-to-outer

    double l;
    l = sqrt(x*x+y*y);

    if( l>290 && l<=330) return  8;
    if( l>250 && l<=290) return  7;
    if( l>210 && l<=250) return  6;
    if( l>170 && l<=210) return  5;
    if( l>130 && l<=170) return  4;
    if( l> 90 && l<=130) return  3;
    if( l> 50 && l<= 90) return  2;
    if( l> 10 && l<= 50) return  1;
    if( l<= 10)          return  0;

    return -1;
}


void fast( int Evts=MY_EVTS, bool AddNoise=ADD_NOISE ){

  double I_av = 36.5*0.001*0.001; // MeV --> 36.5 eV to create e-ion pair
  int N_e;
  int N_s=0;

  int Nsub;

  double l, X, Y, Z, t_anod, d_anod;

  double W1 = 4.0*0.001; // mm/ns
  double z_anod = 0.;

//==============================================================================
// read digitization
//==============================================================================

  double Digi[175];
  int channel ;
  double digi,tt;

  std::ifstream fDIGI("./DigiC.txt" , std::ios::in);

  while( fDIGI >> channel >> digi ){
    Digi[channel]=digi;
  }
  fDIGI.close();

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

    std::ifstream fOUT("./out.data" , std::ios::in);
    std::ifstream fNOI("/home/geant/Data/Noise/MERGED/noise.data" , std::ios::in);

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

    while( fOUT >> ev >> vol >> dE >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){
        if(ev>EVENT){


            for(int p=0;p<9;p++){
                for(int nbin=1;nbin<2694;nbin++){
                    fNOI >> Val;
                    if(nbin<2551 && AddNoise){
                        hFADC[p]->SetBinContent( nbin, hFADC[p]->GetBinContent(nbin) + Val );
                        hDIFF[p]->SetBinContent( nbin, hDIFF[p]->GetBinContent(nbin) + Val );
                    }
                }

                info[p] = eval_info( hDIFF[p] );
                smearTH1(hDIFF[p],sDIFF[p]);
                derivTH1(sDIFF[p],dDIFF[p]);
                MaxDervBin = dDIFF[p]->GetMaximumBin();
                Slope = dDIFF[p]->GetBinContent( MaxDervBin );
                if(info[p].is_fired){
//                    info[p].start = eval_start2( hDIFF[p], info[p] );
//                    info[p].end   = eval_end2  ( hDIFF[p], info[p] );
                    tMax[p]->Fill(info[p].peak);
                    tStart[p]->Fill(info[p].start);
                    tEnergy[p]->Fill(info[p].energy);
                    TotalE += info[p].energy;
//                    std::cout << "----> " << p << "\t" << info[p].energy << "\n";
                }

//                if(p==0) print_info(info[p]) ;
//                std::cout << "pad:" << p << "  "; print_info(info[p]) ;
            }
//            std::cout << "pad: 1\t" << info[1].start << "\t" << info[1].end << "\t\t" << info[1].end-info[1].start << "\n";
            tTotal->Fill(TotalE);
            tMeV->Fill(TotalE/35710.);

            if(info[2].is_fired && !(info[3].is_fired)) { tA2->Fill(TotalE/35710.); EvtCntr++;}
            if(info[3].is_fired && !(info[4].is_fired)) { tA3->Fill(TotalE/35710.); EvtCntr++;}
            if(info[4].is_fired && !(info[5].is_fired)) tA4->Fill(TotalE/35710.);
            if(info[5].is_fired && !(info[6].is_fired)) tA5->Fill(TotalE/35710.);

            hd1->Fill(info[1].end-info[1].start);
            cp[EVENT] = info[0].start;
            fp[EVENT] = info[1].start;
            sp[EVENT] = info[2].start;
            mp[EVENT] = info[1].peak ;
            ep[EVENT] = info[1].end - info[1].start ;

            fired0 = info[0].is_fired;
            fired1 = info[1].is_fired;
            fired2 = info[2].is_fired;
            fired3 = info[3].is_fired;
            fired4 = info[4].is_fired;
            fired5 = info[5].is_fired;
            fired6 = info[6].is_fired;
            fired7 = info[7].is_fired;
            fired8 = info[8].is_fired;

            energy0 = info[0].energy;
            energy1 = info[1].energy;
            energy2 = info[2].energy;
            energy3 = info[3].energy;
            energy4 = info[4].energy;
            energy5 = info[5].energy;
            energy6 = info[6].energy;
            energy7 = info[7].energy;
            energy8 = info[8].energy;
            energy  = TotalE;

            start0 = info[0].start;
            start1 = info[1].start;
            start2 = info[2].start;
            start3 = info[3].start;
            start4 = info[4].start;
            start5 = info[5].start;
            start6 = info[6].start;
            start7 = info[7].start;
            start8 = info[8].start;

            peak0 = info[0].peak;
            peak1 = info[1].peak;
            peak2 = info[2].peak;
            peak3 = info[3].peak;
            peak4 = info[4].peak;
            peak5 = info[5].peak;
            peak6 = info[6].peak;
            peak7 = info[7].peak;
            peak8 = info[8].peak;

            end0 = info[0].end;
            end1 = info[1].end;
            end2 = info[2].end;
            end3 = info[3].end;
            end4 = info[4].end;
            end5 = info[5].end;
            end6 = info[6].end;
            end7 = info[7].end;
            end8 = info[8].end;

            out->Fill();
            if( !(ev%200) ) std::cout << "PROCESSED: "<< ev << " events\n";

            if(ev==Evts) break;

            for(int p=0;p<9;p++){
                hFADC[p]->Reset();
                hDIFF[p]->Reset();
                dDIFF[p]->Reset();
                sDIFF[p]->Reset();
            }
            TotalE=0;
            EVENT=ev;
        }


        if(vol==0){
            N_e = int( dE/ I_av );
            double ll = 1000.*sqrt(pow(xf-xi,2)+pow(yf-yi,2)+pow(zf-zi,2));
            Nsub = int(N_e/Ne_MAX);  if(Nsub < int(ll/Ll_MAX)) Nsub = int(ll/Ll_MAX);
            if(Nsub<1) Nsub=1;
//            double llr = 1000.*sqrt(pow(xf-xi,2)+pow(yf-yi,2));
//            double llz = 1000.*(zf-zi);
//            std::cout << ev << "\t" << N_e << "\t" << llr << "\t" << llz << "\n";
            if(N_e>0){
                dx = (xf-xi)/Nsub;
                dy = (yf-yi)/Nsub;
                dz = (zf-zi)/Nsub;
                dt = (tf-ti)/Nsub;
                N_s = 0;
                for(int ee=0;ee<Nsub;ee++){
                    x = xi + 0.5*dx + dx*ee;
                    y = yi + 0.5*dy + dy*ee;
                    z = zi + 0.5*dz + dz*ee;
                    t = ti + 0.5*dt + dt*ee;
                    fpad = get_pad2(x,y);
                    xd = x + gRandom->Gaus(0,0.06*sqrt(z/10.));
                    yd = y + gRandom->Gaus(0,0.06*sqrt(z/10.));
                    dpad = get_pad2(xd,yd);
                    if(fpad>-1 && dpad>-1){
                      t_anod = (t + (z-z_anod-10.) / W1 ) ;
                      d_anod = (t + (z+gRandom->Gaus(0,0.08*sqrt(z/10.))-z_anod-10.) / W1 ) ;
                      tt = 20;
//                      hFADC[fpad]->Fill(t_anod, Calib);
//                      hFADC[fpad]->Fill(t_anod, Calib);
//                      for(int iii = 0 ; iii<33; iii++  ){
//                          hFADC[fpad]->Fill(t_anod + tt, Calib/33.);
//                          hDIFF[dpad]->Fill(d_anod + tt, Calib/33.);
//                          tt = tt + 40 ;
//                      }

                      for(int iii = 0 ; iii<125; iii++  ){
                          hFADC[fpad]->Fill(t_anod + tt, Calib*Digi[iii]*N_e/Nsub);
                          hDIFF[dpad]->Fill(d_anod + tt, Calib*Digi[iii]*N_e/Nsub);
                          tt = tt + 40 ;
                        }
                    }
                }
            }
        }
    }
    fOUT.close();
    fNOI.close();


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

/*
    TCanvas* canvD = new TCanvas("canvD","canvD",1200,300);
    gStyle->SetOptStat(0);
    for(int p=0;p<9;p++){
        dDIFF[p]->Draw();
        if(p<10){pFADC.Form("dFADS_0%d.png",p);}
        else{ pFADC.Form("dFADS_%d.png",p);}
        canvD->Print( pFADC );
    }
    canvD->Close();


    TFile* f = new TFile("AllPads.root","RECREATE");
    for(int p=0;p<9;p++){
        hFADC[p]->Write();
        hDIFF[p]->Write();
    }
    f->Write();
    f->Close();
*/
    TCanvas* canvT = new TCanvas("canvT","canvT",800,600);
    gStyle->SetOptStat(0);
    for(int p=0;p<9;p++){
        tMax[p]  ->SetLineColor(2);
        tStart[p]->SetLineColor(4);
        tMax[p]  ->SetFillColor(2);
        tStart[p]->SetFillColor(4);
        tMax[p]  ->SetFillStyle(3004);
        tStart[p]->SetFillStyle(3005);
//        tStart[p]->Draw();
        tMax[p]->Draw();
//        tMax[p]->Draw("same");
        tStart[p]->Draw("same");
        std::cout << "Pad " << p << "\t" << tMax[p]->GetMean() << "\t" << tStart[p]->GetMean() << std::endl;
        std::cout << "Pad  \t"           << tMax[p]->GetRMS()  << "\t" << tStart[p]->GetRMS()  << std::endl;
        if(p<10){pFADC.Form("Time_0%d.png",p);}
        else{ pFADC.Form("Time_%d.png",p);}
        canvT->Print( pFADC );
        tEnergy[p]->Draw();
        if(p<10){pFADC.Form("Energy_0%d.png",p);}
        else{ pFADC.Form("Energy_%d.png",p);}
        std::cout << "Pad  \t"  << tEnergy[p]->GetMean()  << "\t" << tEnergy[p]->GetRMS()  << std::endl;
        canvT->Print( pFADC );
    }
    tTotal->Draw();
    canvT->Print( "TotalEnergy.png" );
    tMeV->Draw();
    canvT->Print( "TotalEnergyMeV.png" );
    tA2->Draw();
    tA3->Draw("same");
    canvT->Print( "TotalEnergyMeV23.png" );
    tA3->Draw();
    tA4->Draw("same");
    canvT->Print( "TotalEnergyMeV34.png" );
    tA4->Draw();
    tA5->Draw("same");
    canvT->Print( "TotalEnergyMeV45.png" );
    canvT->Close();
/*
    TGraph* gp = new TGraph(Evts,cp,fp);
    TGraph* gc = new TGraph(Evts,mp,fp);
    TGraph* ge = new TGraph(Evts,ep,fp);
    gp->SetMarkerStyle(20);
    gc->SetMarkerStyle(24);
    ge->SetMarkerStyle(21);
    gp->SetTitle("Central vs 1st pad");
    gc->SetTitle("Pad 1: start vs peak");
    ge->SetTitle("Pad 1: start vs length");
    TCanvas* canvS = new TCanvas("canvS","canvS",800,800);
    gStyle->SetOptStat(0);
    gp->Draw("ap");
    canvS->Print( "Scatter_0vs1.png" );
    gc->Draw("ap");
    canvS->Print( "Corr_PEAKvsSTART.png" );
    ge->Draw("ap");
    canvS->Print( "Corr_LENGTHvsSTART.png" );
    canvS->Close();


    TH1F* hA = new TH1F("hA",";angle, deg.; Events", 200,-10,10);
    TH1F* hB = new TH1F("hB",";angle, deg.; Events", 200,-10,10);
    for(int e=0;e<Evts;e++){
        hA->Fill( atan( (fp[e]-cp[e])*W1/25. )*180./3.14159265);
        hB->Fill( atan( (sp[e]-fp[e])*W1/40. )*180./3.14159265);
    }
    TCanvas* canvA = new TCanvas("canvA","canvA",800,800);
    hA->SetLineWidth(2);
    hA->SetLineColor(1);
    hA->SetFillColor(1);
    hA->SetFillStyle(3005);
    hA->Draw();
    std::cout << "mean : " << hA->GetMean() << "\t rms : " << hA->GetRMS() << "\n";
    canvA->Print( "Angle_0vs1.png" );
    hB->SetLineWidth(2);
    hB->SetLineColor(2);
    hB->SetFillColor(2);
    hB->SetFillStyle(3004);
    hB->Draw();
    std::cout << "mean : " << hB->GetMean() << "\t rms : " << hB->GetRMS() << "\n";
    canvA->Print( "Angle_1vs2.png" );
    canvA->Close();


    TCanvas* canvW = new TCanvas("canvW","canvW",800,800);
    hd1->SetLineWidth(2);
    hd1->SetLineColor(2);
    hd1->SetFillColor(2);
    hd1->SetFillStyle(3004);
    hd1->Draw();
    std::cout << "mean : " << hd1->GetMean() << "\t rms : " << hd1->GetRMS() << "\n";
    canvW->Print( "Length_01.png" );
    canvW->Close();
    std::cout << "Energy: " << tTotal->GetMean() << " +- " << tTotal->GetRMS() << "\n";
*/

    std::cout << "EvtCntr = " << EvtCntr << "\n";
    gSystem->Exit(0);

}
