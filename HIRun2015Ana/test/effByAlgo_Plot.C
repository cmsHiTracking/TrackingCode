#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TAttLine.h"
#include "TAttFill.h"
#include "TAttMarker.h"
#include "TAxis.h"
#include "TLegend.h"

//plots stacked histograms for efficiency by algorith
//eta cut will apply an eta cut, same for pt
//can be run on teh output of HITrackAnalyzerByAlgo or if you want to run on crab, hadd all the outputs before running this
//expects the input file to be 'trk.root'
//output expects a directory called "plots/"
//for some reason, the macro doesn't want to compile (but runs interactively...)

void effByAlgo_Plot(float etaCut = 2.4, float ptCut = 0, bool onlyInclusive = false){

  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0.);
  //largest value of X in 'heffX' minus 1
  const int nIterations = 10;

  TH2D * hsim[20];
  TH2D * hrec[20];
  TH2D * hfak[20];
  TH2D * heff[20];
  TH2D * hsec[20];
  
  TH1D * hsimPt[20];
  TH1D * hrecPt[20];
  TH1D * hfakPt[20];
  TH1D * heffPt[20];
  TH1D * hsecPt[20];
  TH1D * hsimEta[20];
  TH1D * hrecEta[20];
  TH1D * hfakEta[20];
  TH1D * heffEta[20];
  TH1D * hsecEta[20];

  const int nptBins = 51;
  const float ptBins[nptBins] = {
        0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45,
        0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95,
        1.0, 1.05, 1.1, 1.15, 1.2,
        1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
        2.5, 3.0, 4.0, 5.0, 7.5, 10.0, 12.0, 15.0,
        20.0, 25.0, 30.0, 45.0, 60.0, 90.0, 120.0, 
        180.0, 300.0, 500.0};
  const int netaBins = 13;
  const float etaBins[netaBins] = {
        -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0.0,
        0.4, 0.8, 1.2, 1.6, 2.0, 2.4};

  TFile * f;
  f = TFile::Open("trk.root","read");
  hsim[0] = (TH2D*)f->Get("HITrackCorrectionsByAlgo/hsim");
  hrec[0] = (TH2D*)f->Get("HITrackCorrectionsByAlgo/hrec");
  hfak[0] = (TH2D*)f->Get("HITrackCorrectionsByAlgo/hfak"); 
  heff[0] = (TH2D*)f->Get("HITrackCorrectionsByAlgo/heff"); 
  hsec[0] = (TH2D*)f->Get("HITrackCorrectionsByAlgo/hsec"); 
  hsim[0]->SetDirectory(0);
  hrec[0]->SetDirectory(0);
  hfak[0]->SetDirectory(0);
  heff[0]->SetDirectory(0);
  hsec[0]->SetDirectory(0);

  if(!onlyInclusive){
  for(int i = 0; i<nIterations; i++){
    //hsim[i+1] = (TH2D*)f->Get(Form("HITrackCorrections/hsim%d");
    //hrec[i+1] = (TH2D*)f->Get(Form("HITrackCorrections/hrec%d");
    hfak[i+1] = (TH2D*)f->Get(Form("HITrackCorrectionsByAlgo/hfak%d",i)); 
    heff[i+1] = (TH2D*)f->Get(Form("HITrackCorrectionsByAlgo/heff%d",i)); 
    hsec[i+1] = (TH2D*)f->Get(Form("HITrackCorrectionsByAlgo/hsec%d",i)); 
    //hsim[i+1]->SetDirectory(0);
    //hrec[i+1]->SetDirectory(0);
    hfak[i+1]->SetDirectory(0);
    heff[i+1]->SetDirectory(0);
    hsec[i+1]->SetDirectory(0);
  }
  }
  f->Close();   

  TFile * f1 = TFile::Open("effByAlgo.root","recreate");
  for(int i = 0; i<nIterations+1; i++){
    if(onlyInclusive && i>0) continue;
    //defining profiles
    hsimPt[i] = new TH1D(Form("hsimPt%d",i),"",nptBins-1,ptBins);
    hrecPt[i] = new TH1D(Form("hrecPt%d",i),"",nptBins-1,ptBins);
    hfakPt[i] = new TH1D(Form("hfakPt%d",i),"",nptBins-1,ptBins);
    heffPt[i] = new TH1D(Form("heffPt%d",i),"",nptBins-1,ptBins);
    hsecPt[i] = new TH1D(Form("hsecPt%d",i),"",nptBins-1,ptBins);
    hsimEta[i] = new TH1D(Form("hsimEta%d",i),"",netaBins-1,etaBins);
    hrecEta[i] = new TH1D(Form("hrecEta%d",i),"",netaBins-1,etaBins);
    hfakEta[i] = new TH1D(Form("hfakEta%d",i),"",netaBins-1,etaBins);
    heffEta[i] = new TH1D(Form("heffEta%d",i),"",netaBins-1,etaBins);
    hsecEta[i] = new TH1D(Form("hsecEta%d",i),"",netaBins-1,etaBins);

    //making profiles
    for(int j = 0; j<hsim[0]->GetXaxis()->GetNbins()+2; j++){//eta
      if(TMath::Abs(hsim[0]->GetXaxis()->GetBinCenter(j))>etaCut) continue;
      for(int k = 0; k<hsim[0]->GetYaxis()->GetNbins()+2; k++){//pt
        if((hsim[0]->GetYaxis()->GetBinCenter(k))<ptCut) continue;
        if(i==0){
          hsimPt[i]->SetBinContent(k,hsim[i]->GetBinContent(j,k)+hsimPt[i]->GetBinContent(k));
          hrecPt[i]->SetBinContent(k,hrec[i]->GetBinContent(j,k)+hrecPt[i]->GetBinContent(k));
          hsimPt[i]->SetBinError(k,hsim[i]->GetBinError(j,k)+hsimPt[i]->GetBinError(k));
          hrecPt[i]->SetBinError(k,hrec[i]->GetBinError(j,k)+hrecPt[i]->GetBinError(k));
        }
        hfakPt[i]->SetBinContent(k,hfak[i]->GetBinContent(j,k)+hfakPt[i]->GetBinContent(k));
        heffPt[i]->SetBinContent(k,heff[i]->GetBinContent(j,k)+heffPt[i]->GetBinContent(k));
        hsecPt[i]->SetBinContent(k,hsec[i]->GetBinContent(j,k)+hsecPt[i]->GetBinContent(k));
        hfakPt[i]->SetBinError(k,hfak[i]->GetBinError(j,k)+hfakPt[i]->GetBinError(k));
        heffPt[i]->SetBinError(k,heff[i]->GetBinError(j,k)+heffPt[i]->GetBinError(k));
        hsecPt[i]->SetBinError(k,hsec[i]->GetBinError(j,k)+hsecPt[i]->GetBinError(k));
       
        if(i==0){ 
          hsimEta[i]->SetBinContent(j,hsim[i]->GetBinContent(j,k)+hsimEta[i]->GetBinContent(j));
          hrecEta[i]->SetBinContent(j,hrec[i]->GetBinContent(j,k)+hrecEta[i]->GetBinContent(j));
          hsimEta[i]->SetBinError(j,hsim[i]->GetBinError(j,k)+hsimEta[i]->GetBinError(j));
          hrecEta[i]->SetBinError(j,hrec[i]->GetBinError(j,k)+hrecEta[i]->GetBinError(j));
        }
        hfakEta[i]->SetBinContent(j,hfak[i]->GetBinContent(j,k)+hfakEta[i]->GetBinContent(j));
        heffEta[i]->SetBinContent(j,heff[i]->GetBinContent(j,k)+heffEta[i]->GetBinContent(j));
        hsecEta[i]->SetBinContent(j,hsec[i]->GetBinContent(j,k)+hsecEta[i]->GetBinContent(j));
        hfakEta[i]->SetBinError(j,hfak[i]->GetBinError(j,k)+hfakEta[i]->GetBinError(j));
        heffEta[i]->SetBinError(j,heff[i]->GetBinError(j,k)+heffEta[i]->GetBinError(j));
        hsecEta[i]->SetBinError(j,hsec[i]->GetBinError(j,k)+hsecEta[i]->GetBinError(j));
      }
    }
    heffPt[i]->Divide(hsimPt[0]);
    hfakPt[i]->Divide(hrecPt[0]);
    hsecPt[i]->Divide(hrecPt[0]);
    heffEta[i]->Divide(hsimEta[0]);
    hfakEta[i]->Divide(hrecEta[0]);
    hsecEta[i]->Divide(hrecEta[0]);
    heffPt[i]->Write();
    hfakPt[i]->Write();
    hsecPt[i]->Write();
    heffEta[i]->Write();
    hfakEta[i]->Write();
    hsecEta[i]->Write();
  }

  //pteff
  TCanvas * c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogx();
  heffPt[0]->GetXaxis()->SetTitle("p_{T} (GeV)");
  heffPt[0]->GetXaxis()->CenterTitle();
  heffPt[0]->GetYaxis()->SetTitle("Efficiency");
  heffPt[0]->GetYaxis()->CenterTitle();
  heffPt[0]->GetYaxis()->SetRangeUser(0,1.2);
  heffPt[0]->GetXaxis()->SetRangeUser(0.3,10);
  heffPt[0]->SetLineColor(kBlack);
  heffPt[0]->SetLineWidth(1);
  heffPt[0]->SetMarkerStyle(8);
  heffPt[0]->SetMarkerColor(kBlack);
  heffPt[0]->Draw();

  //stacking histograms
  if(!onlyInclusive){
  heffPt[0]->SetLineColor(kBlack);
  heffPt[0]->SetLineWidth(1);
  heffPt[0]->SetFillColor(40);
  heffPt[0]->Draw("same hist"); 
  heffPt[10]->SetLineColor(kBlack);
  heffPt[10]->SetLineWidth(1);
  heffPt[10]->SetFillColor(41);
  heffPt[10]->Draw("same hist");
  heffPt[9]->SetLineColor(kBlack);
  heffPt[9]->SetLineWidth(1);
  heffPt[9]->SetFillColor(20);
  heffPt[9]->Draw("same hist");
  heffPt[8]->SetLineColor(kBlack);
  heffPt[8]->SetLineWidth(1);
  heffPt[8]->SetFillColor(28);
  heffPt[8]->Draw("same hist");
  heffPt[7]->SetLineColor(kBlack);
  heffPt[7]->SetLineWidth(1);
  heffPt[7]->SetFillColor(44);
  heffPt[7]->Draw("same hist");
  heffPt[6]->SetLineColor(kBlack);
  heffPt[6]->SetLineWidth(1);
  heffPt[6]->SetFillColor(32);
  heffPt[6]->Draw("same hist");
  heffPt[5]->SetLineColor(kBlack);
  heffPt[5]->SetLineWidth(1);
  heffPt[5]->SetFillColor(29);
  heffPt[5]->Draw("same hist");
  heffPt[4]->SetLineColor(kBlack);
  heffPt[4]->SetLineWidth(1);
  heffPt[4]->SetFillColor(46);
  heffPt[4]->Draw("same hist");
  heffPt[3]->SetLineColor(kBlack);
  heffPt[3]->SetLineWidth(1);
  heffPt[3]->SetFillColor(kBlue-2);
  heffPt[3]->Draw("same hist");
  heffPt[2]->SetLineColor(kBlack);
  heffPt[2]->SetLineWidth(1);
  heffPt[2]->SetFillColor(38);
  heffPt[2]->Draw("same hist");
  heffPt[1]->SetLineColor(kBlack);
  heffPt[1]->SetLineWidth(1);
  heffPt[1]->SetFillColor(33);
  heffPt[1]->Draw("same hist");
  heffPt[0]->Draw("same p");
  c1->RedrawAxis();

  TLegend * leg = new TLegend(0.15,0.6,0.35,0.85);
  leg->AddEntry(heffPt[0],"All Iterations","p");
  leg->AddEntry(heffPt[1],"hiBasicTracking","f");
  leg->AddEntry(heffPt[2],"hiLowPtQuadStep","f");
  leg->AddEntry(heffPt[3],"hiHighPtTripletStep","f");
  leg->AddEntry(heffPt[4],"hiDetachedQuadStep","f");
  leg->AddEntry(heffPt[5],"hiDetachedTripletStep","f");
  leg->AddEntry(heffPt[6],"hiLowPtTripletStep","f");
  leg->AddEntry(heffPt[7],"hiMixedTripletStep","f");
  leg->AddEntry(heffPt[8],"hiPixellessStep","f");
  leg->AddEntry(heffPt[9],"hiTobTecStep","f");
  leg->AddEntry(heffPt[10],"hiJetCoreRegionalStep","f");
  leg->AddEntry(heffPt[0],"hiRegitMuTrackingAndSta","f");
  leg->Draw("same");
 
  c1->SaveAs(Form("plots/pTEffByIteration_%d_%d.png",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/pTEffByIteration_%d_%d.pdf",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/pTEffByIteration_%d_%d.C",(int)(ptCut*10),(int)(etaCut*10))); 
  delete leg;
  }
  delete c1;


  //etaeff
  c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogx(0);
  heffEta[0]->GetXaxis()->SetTitle("#eta");
  heffEta[0]->GetXaxis()->CenterTitle();
  heffEta[0]->GetYaxis()->SetTitle("Efficiency");
  heffEta[0]->GetYaxis()->CenterTitle();
  heffEta[0]->GetYaxis()->SetRangeUser(0,1.2);
  heffEta[0]->GetXaxis()->SetRangeUser(-2.4,2.4);
  heffEta[0]->SetLineColor(kBlack);
  heffEta[0]->SetLineWidth(1);
  heffEta[0]->SetMarkerStyle(8);
  heffEta[0]->SetMarkerColor(kBlack);
  heffEta[0]->Draw();

  //stacking histograms
  if(!onlyInclusive){
  heffEta[0]->SetLineColor(kBlack);
  heffEta[0]->SetLineWidth(1);
  heffEta[0]->SetFillColor(40);
  heffEta[0]->Draw("same hist"); 
  heffEta[10]->SetLineColor(kBlack);
  heffEta[10]->SetLineWidth(1);
  heffEta[10]->SetFillColor(41);
  heffEta[10]->Draw("same hist");
  heffEta[9]->SetLineColor(kBlack);
  heffEta[9]->SetLineWidth(1);
  heffEta[9]->SetFillColor(20);
  heffEta[9]->Draw("same hist");
  heffEta[8]->SetLineColor(kBlack);
  heffEta[8]->SetLineWidth(1);
  heffEta[8]->SetFillColor(28);
  heffEta[8]->Draw("same hist");
  heffEta[7]->SetLineColor(kBlack);
  heffEta[7]->SetLineWidth(1);
  heffEta[7]->SetFillColor(44);
  heffEta[7]->Draw("same hist");
  heffEta[6]->SetLineColor(kBlack);
  heffEta[6]->SetLineWidth(1);
  heffEta[6]->SetFillColor(32);
  heffEta[6]->Draw("same hist");
  heffEta[5]->SetLineColor(kBlack);
  heffEta[5]->SetLineWidth(1);
  heffEta[5]->SetFillColor(29);
  heffEta[5]->Draw("same hist");
  heffEta[4]->SetLineColor(kBlack);
  heffEta[4]->SetLineWidth(1);
  heffEta[4]->SetFillColor(46);
  heffEta[4]->Draw("same hist");
  heffEta[3]->SetLineColor(kBlack);
  heffEta[3]->SetLineWidth(1);
  heffEta[3]->SetFillColor(kBlue-2);
  heffEta[3]->Draw("same hist");
  heffEta[2]->SetLineColor(kBlack);
  heffEta[2]->SetLineWidth(1);
  heffEta[2]->SetFillColor(38);
  heffEta[2]->Draw("same hist");
  heffEta[1]->SetLineColor(kBlack);
  heffEta[1]->SetLineWidth(1);
  heffEta[1]->SetFillColor(33);
  heffEta[1]->Draw("same hist");
  heffEta[0]->Draw("same p");
  c1->RedrawAxis();

  leg = new TLegend(0.15,0.6,0.35,0.85);
  leg->AddEntry(heffEta[0],"All Iterations","p");
  leg->AddEntry(heffEta[1],"hiBasicTracking","f");
  leg->AddEntry(heffEta[2],"hiLowPtQuadStep","f");
  leg->AddEntry(heffEta[3],"hiHighPtTripletStep","f");
  leg->AddEntry(heffEta[4],"hiDetachedQuadStep","f");
  leg->AddEntry(heffEta[5],"hiDetachedTripletStep","f");
  leg->AddEntry(heffEta[6],"hiLowPtTripletStep","f");
  leg->AddEntry(heffEta[7],"hiMixedTripletStep","f");
  leg->AddEntry(heffEta[8],"hiPixellessStep","f");
  leg->AddEntry(heffEta[9],"hiTobTecStep","f");
  leg->AddEntry(heffEta[10],"hiJetCoreRegionalStep","f");
  leg->AddEntry(heffEta[0],"hiRegitMuTrackingAndSta","f");
  leg->Draw("same");
 
  c1->SaveAs(Form("plots/EtaEffByIteration_%d_%d.png",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/EtaEffByIteration_%d_%d.pdf",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/EtaEffByIteration_%d_%d.C",(int)(ptCut*10),(int)(etaCut*10))); 
  delete leg;
  }
  delete c1;
  
  //ptfake
  c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogx();
  hfakPt[0]->GetXaxis()->SetTitle("p_{T} (GeV)");
  hfakPt[0]->GetXaxis()->CenterTitle();
  hfakPt[0]->GetYaxis()->SetTitle("Fake Rate");
  hfakPt[0]->GetYaxis()->CenterTitle();
  hfakPt[0]->GetYaxis()->SetRangeUser(0,1.8);
  hfakPt[0]->GetXaxis()->SetRangeUser(0.3,10);
  hfakPt[0]->SetLineColor(kBlack);
  hfakPt[0]->SetLineWidth(1);
  hfakPt[0]->SetMarkerStyle(8);
  hfakPt[0]->SetMarkerColor(kBlack);
  hfakPt[0]->Draw();

  //stacking histograms
  if(!onlyInclusive){
  hfakPt[0]->SetLineColor(kBlack);
  hfakPt[0]->SetLineWidth(1);
  hfakPt[0]->SetFillColor(40);
  hfakPt[0]->Draw("same hist"); 
  hfakPt[10]->SetLineColor(kBlack);
  hfakPt[10]->SetLineWidth(1);
  hfakPt[10]->SetFillColor(41);
  hfakPt[10]->Draw("same hist");
  hfakPt[9]->SetLineColor(kBlack);
  hfakPt[9]->SetLineWidth(1);
  hfakPt[9]->SetFillColor(20);
  hfakPt[9]->Draw("same hist");
  hfakPt[8]->SetLineColor(kBlack);
  hfakPt[8]->SetLineWidth(1);
  hfakPt[8]->SetFillColor(28);
  hfakPt[8]->Draw("same hist");
  hfakPt[7]->SetLineColor(kBlack);
  hfakPt[7]->SetLineWidth(1);
  hfakPt[7]->SetFillColor(44);
  hfakPt[7]->Draw("same hist");
  hfakPt[6]->SetLineColor(kBlack);
  hfakPt[6]->SetLineWidth(1);
  hfakPt[6]->SetFillColor(32);
  hfakPt[6]->Draw("same hist");
  hfakPt[5]->SetLineColor(kBlack);
  hfakPt[5]->SetLineWidth(1);
  hfakPt[5]->SetFillColor(29);
  hfakPt[5]->Draw("same hist");
  hfakPt[4]->SetLineColor(kBlack);
  hfakPt[4]->SetLineWidth(1);
  hfakPt[4]->SetFillColor(46);
  hfakPt[4]->Draw("same hist");
  hfakPt[3]->SetLineColor(kBlack);
  hfakPt[3]->SetLineWidth(1);
  hfakPt[3]->SetFillColor(kBlue-2);
  hfakPt[3]->Draw("same hist");
  hfakPt[2]->SetLineColor(kBlack);
  hfakPt[2]->SetLineWidth(1);
  hfakPt[2]->SetFillColor(38);
  hfakPt[2]->Draw("same hist");
  hfakPt[1]->SetLineColor(kBlack);
  hfakPt[1]->SetLineWidth(1);
  hfakPt[1]->SetFillColor(33);
  hfakPt[1]->Draw("same hist");
  hfakPt[0]->Draw("same p");
  c1->RedrawAxis();

  leg = new TLegend(0.15,0.6,0.35,0.85);
  leg->AddEntry(hfakPt[0],"All Iterations","p");
  leg->AddEntry(hfakPt[1],"hiBasicTracking","f");
  leg->AddEntry(hfakPt[2],"hiLowPtQuadStep","f");
  leg->AddEntry(hfakPt[3],"hiHighPtTripletStep","f");
  leg->AddEntry(hfakPt[4],"hiDetachedQuadStep","f");
  leg->AddEntry(hfakPt[5],"hiDetachedTripletStep","f");
  leg->AddEntry(hfakPt[6],"hiLowPtTripletStep","f");
  leg->AddEntry(hfakPt[7],"hiMixedTripletStep","f");
  leg->AddEntry(hfakPt[8],"hiPixellessStep","f");
  leg->AddEntry(hfakPt[9],"hiTobTecStep","f");
  leg->AddEntry(hfakPt[10],"hiJetCoreRegionalStep","f");
  leg->AddEntry(hfakPt[0],"hiRegitMuTrackingAndSta","f");
  leg->Draw("same");
 
  c1->SaveAs(Form("plots/pTFakByIteration_%d_%d.png",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/pTFakByIteration_%d_%d.pdf",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/pTFakByIteration_%d_%d.C",(int)(ptCut*10),(int)(etaCut*10))); 
  delete leg;
  }
  delete c1;
  

  //etafak
  c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogx(0);
  hfakEta[0]->GetXaxis()->SetTitle("#eta");
  hfakEta[0]->GetXaxis()->CenterTitle();
  hfakEta[0]->GetYaxis()->SetTitle("Fake Rate");
  hfakEta[0]->GetYaxis()->CenterTitle();
  hfakEta[0]->GetYaxis()->SetRangeUser(0,1.4);
  hfakEta[0]->GetXaxis()->SetRangeUser(-2.4,2.4);
  hfakEta[0]->SetLineColor(kBlack);
  hfakEta[0]->SetLineWidth(1);
  hfakEta[0]->SetMarkerStyle(8);
  hfakEta[0]->SetMarkerColor(kBlack);
  hfakEta[0]->Draw();

  //stacking histograms
  if(!onlyInclusive){
  hfakEta[0]->SetLineColor(kBlack);
  hfakEta[0]->SetLineWidth(1);
  hfakEta[0]->SetFillColor(40);
  hfakEta[0]->Draw("same hist"); 
  hfakEta[10]->SetLineColor(kBlack);
  hfakEta[10]->SetLineWidth(1);
  hfakEta[10]->SetFillColor(41);
  hfakEta[10]->Draw("same hist");
  hfakEta[9]->SetLineColor(kBlack);
  hfakEta[9]->SetLineWidth(1);
  hfakEta[9]->SetFillColor(20);
  hfakEta[9]->Draw("same hist");
  hfakEta[8]->SetLineColor(kBlack);
  hfakEta[8]->SetLineWidth(1);
  hfakEta[8]->SetFillColor(28);
  hfakEta[8]->Draw("same hist");
  hfakEta[7]->SetLineColor(kBlack);
  hfakEta[7]->SetLineWidth(1);
  hfakEta[7]->SetFillColor(44);
  hfakEta[7]->Draw("same hist");
  hfakEta[6]->SetLineColor(kBlack);
  hfakEta[6]->SetLineWidth(1);
  hfakEta[6]->SetFillColor(32);
  hfakEta[6]->Draw("same hist");
  hfakEta[5]->SetLineColor(kBlack);
  hfakEta[5]->SetLineWidth(1);
  hfakEta[5]->SetFillColor(29);
  hfakEta[5]->Draw("same hist");
  hfakEta[4]->SetLineColor(kBlack);
  hfakEta[4]->SetLineWidth(1);
  hfakEta[4]->SetFillColor(46);
  hfakEta[4]->Draw("same hist");
  hfakEta[3]->SetLineColor(kBlack);
  hfakEta[3]->SetLineWidth(1);
  hfakEta[3]->SetFillColor(kBlue-2);
  hfakEta[3]->Draw("same hist");
  hfakEta[2]->SetLineColor(kBlack);
  hfakEta[2]->SetLineWidth(1);
  hfakEta[2]->SetFillColor(38);
  hfakEta[2]->Draw("same hist");
  hfakEta[1]->SetLineColor(kBlack);
  hfakEta[1]->SetLineWidth(1);
  hfakEta[1]->SetFillColor(33);
  hfakEta[1]->Draw("same hist");
  hfakEta[0]->Draw("same p");
  c1->RedrawAxis();

  leg = new TLegend(0.15,0.6,0.35,0.85);
  leg->AddEntry(hfakEta[0],"All Iterations","p");
  leg->AddEntry(hfakEta[1],"hiBasicTracking","f");
  leg->AddEntry(hfakEta[2],"hiLowPtQuadStep","f");
  leg->AddEntry(hfakEta[3],"hiHighPtTripletStep","f");
  leg->AddEntry(hfakEta[4],"hiDetachedQuadStep","f");
  leg->AddEntry(hfakEta[5],"hiDetachedTripletStep","f");
  leg->AddEntry(hfakEta[6],"hiLowPtTripletStep","f");
  leg->AddEntry(hfakEta[7],"hiMixedTripletStep","f");
  leg->AddEntry(hfakEta[8],"hiPixellessStep","f");
  leg->AddEntry(hfakEta[9],"hiTobTecStep","f");
  leg->AddEntry(hfakEta[10],"hiJetCoreRegionalStep","f");
  leg->AddEntry(hfakEta[0],"hiRegitMuTrackingAndSta","f");
  leg->Draw("same");
 
  c1->SaveAs(Form("plots/EtaFakByIteration_%d_%d.png",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/EtaFakByIteration_%d_%d.pdf",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/EtaFakByIteration_%d_%d.C",(int)(ptCut*10),(int)(etaCut*10))); 
  delete leg;
  }
  delete c1;

  //ptsece
  c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogx();
  hsecPt[0]->GetXaxis()->SetTitle("p_{T} (GeV)");
  hsecPt[0]->GetXaxis()->CenterTitle();
  hsecPt[0]->GetYaxis()->SetTitle("Secondary Rate");
  hsecPt[0]->GetYaxis()->CenterTitle();
  hsecPt[0]->GetYaxis()->SetRangeUser(0,0.2);
  hsecPt[0]->GetXaxis()->SetRangeUser(0.3,10);
  hsecPt[0]->SetLineColor(kBlack);
  hsecPt[0]->SetLineWidth(1);
  hsecPt[0]->SetMarkerStyle(8);
  hsecPt[0]->SetMarkerColor(kBlack);
  hsecPt[0]->Draw();

  //stacking histograms
  if(!onlyInclusive){
  hsecPt[0]->SetLineColor(kBlack);
  hsecPt[0]->SetLineWidth(1);
  hsecPt[0]->SetFillColor(40);
  hsecPt[0]->Draw("same hist"); 
  hsecPt[10]->SetLineColor(kBlack);
  hsecPt[10]->SetLineWidth(1);
  hsecPt[10]->SetFillColor(41);
  hsecPt[10]->Draw("same hist");
  hsecPt[9]->SetLineColor(kBlack);
  hsecPt[9]->SetLineWidth(1);
  hsecPt[9]->SetFillColor(20);
  hsecPt[9]->Draw("same hist");
  hsecPt[8]->SetLineColor(kBlack);
  hsecPt[8]->SetLineWidth(1);
  hsecPt[8]->SetFillColor(28);
  hsecPt[8]->Draw("same hist");
  hsecPt[7]->SetLineColor(kBlack);
  hsecPt[7]->SetLineWidth(1);
  hsecPt[7]->SetFillColor(44);
  hsecPt[7]->Draw("same hist");
  hsecPt[6]->SetLineColor(kBlack);
  hsecPt[6]->SetLineWidth(1);
  hsecPt[6]->SetFillColor(32);
  hsecPt[6]->Draw("same hist");
  hsecPt[5]->SetLineColor(kBlack);
  hsecPt[5]->SetLineWidth(1);
  hsecPt[5]->SetFillColor(29);
  hsecPt[5]->Draw("same hist");
  hsecPt[4]->SetLineColor(kBlack);
  hsecPt[4]->SetLineWidth(1);
  hsecPt[4]->SetFillColor(46);
  hsecPt[4]->Draw("same hist");
  hsecPt[3]->SetLineColor(kBlack);
  hsecPt[3]->SetLineWidth(1);
  hsecPt[3]->SetFillColor(kBlue-2);
  hsecPt[3]->Draw("same hist");
  hsecPt[2]->SetLineColor(kBlack);
  hsecPt[2]->SetLineWidth(1);
  hsecPt[2]->SetFillColor(38);
  hsecPt[2]->Draw("same hist");
  hsecPt[1]->SetLineColor(kBlack);
  hsecPt[1]->SetLineWidth(1);
  hsecPt[1]->SetFillColor(33);
  hsecPt[1]->Draw("same hist");
  hsecPt[0]->Draw("same p");
  c1->RedrawAxis();

  leg = new TLegend(0.15,0.6,0.35,0.85);
  leg->AddEntry(hsecPt[0],"All Iterations","p");
  leg->AddEntry(hsecPt[1],"hiBasicTracking","f");
  leg->AddEntry(hsecPt[2],"hiLowPtQuadStep","f");
  leg->AddEntry(hsecPt[3],"hiHighPtTripletStep","f");
  leg->AddEntry(hsecPt[4],"hiDetachedQuadStep","f");
  leg->AddEntry(hsecPt[5],"hiDetachedTripletStep","f");
  leg->AddEntry(hsecPt[6],"hiLowPtTripletStep","f");
  leg->AddEntry(hsecPt[7],"hiMixedTripletStep","f");
  leg->AddEntry(hsecPt[8],"hiPixellessStep","f");
  leg->AddEntry(hsecPt[9],"hiTobTecStep","f");
  leg->AddEntry(hsecPt[10],"hiJetCoreRegionalStep","f");
  leg->AddEntry(hsecPt[0],"hiRegitMuTrackingAndSta","f");
  leg->Draw("same");
 
  c1->SaveAs(Form("plots/pTSecByIteration_%d_%d.png",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/pTSecByIteration_%d_%d.pdf",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/pTSecByIteration_%d_%d.C",(int)(ptCut*10),(int)(etaCut*10))); 
  delete leg;
  }
  delete c1;
  

  //etasec
  c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogx(0);
  hsecEta[0]->GetXaxis()->SetTitle("#eta");
  hsecEta[0]->GetXaxis()->CenterTitle();
  hsecEta[0]->GetYaxis()->SetTitle("Secondary Rate");
  hsecEta[0]->GetYaxis()->CenterTitle();
  hsecEta[0]->GetYaxis()->SetRangeUser(0,0.2);
  hsecEta[0]->GetXaxis()->SetRangeUser(-2.4,2.4);
  hsecEta[0]->SetLineColor(kBlack);
  hsecEta[0]->SetLineWidth(1);
  hsecEta[0]->SetMarkerStyle(8);
  hsecEta[0]->SetMarkerColor(kBlack);
  hsecEta[0]->Draw();

  //stacking histograms
  if(!onlyInclusive){
  hsecEta[0]->SetLineColor(kBlack);
  hsecEta[0]->SetLineWidth(1);
  hsecEta[0]->SetFillColor(40);
  hsecEta[0]->Draw("same hist"); 
  hsecEta[10]->SetLineColor(kBlack);
  hsecEta[10]->SetLineWidth(1);
  hsecEta[10]->SetFillColor(41);
  hsecEta[10]->Draw("same hist");
  hsecEta[9]->SetLineColor(kBlack);
  hsecEta[9]->SetLineWidth(1);
  hsecEta[9]->SetFillColor(20);
  hsecEta[9]->Draw("same hist");
  hsecEta[8]->SetLineColor(kBlack);
  hsecEta[8]->SetLineWidth(1);
  hsecEta[8]->SetFillColor(28);
  hsecEta[8]->Draw("same hist");
  hsecEta[7]->SetLineColor(kBlack);
  hsecEta[7]->SetLineWidth(1);
  hsecEta[7]->SetFillColor(44);
  hsecEta[7]->Draw("same hist");
  hsecEta[6]->SetLineColor(kBlack);
  hsecEta[6]->SetLineWidth(1);
  hsecEta[6]->SetFillColor(32);
  hsecEta[6]->Draw("same hist");
  hsecEta[5]->SetLineColor(kBlack);
  hsecEta[5]->SetLineWidth(1);
  hsecEta[5]->SetFillColor(29);
  hsecEta[5]->Draw("same hist");
  hsecEta[4]->SetLineColor(kBlack);
  hsecEta[4]->SetLineWidth(1);
  hsecEta[4]->SetFillColor(46);
  hsecEta[4]->Draw("same hist");
  hsecEta[3]->SetLineColor(kBlack);
  hsecEta[3]->SetLineWidth(1);
  hsecEta[3]->SetFillColor(kBlue-2);
  hsecEta[3]->Draw("same hist");
  hsecEta[2]->SetLineColor(kBlack);
  hsecEta[2]->SetLineWidth(1);
  hsecEta[2]->SetFillColor(38);
  hsecEta[2]->Draw("same hist");
  hsecEta[1]->SetLineColor(kBlack);
  hsecEta[1]->SetLineWidth(1);
  hsecEta[1]->SetFillColor(33);
  hsecEta[1]->Draw("same hist");
  hsecEta[0]->Draw("same p");
  c1->RedrawAxis();

  leg = new TLegend(0.15,0.6,0.35,0.85);
  leg->AddEntry(hsecEta[0],"All Iterations","p");
  leg->AddEntry(hsecEta[1],"hiBasicTracking","f");
  leg->AddEntry(hsecEta[2],"hiLowPtQuadStep","f");
  leg->AddEntry(hsecEta[3],"hiHighPtTripletStep","f");
  leg->AddEntry(hsecEta[4],"hiDetachedQuadStep","f");
  leg->AddEntry(hsecEta[5],"hiDetachedTripletStep","f");
  leg->AddEntry(hsecEta[6],"hiLowPtTripletStep","f");
  leg->AddEntry(hsecEta[7],"hiMixedTripletStep","f");
  leg->AddEntry(hsecEta[8],"hiPixellessStep","f");
  leg->AddEntry(hsecEta[9],"hiTobTecStep","f");
  leg->AddEntry(hsecEta[10],"hiJetCoreRegionalStep","f");
  leg->AddEntry(hsecEta[0],"hiRegitMuTrackingAndSta","f");
  leg->Draw("same");
 
  c1->SaveAs(Form("plots/EtaSecByIteration_%d_%d.png",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/EtaSecByIteration_%d_%d.pdf",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/EtaSecByIteration_%d_%d.C",(int)(ptCut*10),(int)(etaCut*10))); 
  //delete leg;
  }
  //delete c1;
}
