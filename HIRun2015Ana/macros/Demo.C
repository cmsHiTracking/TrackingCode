#include "TrackCorrector3D.h"
using namespace std;

/*
Read ME:
This is a simple way to get efficiency correction in bins of pT, eta, and centrality
similarly for 2D case. 
*/

void Demo(){
	
	TrackCorrector3D testload("../rootfile/PbPb_dijet_NTT.root");//efficiency in 2D and 3D histograms
	testload.load("HITrackCorrections");//name of the folder

	//double getWeigt(double pt, double eta, double centralitybin, string option)
	//if option leaves open or "", getWeight returns (1. - fak ) * ( 1. - sec ) / eff  / (1. + mul )
	//if option is specified with "eff" or "fak" or "sec" or "mul", getWeight only return the corresponding value 
	
	
	cout << "getWeight with all correction " << testload.getWeight(1.0, 1.0, 50, "") << endl;
	cout << "getWeight with only fake rate " << testload.getWeight(1.0, 1.0, 50, "fak") << endl;

}
