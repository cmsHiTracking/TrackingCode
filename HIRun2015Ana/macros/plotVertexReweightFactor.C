#include "RiceStyle.h"

using namespace std;

void plotVertexReweightFactor(){

	TFile* file = new TFile("../Ntuple/singleTrackTree_test.root");
	TFile* file1 = new TFile("../Ntuple/trackTree_MC_v1.root");

	TTree* ana = (TTree*) file->Get("ana_PbPb/trackTree");
	TTree* hydjet = (TTree*) file1->Get("ana_PbPb/trackTree");

	TH1D* vtx;
	TH1D* vtx1;

	vtx = makeHist("vtx","zVtx","zVtx","#Counts",100,-20,20,kBlack);
	vtx1 = makeHist("vtx1","zVtx1","zVtx","#Counts",100,-20,20,kRed);

	ana->Draw("zVtx>>vtx", "highPurity == 1");
	hydjet->Draw("zVtx>>vtx1", "highPurity == 1");

	vtx->Scale(1/(vtx->Integral()));
	vtx1->Scale(1/(vtx1->Integral()));

	TF1 * tmp = new TF1("tmp", "gaus");
	TF1 * tmp1 = new TF1("tmp1", "gaus");

	vtx->Fit("tmp","","",-15,15);
	vtx1->Fit("tmp1","","",-15,15);

	tmp =(TF1*) vtx->GetFunction("tmp");
	tmp1 =(TF1*) vtx1->GetFunction("tmp1");


	double A, mean, sigma;
	A = tmp->GetParameter(0);
	mean = tmp->GetParameter(1);
	sigma = tmp->GetParameter(2);
	cout << "A: " << A << endl;
	cout << "mean: " << mean << endl;
	cout << "sigma: " << sigma << endl;


	double A1, mean1, sigma1;
	A1 = tmp1->GetParameter(0);
	mean1 = tmp1->GetParameter(1);
	sigma1= tmp1->GetParameter(2);
	cout << "A1: " << A1 << endl;
	cout << "mean1: " << mean1 << endl;
	cout << "sigma1: " << sigma1 << endl;

	vtx->Draw("P");
	vtx1->Draw("Psame");


}