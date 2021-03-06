#include <fstream>
#include <iostream>
#include <iomanip>

#include "histo_funcs.cc"
#include "../configs/reco/config_track.h"

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

struct hits_info
{
    TVector3  vect[EVENT_SIZE];
    double    time[EVENT_SIZE];
    int n;
};
/*
TVector3 Vertex(TVector3 p1, TVector3 b, TVector3 p2, TVector3 d){

    TVector3 d1, d2, n1, n2, c1, c2, rr;

    d1 = ( b - p1 ).Unit();
    d2 = ( d - p2 ).Unit();

    n1 = d1.Cross( d2.Cross(d1) );
    n2 = d2.Cross( d1.Cross(d2) );

    c1 = p1 + d1 * ( ( ( p2 - p1 ) * n2 ) / ( d1*n2 ) );
    c2 = p2 + d2 * ( ( ( p1 - p2 ) * n1 ) / ( d2*n1 ) );

    rr = (c1+c2)*0.5 ;

    return rr.Z();
}
*/
hits_info info[10];


void fill_info(int vol, double x, double y, double z, double t){
    info[vol].vect[ info[vol].n ].SetX( x + gRandom->Gaus( 0, RESO ) );
    info[vol].vect[ info[vol].n ].SetY( y + gRandom->Gaus( 0, RESO ) );
    info[vol].vect[ info[vol].n ].SetZ( z                            );
    info[vol].time[ info[vol].n ] = t;
    info[vol].n++;
}

void reset_info(){ 
    for(int i=0;i<10;i++)
        info[i].n=0; 
}


bool good_event(){
   for(int i=0;i<10;i++){
       //std::cout << i << " ";
       if(info[i].n < required_hits[i]){
           return false;
       }
   } 
   //std::cout << "\n";
   return true;
}

bool good_event2(){

   if( info[0].n<1 && info[1].n<1 ) return false;
   if( info[2].n<1 && info[3].n<1 ) return false;
   if( info[4].n<1 && info[5].n<1 ) return false;
   if( info[6].n<1 && info[7].n<1 ) return false;

   return true;
}


float calc_angle(){
    TVector3 v1 = 0.5*(info[0].vect[0] + info[1].vect[0]);
    TVector3 v2 = 0.5*(info[2].vect[0] + info[3].vect[0]);
    TVector3 v3 = 0.5*(info[4].vect[0] + info[5].vect[0]);
    TVector3 v4 = 0.5*(info[6].vect[0] + info[7].vect[0]);
    return 1000.*1000.*(v4-v3).Angle(v2-v1);
}


float calc_angle1(){
    TVector3 v1 = info[0].vect[0];
    TVector3 v2 = info[2].vect[0];
    TVector3 v3 = info[4].vect[0];
    TVector3 v4 = info[6].vect[0];
    return 1000.*1000.*(v4-v3).Angle(v2-v1);
}


float calc_angle2(){
    TVector3 v1 = info[1].vect[0];
    TVector3 v2 = info[3].vect[0];
    TVector3 v3 = info[5].vect[0];
    TVector3 v4 = info[7].vect[0];
    return 1000.*1000.*(v4-v3).Angle(v2-v1);
}

float calc_angle3(){
    TVector3 v1, v2, v3, v4;

    if(info[0].n>0 ){ v1 = info[0].vect[0]; }
    else{             v1 = info[1].vect[0]; }

    if(info[2].n>0 ){ v2 = info[2].vect[0]; }
    else{             v2 = info[3].vect[0]; }

    if(info[4].n>0 ){ v3 = info[4].vect[0]; }
    else{             v3 = info[5].vect[0]; }

    if(info[6].n>0 ){ v4 = info[6].vect[0]; }
    else{             v4 = info[7].vect[0]; }

    return 1000.*1000.*(v4-v3).Angle(v2-v1);
}


void reco_track(){

    int ev, vol;
    double dE, x, y, z, t;
    

    std::ifstream fMERGED("merged.data" , std::ios::in);

    int EVENT = 0;
    int nGood=0;
    int nBad =0;

    float Ang,Ang1,Ang2;

    TH1F* hAng  = new TH1F("hAng" ,";angle,#mu rad;Evts", 150, 0, 1500);
    TH1F* hAng1 = new TH1F("hAng1",";angle,#mu rad;Evts", 150, 0, 1500);
    TH1F* hAng2 = new TH1F("hAng2",";angle,#mu rad;Evts", 150, 0, 1500);
    hAng1->SetLineColor(1);
    hAng2->SetLineColor(2);
    while( fMERGED >> ev >> vol >> dE >> x >> y >> z >> t ){
        if(ev>EVENT){

/*
            std::cout << EVENT << "\t";
            for(int i=0;i<10;i++)
                std::cout << "   " << info[i].n << "/" << required_hits[i] ;
            std::cout << "\n";

            if( good_event() ){ 
                nGood++;
                //std::cout << EVENT << "\t" << calc_angle() << "\t" << calc_angle1() << "\t" << calc_angle2() << "\n";
                //std::cout << EVENT << "\t" << calc_angle() << "\n";
                Ang  = calc_angle();
                Ang1 = calc_angle1();
                Ang2 = calc_angle2();
                if( Ang>0 && Ang<1500)   hAng->Fill( Ang  );
                if( Ang1>0 && Ang1<1500) hAng1->Fill( Ang1 );
                if( Ang2>0 && Ang2<1500) hAng2->Fill( Ang2 );
            } else {nBad++;}
*/
            if( good_event2() ){ 
                nGood++;
                Ang  = calc_angle3();
                if( Ang>0 && Ang<1500)   hAng->Fill( Ang  );
            } else {nBad++;}


            reset_info();
//            if( (ev-EVENT)>1 ) std::cout << ev-1 << "\n";
            EVENT = ev;
        }

        fill_info(vol, x, y, z, t);
    }

    TCanvas* canv = new TCanvas("canv","canv",800,600);
    hAng->Fit("gaus");
    hAng->Draw();
//    hAng1->Draw();
//    hAng2->Draw("same");
    canv->Print("ANG.png");

    std::cout << "Good / Bad : " << nGood << " / " << nBad << " \n";
    std::cout << "Total      : " << EVENT << " \n";
    std::cout << "Efficiency : " << 100.*float(nGood) / float( EVENT ) << " %\n";

    fMERGED.close();
    gSystem->Exit(0);

}


/*
          if( fired[0] && fired[1] && fired[2] && fired[3] ){

              vv0.SetXYZ( xx[0] , yy[0], zz[0]);
              vv1.SetXYZ( xx[1] , yy[1], zz[1]);
              vv2.SetXYZ( xx[2] , yy[2], zz[2]);
              vv3.SetXYZ( xx[3] , yy[3], zz[3]);
              ww0.SetXYZ( sx[0] , sy[0], sz[0]);
              ww1.SetXYZ( sx[1] , sy[1], sz[1]);
              ww2.SetXYZ( sx[2] , sy[2], sz[2]);
              ww3.SetXYZ( sx[3] , sy[3], sz[3]);

              vINI.SetXYZ( xx[1]-xx[0] , yy[1]-yy[0], -5000.);
              vOUT.SetXYZ( xx[3]-xx[2] , yy[3]-yy[2], -5000.);
              v_vtx = Vertex( vv0, vv1, vv2, vv3);

              wINI.SetXYZ( sx[1]-sx[0] , sy[1]-sy[0], -5000.);
              wOUT.SetXYZ( sx[3]-sx[2] , sy[3]-sy[2], -5000.);
              w_vtx = Vertex( ww0, ww1, ww2, ww3);
*/