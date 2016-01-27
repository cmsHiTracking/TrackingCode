#include "RiceStyle.h"

using namespace std;

void plotFilterFraction(){
	
	TFile* file1 = new TFile("../rootfile/pileUpFilterEfficiency_MC_1.root");
	TFile* file2 = new TFile("../rootfile/pileUpFilterEfficiency_updateMC_2.root");
	TFile* file3 = new TFile("../rootfile/pileUpFilterEfficiency_updateMC_3.root");


	vector<TH1D*> hist1 = loadingHistogram(file1, "ana_PbPb","/Ntrk", 4);
	vector<TH1D*> hist2 = loadingHistogram(file2, "ana_PbPb","/Ntrk", 4);
	vector<TH1D*> hist3 = loadingHistogram(file3, "ana_PbPb","/Ntrk", 4);

	TCanvas* c1 = makeMultiCanvas("c1","Filter Fraction", 2,2);

	TH1D* base1 = makeHist("base1", "PYTHIA MB","N^{offline}_{trk}","Fraction accepted", 200, 0,100, kBlack);
	TH1D* base2 = makeHist("base2", "PYTHIA PU = 2","N^{offline}_{trk}","Fraction accepted", 200, 0,100, kBlack);
	TH1D* base3 = makeHist("base3", "PYTHIA PU = 3","N^{offline}_{trk}","Fraction accepted", 200, 0,100, kBlack);
	

	c1->cd(1);

	TGraphAsymmErrors * gr1[5];
	gPad->SetTicks();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);

	base1->Draw();
	gr1[0] = new TGraphAsymmErrors();
	gr1[0]->Divide(hist1[1], hist1[0], "cp");
	gr1[0]->SetMarkerStyle(20);
	gr1[0]->SetLineColor(1);
	gr1[0]->SetMarkerColor(1);
	gr1[0]->Draw("same");

	gr1[1] = new TGraphAsymmErrors();
	gr1[1]->Divide(hist1[2], hist1[0], "cp");
	gr1[1]->SetMarkerStyle(20);
	gr1[1]->SetLineColor(2);
	gr1[1]->SetMarkerColor(2);
	gr1[1]->Draw("same");

	gr1[2] = new TGraphAsymmErrors();
	gr1[2]->Divide(hist1[3], hist1[0], "cp");
	gr1[2]->SetMarkerStyle(20);
	gr1[2]->SetLineColor(4);
	gr1[2]->SetMarkerColor(4);
	gr1[2]->Draw("same");

    TLegend *w1 = new TLegend(0.25,0.25,0.45,0.45);
    w1->SetLineColor(kWhite);
    w1->SetFillColor(0);
    w1->AddEntry(gr1[2], "Gplus+dz","P");
	w1->AddEntry(gr1[1], "Gplus","P");
	w1->AddEntry(gr1[0], "vtx1","P");

	w1->Draw("same");

	c1->cd(2);

	TGraphAsymmErrors * gr2[5];
	gPad->SetTicks();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);

	base2->Draw();
	gr2[0] = new TGraphAsymmErrors();
	gr2[0]->Divide(hist2[1], hist2[0], "cp");
	gr2[0]->SetMarkerStyle(20);
	gr2[0]->SetLineColor(1);
	gr2[0]->SetMarkerColor(1);
	gr2[0]->Draw("same");

	gr2[1] = new TGraphAsymmErrors();
	gr2[1]->Divide(hist2[2], hist2[0], "cp");
	gr2[1]->SetMarkerStyle(20);
	gr2[1]->SetLineColor(2);
	gr2[1]->SetMarkerColor(2);
	gr2[1]->Draw("same");

	gr2[2] = new TGraphAsymmErrors();
	gr2[2]->Divide(hist2[3], hist2[0], "cp");
	gr2[2]->SetMarkerStyle(20);
	gr2[2]->SetLineColor(4);
	gr2[2]->SetMarkerColor(4);
	gr2[2]->Draw("same");

	c1->cd(3);

	TGraphAsymmErrors * gr3[5];
	gPad->SetTicks();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);

	base3->Draw();
	gr3[0] = new TGraphAsymmErrors();
	gr3[0]->Divide(hist3[1], hist3[0], "cp");
	gr3[0]->SetMarkerStyle(20);
	gr3[0]->SetLineColor(1);
	gr3[0]->SetMarkerColor(1);
	gr3[0]->Draw("same");

	gr3[1] = new TGraphAsymmErrors();
	gr3[1]->Divide(hist3[2], hist3[0], "cp");
	gr3[1]->SetMarkerStyle(20);
	gr3[1]->SetLineColor(2);
	gr3[1]->SetMarkerColor(2);
	gr3[1]->Draw("same");

	gr3[2] = new TGraphAsymmErrors();
	gr3[2]->Divide(hist3[3], hist3[0], "cp");
	gr3[2]->SetMarkerStyle(20);
	gr3[2]->SetLineColor(4);
	gr3[2]->SetMarkerColor(4);
	gr3[2]->Draw("same");

	c1->SaveAs("../files/pileUpFilterEfficiency_MC.png");
	c1->SaveAs("../files/pileUpFilterEfficiency_MC.pdf");


}