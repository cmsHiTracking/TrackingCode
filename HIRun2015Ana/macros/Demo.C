#include "TrackCorrector3D.h"
using namespace std;

/*
Read ME:
This is a simple way to get efficiency correction in bins of pT, eta, and centrality
similarly for 2D case. 
*/

void Demo(){
	
	TrackCorrector3D testload("../rootfile/PbPb_eff_MC_v1.root");//efficiency in 2D and 3D histograms
	testload.load("HITrackCorrections");//name of the folder

	//double getWeigt(pt, eta, centralitybin)
	//getWeight is calculated as (1. - fak ) * ( 1. - sec ) / eff  / (1. + mul )
	cout << "getWeight: " << testload.getWeight(1.0, 1.0, 50) << endl;

}
