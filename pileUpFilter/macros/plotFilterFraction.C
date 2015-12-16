#include "RiceStyle.h"

using namespace std;

void plotFilterFraction(){
	
	TFile* file = new TFile("../rootfile/Ntrk_pileup_1.root");
	vector<TH1D*> hist = loadingHistogram(file, "ana_PbPb","/Ntrk", 6);
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
	gr[2]->SetLineColor(3);
	gr[2]->SetMarkerColor(3);
	gr[2]->Draw("same");

	gr[3] = new TGraphAsymmErrors();
	gr[3]->Divide(hist[4], hist[0], "cp");
	gr[3]->SetMarkerStyle(20);
	gr[3]->SetLineColor(4);
	gr[3]->SetMarkerColor(4);
	gr[3]->Draw("same");

	gr[4] = new TGraphAsymmErrors();
	gr[4]->Divide(hist[5], hist[0], "cp");
	gr[4]->SetMarkerStyle(20);
	gr[4]->SetLineColor(5);
	gr[4]->SetMarkerColor(5);
	gr[4]->Draw("same");

}