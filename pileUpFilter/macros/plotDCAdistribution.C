#include "RiceStyle.h"

using namespace std;

void plotDCAdistribution(){



	TFile* file[4];

	file[0] = new TFile("../rootfile/pileUpFilterEfficiency_DATA_MB.root");
	file[1] = new TFile("../rootfile/pileUpFilterEfficiency_MC_1.root");

	TH1D* temp1 = (TH1D*)file[0]->Get("ana_PbPb0/vertexZ");
	TH1D* temp2 = (TH1D*)file[1]->Get("ana_PbPb0/vertexZ");

	TH1D* base1 = makeHist("base1","pp DATA","Track impact parameter Z","", 100,-1.3,1.3);
	TH1D* base2 = makeHist("base2","pp MC","Track impact parameter Z","", 100,-1.3,1.3);

	base1->GetYaxis()->SetRangeUser(0,0.05);
	base2->GetYaxis()->SetRangeUser(0,0.05);

	base1->GetXaxis()->SetTitleColor(kBlack);
	base2->GetXaxis()->SetTitleColor(kBlack);

	TCanvas* c1 = makeMultiCanvas("c1","c1",2,1);
	c1->cd(1);
	gPad->SetLeftMargin(0.13);
	gPad->SetBottomMargin(0.13);
	base1->Draw("");
	temp1->Scale( 1/(temp1->Integral()));
	temp1->SetMarkerStyle(20);
	temp1->Draw("Psame");
	c1->cd(2);
	base2->Draw("");
	gPad->SetLeftMargin(0.13);
	gPad->SetBottomMargin(0.13);
	temp2->Scale( 1/(temp2->Integral()));
	temp2->SetMarkerStyle(20);
	temp2->Draw("Psame");



}