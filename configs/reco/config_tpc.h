
int MY_EVTS    = 5;
double Calib   = 200./151.;

int Ne_MAX = 100; // max nubmer of e- per substep
int Ll_MAX = 40 ; // um, length of substep

double I_av = 36.5*0.001*0.001; // MeV --> 36.5 eV to create e-ion pair
double W1 = 4.0*0.001; // mm/ns

// Shapung
//bool ADD_SHAPING = true;
bool ADD_SHAPING = false;

// Anodes positions
double Z_anode_1 = -400.;
double Z_anode_2 =  400.;

// diffusion parameters are obtained from German Korolev (PNPI)
bool  ADD_DIFFUSION = false;
double DIFF_P =0.06;
double DIFF_L =0.08;

// add noise
//bool ADD_NOISE = true;
bool ADD_NOISE = false;