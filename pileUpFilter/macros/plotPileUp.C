#include "RiceStyle.h"

using namespace std;

const int MAX = 3;

double determ(double a[MAX][MAX],int n) {
  double det=0, p, h, k, i, j, temp[MAX][MAX];
  if(n==1) {
    return a[0][0];
  } else if(n==2) {
    det=(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
    return det;
  } else {
    for(p=0;p<n;p++) {
      h = 0;
      k = 0;
      for(i=1;i<n;i++) {
        for( j=0;j<n;j++) {
          if(j==p) {
            continue;
          }
          temp[h][k] = a[i][j];
          k++;
          if(k==n-1) {
            h++;
            k = 0;
          }
        }
      }
      det=det+a[0][p]*pow(-1,p)*determ(temp,n-1);
    }
    return det;
  }
}

void plotPileUp(){

	TFile* file1 = new TFile("../rootfile/pileUpFilterEfficiency_MC_1.root");
	TFile* file2 = new TFile("../rootfile/pileUpFilterEfficiency_updateMC_2.root");
	TFile* file3 = new TFile("../rootfile/pileUpFilterEfficiency_updateMC_3.root");
	TFile* file4 = new TFile("../rootfile/pileUpFilterEfficiency_updateData_272274.root");

	vector<TH1D*> vertex1 = loadingHistogram(file1, "ana_PbPb","/numberOfVertices", 4);
	vector<TH1D*> vertex2 = loadingHistogram(file2, "ana_PbPb","/numberOfVertices", 4);
	vector<TH1D*> vertex3 = loadingHistogram(file3, "ana_PbPb","/numberOfVertices", 4);
	vector<TH1D*> vertexall = loadingHistogram(file4, "ana_PbPb","/numberOfVertices", 4);

	vertex1[0]->Scale(1/(vertex1[0]->Integral()));
	vertex2[0]->Scale(1/(vertex2[0]->Integral()));
	vertex3[0]->Scale(1/(vertex3[0]->Integral()));
	vertexall[0]->Scale(1/(vertexall[0]->Integral()));

	TH1D* base1 = makeHist("base1","pileup 1","number of vertices","",15,0,5);
	TH1D* base2 = makeHist("base2","pileup 2","number of vertices","",15,0,5);
	TH1D* base3 = makeHist("base3","pileup 3","number of vertices","",15,0,5);
	TH1D* base4 = makeHist("base4","data","number of vertices","",15,0,5);

	base1->GetXaxis()->SetTitleColor(kBlack);
	base2->GetXaxis()->SetTitleColor(kBlack);
	base3->GetXaxis()->SetTitleColor(kBlack);
	base4->GetXaxis()->SetTitleColor(kBlack);


	TCanvas* c1 = makeMultiCanvas("c1","",2,2);
	c1->cd(1);
	gPad->SetBottomMargin(0.13);
	base1->Draw();
	vertex1[0]->Draw("Psame");
	c1->cd(2);
	gPad->SetBottomMargin(0.13);
	base2->Draw();
	vertex2[0]->Draw("Psame");
	c1->cd(3);
	gPad->SetBottomMargin(0.13);
	base3->Draw();
	vertex3[0]->Draw("Psame");
	c1->cd(4);
	gPad->SetBottomMargin(0.13);
	base4->Draw();
	vertexall[0]->Draw("Psame");

	
	vector<double> q, x, y, z, d;
	q.push_back(1.0); q.push_back(0.); q.push_back(0.); q.push_back(0.);

	for(int i = 2; i < 5 ; i++){

		x.push_back( vertex1[0]->GetBinContent(i) );
		y.push_back( vertex2[0]->GetBinContent(i) );
		z.push_back( vertex3[0]->GetBinContent(i) );
		d.push_back( vertexall[0]->GetBinContent(i) );

	}


	double DD[3][3];
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){

			if(i == 0 ) DD[i][j] = x[j];
			if(i == 1 ) DD[i][j] = y[j];
			if(i == 2 ) DD[i][j] = z[j];
		}
	}

	double D0[3][3];
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){

			if(i == 0 ) D0[i][j] = d[j];
			if(i == 1 ) D0[i][j] = y[j];
			if(i == 2 ) D0[i][j] = z[j];
		}
	}
	double D1[3][3];
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){

			if(i == 0 ) D1[i][j] = x[j];
			if(i == 1 ) D1[i][j] = d[j];
			if(i == 2 ) D1[i][j] = z[j];
		}
	}
	double D2[3][3];
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){

			if(i == 0 ) D2[i][j] = x[j];
			if(i == 1 ) D2[i][j] = y[j];
			if(i == 2 ) D2[i][j] = d[j];
		}
	}
	// double D3[3][3];
	// for(int i = 0; i < 4; i++){
	// 	for(int j = 0; j < 4; j++){

	// 		if(i == 0 ) D3[i][j] = q[j];
	// 		if(i == 1 ) D3[i][j] = x[j];
	// 		if(i == 2 ) D3[i][j] = y[j];
	// 		if(i == 3 ) D3[i][j] = d[j];
	// 	}
	// }


	double DDD =  determ(DD, 3);
	double D00 =  determ(D0, 3);
	double D11 =  determ(D1, 3);
	double D22 =  determ(D2, 3);


	cout << "c0 = " << D00/DDD << endl;
	cout << "c1 = " << D11/DDD << endl;
	cout << "c2 = " << D22/DDD << endl;



    
	




}