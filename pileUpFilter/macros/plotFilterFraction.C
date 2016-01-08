#include "RiceStyle.h"

using namespace std;

void plotFilterFraction(){
	
	TFile* file = new TFile("../rootfile/pielUpFilterEfficiency_MC_2.root");
	vector<TH1D*> hist = loadingHistogram(file, "ana_PbPb","/Ntrk", 4);
	TCanvas* c1 = makeCanvas("c1","Filter Fraction");
	TH1D* base = makeHist("base", "","N^{offline}_{trk}","Fraction accepted", 200, 0,100, kBlack);

	TGraphAsymmErrors * gr[5];
	gPad->SetTicks();
	gPad->SetLeftMargin(0.15);
	
	base->Draw();
	gr[0] = new TGraphAsymmErrors();
	gr[0]->Divide(hist[1], hist[0], "cp");
	gr[0]->SetMarkerStyle(20);
	gr[0]->SetLineColor(1);
	gr[0]->SetMarkerColor(1);
	gr[0]->Draw("same");

	gr[1] = new TGraphAsymmErrors();
	gr[1]->Divide(hist[2], hist[0], "cp");
	gr[1]->SetMarkerStyle(20);
	gr[1]->SetLineColor(2);
	gr[1]->SetMarkerColor(2);
	gr[1]->Draw("same");

	gr[2] = new TGraphAsymmErrors();
	gr[2]->Divide(hist[3], hist[0], "cp");
	gr[2]->SetMarkerStyle(20);
	gr[2]->SetLineColor(4);
	gr[2]->SetMarkerColor(4);
	gr[2]->Draw("same");

    TLegend *w1 = new TLegend(0.35,0.45,0.55,0.65);
    w1->SetLineColor(kWhite);
    w1->SetFillColor(0);
    w1->AddEntry(gr[0], "Gplus+dz","P");
	w1->AddEntry(gr[1], "Gplus","P");
	w1->AddEntry(gr[2], "vtx1","P");

	w1->Draw("same");

}