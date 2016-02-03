#ifndef TRACKCORRECTOR3D_C
#define TRACKCORRECTOR3D_C

#include <string>
#include <iostream>

#include "TFile.h"
#include "TString.h"
#include "TH3.h"
#include "TObject.h"

class TrackCorrector3D 
{
  public:
    TrackCorrector3D();
    TrackCorrector3D( std::string fileName );
    void load(std::string dirName);
    double getWeight( double pT, double eta, double occ, string option );
    double getWeightNoFake( double pT, double eta, double occ );
    double getEvtFakeRatepPb( double pT, double mul, double occ );
    double getEvtFakeRatePbp( double pT, double mul, double occ );
    double getEventWeight( int M);
    double getZeroMultFrac();
    double getEventWeightEPOS( int M);
    double getZeroMultFracEPOS();
    void setOption1(bool opt){ option1 = opt; return;};
    void setOption2(bool opt){ option2 = opt; return;};
    virtual ~TrackCorrector3D();

  private:

    static const double trigEff[30];
    static const double trigFak[30];
    static const double zeroMFraction;
    static const double trigEffEPOS[30];
    static const double trigFakEPOS[30];
    static const double zeroMFractionEPOS;

    TFile * table;

    TH3F * reff3D;
    TH3F * rrec3D;
    TH3F * rsim3D;
    TH3F * rfak3D;
    TH3F * rsec3D;
    TH3F * rmul3D;

    // when option 1 is set to true, the fake, secondary, and multiple
    // reco corrections are taken from the 2D table that does not
    // bin by leading Jet Et

};

TrackCorrector3D::TrackCorrector3D( std::string fileName )
{
 table = new TFile(fileName.c_str());
}

TrackCorrector3D::TrackCorrector3D()
{
  table = new TFile("trackCorrections_HIJING_DiJet120_v0.root");
}

void
TrackCorrector3D::load(std::string dirName)
{

TH3F * corr3Deff = (TH3F*) table->Get(Form("%s/heff3D",dirName.c_str()));
TH3F * corr3Dsim = (TH3F*) table->Get(Form("%s/hsim3D",dirName.c_str()));
TH3F * corr3Drec = (TH3F*) table->Get(Form("%s/hrec3D",dirName.c_str()));
TH3F * corr3Dfak = (TH3F*) table->Get(Form("%s/hfak3D",dirName.c_str()));
TH3F * corr3Dsec = (TH3F*) table->Get(Form("%s/hsec3D",dirName.c_str()));
TH3F * corr3Dmul = (TH3F*) table->Get(Form("%s/hmul3D",dirName.c_str()));

reff3D = (TH3F*) corr3Deff->Clone("reff3D");
rrec3D = (TH3F*) corr3Drec->Clone("rrec3D");
rsim3D = (TH3F*) corr3Dsim->Clone("rsim3D");
rfak3D = (TH3F*) corr3Dfak->Clone("rfak3D");
rmul3D = (TH3F*) corr3Dsec->Clone("rmul3D");
rsec3D = (TH3F*) corr3Dmul->Clone("rsec3D");

reff3D->Divide(corr3Deff,corr3Dsim,1,1,"B");
rmul3D->Divide(corr3Dmul,corr3Dsim,1,1,"B");
rfak3D->Divide(corr3Dfak,corr3Drec,1,1,"B");
rsec3D->Divide(corr3Dsec,corr3Drec,1,1,"B");

}

TrackCorrector3D::~TrackCorrector3D()
{  
  delete table;  
}

double
TrackCorrector3D::getWeight(double pT, double eta, double occ, string option ) 
{

  double eff = reff3D->GetBinContent(
                  reff3D->GetXaxis()->FindBin(eta),
                  reff3D->GetYaxis()->FindBin(pT),
                  reff3D->GetZaxis()->FindBin(occ) );
  if( eff >= 0.9999 || eff <= 0.0001) eff = 1;

  double sec = rsec3D->GetBinContent(
              rsec3D->GetXaxis()->FindBin(eta),
              rsec3D->GetYaxis()->FindBin(pT),
              rsec3D->GetZaxis()->FindBin(occ) );
  if( sec >= 0.9999 || sec <= 0.0001) sec = 0;
  double fak = rfak3D->GetBinContent(
              rfak3D->GetXaxis()->FindBin(eta),
              rfak3D->GetYaxis()->FindBin(pT),
              rfak3D->GetZaxis()->FindBin(occ) );
  if( fak >= 0.9999 || fak <= 0.0001) fak = 0;
  double mul = rmul3D->GetBinContent(
              rmul3D->GetXaxis()->FindBin(eta),
              rmul3D->GetYaxis()->FindBin(pT),
              rmul3D->GetZaxis()->FindBin(occ) );
  if( mul >= 0.9999 || mul <= 0.0001) mul = 0;

  if( option == "eff" ) return eff;
  else if( option == "fak" ) return fak;
  else if( option == "sec" ) return sec;
  else if( option == "mul" ) return mul;
  else{
    return (1. - fak ) * ( 1. - sec ) / eff  / (1. + mul );
  }

}

double
TrackCorrector3D::getWeightNoFake(double pT, double eta, double occ )
{

  double eff = reff3D->GetBinContent(
                  reff3D->GetXaxis()->FindBin(eta),
                  reff3D->GetYaxis()->FindBin(pT),
                  reff3D->GetZaxis()->FindBin(occ) );
  if( eff >= 0.9999 || eff <= 0.0001) eff = 1;

  double sec = rsec3D->GetBinContent(
              rsec3D->GetXaxis()->FindBin(eta),
              rsec3D->GetYaxis()->FindBin(pT),
              rsec3D->GetZaxis()->FindBin(occ));
  if( sec >= 0.9999 || sec <= 0.0001) sec = 0;
  double mul = rmul3D->GetBinContent(
              rmul3D->GetXaxis()->FindBin(eta),
              rmul3D->GetYaxis()->FindBin(pT),
              rmul3D->GetZaxis()->FindBin(occ));
  if( mul >= 0.9999 || mul <= 0.0001) mul = 0;

  return ( 1. - sec ) / eff  / (1. + mul );
}

#endif /* TRACKCORRECTOR3D_C */