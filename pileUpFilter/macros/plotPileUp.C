#include "RiceStyle.h"

using namespace std;

const int MAX = 4;

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

	TFile* file1 = new TFile("../rootfile/pileUpFilterEfficiency_updateMC1_v2.root");
	TFile* file2 = new TFile("../rootfile/pileUpFilterEfficiency_updateMC2_v2.root");
	TFile* file3 = new TFile("../rootfile/pileUpFilterEfficiency_updateMC3_v2.root");
	TFile* file4 = new TFile("../rootfile/pileUpFilterEfficiency_updateData_272274_v2.root");

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

	TLatex * t1[4];
	TLatex * t2[4];
	TLatex * t3[4];
	TLatex * t4[4];

	t1[0] = new TLatex(0.4,0.3,"x0");
	t1[1] = new TLatex(1.4,0.9,"x1");
	t1[2] = new TLatex(2.4,0.1,"x2");
	t1[3] = new TLatex(3.4,0.1,"x3");

	t2[0] = new TLatex(0.4,0.1,"y0");
	t2[1] = new TLatex(1.4,0.4,"y1");
	t2[2] = new TLatex(2.4,0.7,"y2");
	t2[3] = new TLatex(3.4,0.1,"y3");

	t3[0] = new TLatex(0.4,0.1,"z0");
	t3[1] = new TLatex(1.4,0.2,"z1");
	t3[2] = new TLatex(2.4,0.5,"z2");
	t3[3] = new TLatex(3.4,0.6,"z3");

	t4[0] = new TLatex(0.4,0.5,"d0");
	t4[1] = new TLatex(1.4,0.5,"d1");
	t4[2] = new TLatex(2.4,0.2,"d2");
	t4[3] = new TLatex(3.4,0.1,"d3");


	TCanvas* c1 = makeMultiCanvas("c1","",2,2);
	c1->cd(1);
	gPad->SetBottomMargin(0.13);
	base1->Draw();
	for(int i = 0; i < 4; i++){ t1[i]->Draw("same");};
	vertex1[0]->SetMarkerStyle(20);
	vertex1[0]->Draw("same");
	c1->cd(2);
	gPad->SetBottomMargin(0.13);
	base2->Draw();
	for(int i = 0; i < 4; i++){ t2[i]->Draw("same");};
	vertex2[0]->Draw("same");
	c1->cd(3);
	gPad->SetBottomMargin(0.13);
	base3->Draw();
	for(int i = 0; i < 4; i++){ t3[i]->Draw("same");};
	vertex3[0]->Draw("same");
	c1->cd(4);
	gPad->SetBottomMargin(0.13);
	base4->Draw();
	for(int i = 0; i < 4; i++){ t4[i]->Draw("same");};
	vertexall[0]->Draw("same");

	
	vector<double> q, x, y, z, d;
	q.push_back(1.0); q.push_back(0.); q.push_back(0.); q.push_back(0.);

	for(int i = 1; i < 5 ; i++){

		x.push_back( vertex1[0]->GetBinContent(i) );
		y.push_back( vertex2[0]->GetBinContent(i) );
		z.push_back( vertex3[0]->GetBinContent(i) );
		d.push_back( vertexall[0]->GetBinContent(i) );

	}

	for(int i = 0; i < 4; i++){

		cout << "q_" << i << " is " << q[i] << endl;
		cout << "x_" << i << " is " << x[i] << endl;
		cout << "y_" << i << " is " << y[i] << endl;
		cout << "z_" << i << " is " << z[i] << endl;
		cout << "d_" << i << " is " << d[i] << endl;
	}


	double DD[4][4];
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){

			if(i == 0 ) DD[j][i] = q[j];
			if(i == 1 ) DD[j][i] = x[j];
			if(i == 2 ) DD[j][i] = y[j];
			if(i == 3 ) DD[j][i] = z[j];
		}
	}

	double D0[4][4];
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){

			if(i == 0 ) D0[j][i] = d[j];
			if(i == 1 ) D0[j][i] = x[j];
			if(i == 2 ) D0[j][i] = y[j];
			if(i == 3 ) D0[j][i] = z[j];
		}
	}
	double D1[4][4];
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){

			if(i == 0 ) D1[j][i] = q[j];
			if(i == 1 ) D1[j][i] = d[j];
			if(i == 2 ) D1[j][i] = y[j];
			if(i == 3 ) D1[j][i] = z[j];
		}
	}
	double D2[4][4];
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){

			if(i == 0 ) D2[j][i] = q[j];
			if(i == 1 ) D2[j][i] = x[j];
			if(i == 2 ) D2[j][i] = d[j];
			if(i == 3 ) D2[j][i] = z[j];
		}
	}

	double D3[4][4];
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){

			if(i == 0 ) D3[j][i] = q[j];
			if(i == 1 ) D3[j][i] = x[j];
			if(i == 2 ) D3[j][i] = y[j];
			if(i == 3 ) D3[j][i] = d[j];
		}
	}


	double DDD =  determ(DD, 4);
	double D00 =  determ(D0, 4);
	double D11 =  determ(D1, 4);
	double D22 =  determ(D2, 4);
	double D33 =  determ(D3, 4);

	cout << "c0 = " << D00/DDD << endl;
	cout << "c1 = " << D11/DDD << endl;
	cout << "c2 = " << D22/DDD << endl;
	cout << "c3 = " << D33/DDD << endl;



    
	




}