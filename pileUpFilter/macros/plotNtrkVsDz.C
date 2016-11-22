#include "RiceStyle.h"

using namespace std;

void plotNtrkVsDz(){
	
	TFile* file1 = new TFile("../rootfile/pileUpStudy_pPb8TeV_MC_pile0.root");
	TFile* file2 = new TFile("../rootfile/pileUpStudy_pPb8TeV_MC_pile1.root");
	TFile* file3 = new TFile("../rootfile/pileUpStudy_pPb8TeV_MC_pile2.root");

	TFile* file4 = new TFile("../rootfile/pileUpStudy_pPb8TeV_data_285480.root");
	TFile* file5 = new TFile("../rootfile/pileUpStudy_pPb8TeV_data_285505.root");
	TFile* file6 = new TFile("../rootfile/pileUpStudy_pPb8TeV_data_285517.root");

	TH2D* hist1 = (TH2D*) file1->Get("pPbPileup/assocVtxDzNtrk");
	TH2D* hist2 = (TH2D*) file2->Get("pPbPileup/assocVtxDzNtrk");
	TH2D* hist3 = (TH2D*) file3->Get("pPbPileup/assocVtxDzNtrk");

	TH2D* hist4 = (TH2D*) file4->Get("pPbPileup/assocVtxDzNtrk");
	TH2D* hist5 = (TH2D*) file5->Get("pPbPileup/assocVtxDzNtrk");
	TH2D* hist6 = (TH2D*) file6->Get("pPbPileup/assocVtxDzNtrk");

	TCanvas* c1 = makeMultiCanvas("c1","Filter Fraction", 2,2);

	TH1D* base1 = makeHist("base1", "EPOS PU = 0","dz (cm)","N_{trk}", 200, 0,100, kBlack);
	TH1D* base2 = makeHist("base2", "EPOS PU = 1","dz (cm)","N_{trk}", 200, 0,100, kBlack);
	TH1D* base3 = makeHist("base3", "EPOS PU = 2","dz (cm)","N_{trk}", 200, 0,100, kBlack);

	base1->GetYaxis()->SetRangeUser(0,20);
	base1->GetXaxis()->SetRangeUser(0,7);

	base2->GetYaxis()->SetRangeUser(0,20);
	base2->GetXaxis()->SetRangeUser(0,7);

	base3->GetYaxis()->SetRangeUser(0,20);
	base3->GetXaxis()->SetRangeUser(0,7);

	TLine* l1[20];
	TLine* l2[20];
	
	l1[0] = new TLine(0.1,13,0.1,20);
	l1[1] = new TLine(0.2,9,0.2,13);
	l1[2] = new TLine(0.3,8,0.3,9);
	l1[3] = new TLine(0.4,7,0.4,8);
	l1[4] = new TLine(0.5,6,0.5,7);
	l1[5] = new TLine(0.6,5,0.6,6);
	l1[6] = new TLine(0.8,4,0.8,5);
	l1[7] = new TLine(1.0,3,1.0,4);
	l1[8] = new TLine(1.5,2,1.5,3);

	l2[0] = new TLine(0.1,13,0.2,13);
	l2[1] = new TLine(0.2,9,0.3,9);
	l2[2] = new TLine(0.3,8,0.4,8);
	l2[3] = new TLine(0.4,7,0.5,7);
	l2[4] = new TLine(0.5,6,0.6,6);
	l2[5] = new TLine(0.6,5,0.8,5);
	l2[6] = new TLine(0.8,4,1.0,4);
	l2[7] = new TLine(1.0,3,1.5,3);
	l2[8] = new TLine(1.5,2,4.0,2);

	c1->cd(1);
	gPad->SetTicks();
	gPad->SetLogz();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);
	base1->Draw();
	hist1->Draw("colzsame");
	for(int i = 0; i < 9; i++){

		l1[i]->SetLineColor(kBlack);
		l1[i]->SetLineStyle(2);
		l1[i]->SetLineWidth(2);
		l1[i]->Draw("same");

		l2[i]->SetLineColor(kBlack);
		l2[i]->SetLineStyle(2);
		l2[i]->SetLineWidth(2);
		l2[i]->Draw("same");
	}

	c1->cd(2);
	gPad->SetTicks();
	gPad->SetLogz();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);
	base2->Draw();
	hist2->Draw("colzsame");
	for(int i = 0; i < 9; i++){

		l1[i]->SetLineColor(kBlack);
		l1[i]->SetLineStyle(2);
		l1[i]->SetLineWidth(2);
		l1[i]->Draw("same");

		l2[i]->SetLineColor(kBlack);
		l2[i]->SetLineStyle(2);
		l2[i]->SetLineWidth(2);
		l2[i]->Draw("same");
	}

	c1->cd(3);
	gPad->SetTicks();
	gPad->SetLogz();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);
	base3->Draw();
	hist3->Draw("colzsame");
	for(int i = 0; i < 9; i++){

		l1[i]->SetLineColor(kBlack);
		l1[i]->SetLineStyle(2);
		l1[i]->SetLineWidth(2);
		l1[i]->Draw("same");

		l2[i]->SetLineColor(kBlack);
		l2[i]->SetLineStyle(2);
		l2[i]->SetLineWidth(2);
		l2[i]->Draw("same");
	}



	TCanvas* c2 = makeMultiCanvas("c2","Filter Fraction", 2,2);

	TH1D* base4 = makeHist("base4", "DATA #LTPU#GT = 0.04","dz (cm)","N_{trk}", 200, 0,100, kBlack);
	TH1D* base5 = makeHist("base5", "DATA #LTPU#GT = 0.25","dz (cm)","N_{trk}", 200, 0,100, kBlack);
	TH1D* base6 = makeHist("base6", "DATA #LTPU#GT = 0.1","dz (cm)","N_{trk}", 200, 0,100, kBlack);

	base4->GetYaxis()->SetRangeUser(0,20);
	base4->GetXaxis()->SetRangeUser(0,7);

	base5->GetYaxis()->SetRangeUser(0,20);
	base5->GetXaxis()->SetRangeUser(0,7);

	base6->GetYaxis()->SetRangeUser(0,20);
	base6->GetXaxis()->SetRangeUser(0,7);

	c2->cd(1);
	gPad->SetTicks();
	gPad->SetLogz();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);
	base4->Draw();
	hist4->Draw("colzsame");
	for(int i = 0; i < 9; i++){

		l1[i]->SetLineColor(kBlack);
		l1[i]->SetLineStyle(2);
		l1[i]->SetLineWidth(2);
		l1[i]->Draw("same");

		l2[i]->SetLineColor(kBlack);
		l2[i]->SetLineStyle(2);
		l2[i]->SetLineWidth(2);
		l2[i]->Draw("same");
	}

	c2->cd(2);
	gPad->SetTicks();
	gPad->SetLogz();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);
	base5->Draw();
	hist5->Draw("colzsame");
	for(int i = 0; i < 9; i++){

		l1[i]->SetLineColor(kBlack);
		l1[i]->SetLineStyle(2);
		l1[i]->SetLineWidth(2);
		l1[i]->Draw("same");

		l2[i]->SetLineColor(kBlack);
		l2[i]->SetLineStyle(2);
		l2[i]->SetLineWidth(2);
		l2[i]->Draw("same");
	}

	c2->cd(3);
	gPad->SetTicks();
	gPad->SetLogz();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);
	base6->Draw();
	hist6->Draw("colzsame");
	for(int i = 0; i < 9; i++){

		l1[i]->SetLineColor(kBlack);
		l1[i]->SetLineStyle(2);
		l1[i]->SetLineWidth(2);
		l1[i]->Draw("same");

		l2[i]->SetLineColor(kBlack);
		l2[i]->SetLineStyle(2);
		l2[i]->SetLineWidth(2);
		l2[i]->Draw("same");
	}



	// c1->SaveAs("../files/pileUpFilterEfficiency_MC.png");
	// c1->SaveAs("../files/pileUpFilterEfficiency_MC.pdf");


}