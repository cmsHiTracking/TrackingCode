//cription: [one line class summary]

// Implementation:
  //   [Notes on implementation]

//
// Original Author:  Zhoudunming Tu,
//         Created:  Mon Jun 13 20:56:30 CEST 2011
// $Id$
//
//


// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <map>
#include <sstream>


#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TCanvas.h>
#include <TVector3.h>
#include <TRandom.h>
#include <TNtuple.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"



#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"

#include "DataFormats/Candidate/interface/Candidate.h"

#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/TrackReco/interface/DeDxData.h"

#include <Math/Functions.h>
#include <Math/SVector.h>
#include <Math/SMatrix.h>

//////////////////////////////////////////////
// CMSSW user include files
#include "DataFormats/Common/interface/DetSetAlgorithm.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHitCollection.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"

#include "DataFormats/SiPixelDetId/interface/PixelEndcapName.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"


#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"

#include "DataFormats/TrackReco/interface/DeDxData.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// Heavyion
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"

// Particle Flow
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"

// Vertex significance
#include "RecoBTag/SecondaryVertex/interface/SecondaryVertex.h"

// Root include files
#include "TTree.h"
//
// Track Matching and fake rate calculations     
//#include "RiceHIG/V0Analysis/interface/V0Validator.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

//
// class decleration
//

class NtrkAnalyzer : public edm::EDAnalyzer {
public:
  explicit NtrkAnalyzer(const edm::ParameterSet&);
  ~NtrkAnalyzer();


private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;



  // ----------member data ---------------------------

  edm::EDGetTokenT<edm::View<reco::Track> > trackSrc_;//track collection: hiGeneralAndRegitTracks
  edm::EDGetTokenT<reco::VertexCollection> vertexSrc_;// vertex collection: hiSelectedVertex
  edm::EDGetTokenT<CaloTowerCollection> towerSrc_;

  double offlineptErr_;
  double offlineDCA_;

  int Nmin_;
  int Nmax_;

  TH1D* Ntrk;
  TH1D* leadingPt;
  TH1D* vertexZ;
  TH1D* HFsum;
  TH1D* HFsumEt;


  };

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

NtrkAnalyzer::NtrkAnalyzer(const edm::ParameterSet& iConfig)
 
{
  trackSrc_ = consumes<edm::View<reco::Track> >(iConfig.getParameter<edm::InputTag>("trackSrc"));
  vertexSrc_ = consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertexSrc"));
  towerSrc_ = consumes<CaloTowerCollection>(iConfig.getParameter<edm::InputTag>("towerSrc"));
  
  Nmin_ = iConfig.getUntrackedParameter<int>("Nmin");
  Nmax_ = iConfig.getUntrackedParameter<int>("Nmax");

  offlineptErr_ = iConfig.getUntrackedParameter<double>("offlineptErr", 0.0);
  offlineDCA_ = iConfig.getUntrackedParameter<double>("offlineDCA", 0.0);

}


NtrkAnalyzer::~NtrkAnalyzer()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}

//==================
// member functions
//==================

// ------------ method called to for each event  ------------
void
NtrkAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
	
  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(vertexSrc_,vertices);
  double bestvz=-999.9, bestvx=-999.9, bestvy=-999.9;
  double bestvzError=-999.9, bestvxError=-999.9, bestvyError=-999.9;
  const reco::Vertex & vtx = (*vertices)[0];
  bestvz = vtx.z(); 
  bestvx = vtx.x(); 
  bestvy = vtx.y();
  bestvzError = vtx.zError(); 
  bestvxError = vtx.xError(); 
  bestvyError = vtx.yError();
  
  //first selection; vertices
  if(bestvz < -15.0 || bestvz > 15.0) return;
  if( vtx.tracksSize() < 1 ) return;

  edm::Handle<edm::View<reco::Track>> tracks;
  iEvent.getByToken(trackSrc_, tracks);

  int count = 0;
  double max_pt = 0.0;

  for(unsigned it = 0; it < tracks->size(); it++){

     const reco::Track & trk = (*tracks)[it];
	
     math::XYZPoint bestvtx(bestvx,bestvy,bestvz);

        double dzvtx = trk.dz(bestvtx);
        double dxyvtx = trk.dxy(bestvtx);
        double dzerror = sqrt(trk.dzError()*trk.dzError()+bestvzError*bestvzError);
        double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+bestvxError*bestvyError); 

        if(!trk.quality(reco::TrackBase::highPurity)) continue;
        if(fabs(trk.ptError())/trk.pt() > offlineptErr_ ) continue;
        if(fabs(dzvtx/dzerror) > offlineDCA_) continue;
        if(fabs(dxyvtx/dxyerror) > offlineDCA_) continue;

        if ( fabs(trk.eta()) > 2.4 || trk.pt() < 0.4  ) continue;

        if( trk.pt() > max_pt ) max_pt = trk.pt();
        vertexZ->Fill( dzvtx );
        count++;
      
  } 

  if( count < Nmin_ || count >= Nmax_ ) return;

  Ntrk->Fill( count );
  leadingPt->Fill( max_pt );

  edm::Handle<CaloTowerCollection> towers;
  iEvent.getByToken(towerSrc_, towers);

  double energy = 0.;
  double sumEt = 0.;
  for(unsigned i = 0; i < towers->size(); ++i){

        const CaloTower & hit= (*towers)[i];
        if( fabs(hit.eta()) > 5.0 || fabs(hit.eta()) < 3.0  ) continue;
        energy += (hit.hadEnergy() + hit.emEnergy());
        sumEt += (hit.hadEt()+hit.emEt());
  }
  
  HFsum->Fill( energy );
  HFsumEt->Fill( sumEt );

}
// ------------ method called once each job just before starting event loop  ------------
void 
NtrkAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
    
  TH3D::SetDefaultSumw2();

  Ntrk = fs->make<TH1D>("Ntrk",";Ntrk",500,0,500);
  leadingPt = fs->make<TH1D>("leadingPt",";p_{T} (GeV)",1000,0,200);
  vertexZ = fs->make<TH1D>("vertexZ",";vertexZ",1000,-1,1);
  HFsum = fs->make<TH1D>("HFsum", ";HFsum", 1000, 0, 10000);
  HFsumEt = fs->make<TH1D>("HFsumEt", ";HFsumEt", 1000, 0, 10000);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
NtrkAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(NtrkAnalyzer);
