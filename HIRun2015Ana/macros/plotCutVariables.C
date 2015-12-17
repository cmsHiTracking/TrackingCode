#include "RiceStyle.h"

using namespace std;

/*
Because the tree format output is too large to include on git, this is an example of plotting
cut variables distribution between MC and Data. As long as the output is in Ntuple or TrackTree 
format, input the MC and Data Ntuple in the following directory
*/

void plotCutVariables(){
	
	TFile* file = new TFile("../your/directory/DATA_tree.root"); //need to overwrite
	TFile* file1 = new TFile("../your/directory/MC_tree.root");// need to overwrite
	
	TTree* ana = (TTree*) file->Get("yourFolderName/trackTree");
	TTree* hydjet = (TTree*) file1->Get("yourFolderName/trackTree");

	vector<char*> varNames;
	varNames.push_back( "fabs(trkPtError)/trkPt>>cut1" );
	varNames.push_back( "trkEta>>cut2" );
	varNames.push_back( "trkPhi>>cut3");
	varNames.push_back( "trkAlgo>>cut4" );
	varNames.push_back( "trkNHit>>cut5" );
	varNames.push_back( "fabs(trkDxy1/trkDxyError1)>>cut6" );
	varNames.push_back( "fabs(trkDz1/trkDzError1)>>cut7" );
	varNames.push_back( "(trkChi2/trkNdof)/trkNlayer>>cut8");
	varNames.push_back( "zVtx>>cut9" );

	vector<char*> varNames1;
	varNames1.push_back( "fabs(trkPtError)/trkPt>>cut11" );
	varNames1.push_back( "trkEta>>cut12" );
	varNames1.push_back( "trkPhi>>cut13");
	varNames1.push_back( "trkAlgo>>cut14" );
	varNames1.push_back( "trkNHit>>cut15" );
	varNames1.push_back( "fabs(trkDxy1/trkDxyError1)>>cut16" );
	varNames1.push_back( "fabs(trkDz1/trkDzError1)>>cut17" );
	varNames1.push_back( "(trkChi2/trkNdof)/trkNlayer>>cut18");
	varNames1.push_back( "zVtx>>cut19" );

	TH1D* cut[10];
	cut[0] = makeHist("cut1", varNames[0], "", "#Counts", 1000,0,0.2, kBlack);
	cut[1] = makeHist("cut2", varNames[1], "", "#Counts", 100,-3.0,3.0, kBlack);
	cut[2] = makeHist("cut3", varNames[2], "", "#Counts", 100,-3.5,3.5, kBlack);
	cut[3] = makeHist("cut4", varNames[3], "", "#Counts", 20, 0,20, kBlack);
	cut[4] = makeHist("cut5", varNames[4], "", "#Counts", 100,0,50, kBlack);
	cut[5] = makeHist("cut6", varNames[5], "", "#Counts", 500,0,50, kBlack);
	cut[6] = makeHist("cut7", varNames[6], "", "#Counts", 500,0,50, kBlack);
	cut[7] = makeHist("cut8", varNames[7], "", "#Counts", 100,0,2, kBlack);
	cut[8] = makeHist("cut9", varNames[8], "", "#Counts", 500,-20,20, kBlack);

	TH1D* cut1[10];
	cut1[0] = makeHist("cut11", varNames1[0], "", "#Counts", 1000,0,0.2, kRed);
	cut1[1] = makeHist("cut12", varNames1[1], "", "#Counts", 100,-3.0,3.0, kRed);
	cut1[2] = makeHist("cut13", varNames1[2], "", "#Counts", 100,-3.5,3.5, kRed);
	cut1[3] = makeHist("cut14", varNames1[3], "", "#Counts", 20, 0,20, kRed);
	cut1[4] = makeHist("cut15", varNames1[4], "", "#Counts", 100,0,50, kRed);
	cut1[5] = makeHist("cut16", varNames1[5], "", "#Counts", 500,0,50, kRed);
	cut1[6] = makeHist("cut17", varNames1[6], "", "#Counts", 500,0,50, kRed);
	cut1[7] = makeHist("cut18", varNames1[7], "", "#Counts", 100,0,2, kRed);
	cut1[8] = makeHist("cut19", varNames1[8], "", "#Counts", 500,-20,20, kRed);

	TCanvas* canvas = makeMultiCanvas("canvas","name",3,3);

	for( int i = 0; i < varNames.size(); i ++ ){

		canvas->cd(i+1);
		gPad->SetTicks();
		if( i == 0 || i  == 5 || i == 6 || i == 7 ) {
			gPad->SetLogy(1);
		}
		ana->Draw(varNames[i], "highPurity == 1 ");
		hydjet->Draw(varNames1[i], "highPurity == 1 " );

		cut[i]->Scale( 1/(cut[i]->Integral()) );
		cut[i]->Draw("");

		cut1[i]->Scale( 1/(cut1[i]->Integral()) );
		cut1[i]->Draw("same");
	}

	TLegend *w1 = new TLegend(0.75,0.75,0.87,0.87);
	w1->SetLineColor(kWhite);
	w1->SetFillColor(0);
	w1->AddEntry(cut1[0], "MC", "P");
	w1->AddEntry(cut[0], "Data", "P");
	w1->Draw("same");
}