//
// Original Author:  Eric Appelt
//         Created:  Mar 6, 2015
//
//

// Do not compile - this class is broken due to change in 
// TrackerHitAssociator interface as of 750_pre5. Need to fix.
//
#ifdef THIS_CLASS_IS_CURRENTLY_BROKEN

#include <memory>
#include <algorithm>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDGetToken.h"

#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TTree.h>
#include <TLorentzVector.h>

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <DataFormats/VertexReco/interface/Vertex.h>
#include <DataFormats/VertexReco/interface/VertexFwd.h>
#include <DataFormats/TrackReco/interface/Track.h>
#include <DataFormats/TrackReco/interface/TrackFwd.h>
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "DataFormats/RecoCandidate/interface/TrackAssociation.h"
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"

#include "DataFormats/TrackingRecHit/interface/RecHit2DLocalPos.h"
#include "DataFormats/TrackingRecHit/interface/RecSegment.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit2D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit1D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHit.h"
#include "DataFormats/SiStripDetId/interface/StripSubdetector.h"
#include "DataFormats/SiStripDetId/interface/SiStripDetId.h"
#include "DataFormats/SiStripDetId/interface/TIDDetId.h"
#include "DataFormats/SiStripDetId/interface/TECDetId.h"
#include "DataFormats/SiStripDetId/interface/TIBDetId.h"
#include "DataFormats/SiStripDetId/interface/TOBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
//#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"


#include "TrackingCode/HIRun2015Ana/interface/HITrackCorrectionTreeHelper.h"

class HITrackProfiler : public edm::EDAnalyzer {
   public:
      explicit HITrackProfiler(const edm::ParameterSet&);
      ~HITrackProfiler();

      static bool vtxSort( const reco::Vertex &  a, const reco::Vertex & b );

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      void initHistos(const edm::Service<TFileService> & fs);
      bool passesTrackCuts(const reco::Track & track, const reco::Vertex & vertex);

      // ----------member data ---------------------------


      std::map<std::string,TTree*> trkTree_;
      std::map<std::string,TH2F*> trkCorr2D_; 
      TTree * recHitTree_;
      TH3F * momRes_;
      TH1F * vtxZ_;
      TF1 * vtxWeightFunc_;

      HITrackCorrectionTreeHelper treeHelper_;
      edm::ParameterSet theConfig_;

      edm::EDGetTokenT<reco::VertexCollection> vertexSrc_;
      edm::EDGetTokenT<edm::View<reco::Track> > trackSrc_;
      edm::EDGetTokenT<TrackingParticleCollection> tpFakSrc_;
      edm::EDGetTokenT<TrackingParticleCollection> tpEffSrc_;
      edm::EDGetTokenT<reco::RecoToSimCollection> associatorMapRTS_;
      edm::EDGetTokenT<reco::SimToRecoCollection> associatorMapSTR_;

      std::vector<double> ptBins_;
      std::vector<double> etaBins_;

      std::vector<double> vtxWeightParameters_;
      bool doVtxReweighting_;

      bool applyVertexZCut_;
      double vertexZMax_;

      bool applyTrackCuts_;
      std::string qualityString_;
      double dxyErrMax_;
      double dzErrMax_;
      double ptErrMax_;

      bool doMomRes_;

      bool fillNTuples_;

      bool useCentrality_;
      edm::EDGetTokenT<int> centralitySrc_;

};

HITrackProfiler::HITrackProfiler(const edm::ParameterSet& iConfig):
treeHelper_(),
theConfig_(iConfig),
vertexSrc_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertexSrc"))),
trackSrc_(consumes<edm::View<reco::Track> >(iConfig.getParameter<edm::InputTag>("trackSrc"))),
tpFakSrc_(consumes<TrackingParticleCollection>(iConfig.getParameter<edm::InputTag>("tpFakSrc"))),
tpEffSrc_(consumes<TrackingParticleCollection>(iConfig.getParameter<edm::InputTag>("tpEffSrc"))),
associatorMapRTS_(consumes<reco::RecoToSimCollection>(iConfig.getParameter<edm::InputTag>("associatorMap"))),
associatorMapSTR_(consumes<reco::SimToRecoCollection>(iConfig.getParameter<edm::InputTag>("associatorMap"))),
ptBins_(iConfig.getParameter<std::vector<double> >("ptBins")),
etaBins_(iConfig.getParameter<std::vector<double> >("etaBins")),
vtxWeightParameters_(iConfig.getParameter<std::vector<double> >("vtxWeightParameters")),
doVtxReweighting_(iConfig.getParameter<bool>("doVtxReweighting")),
applyVertexZCut_(iConfig.getParameter<bool>("applyVertexZCut")),
vertexZMax_(iConfig.getParameter<double>("vertexZMax")),
applyTrackCuts_(iConfig.getParameter<bool>("applyTrackCuts")),
qualityString_(iConfig.getParameter<std::string>("qualityString")),
dxyErrMax_(iConfig.getParameter<double>("dzErrMax")),
dzErrMax_(iConfig.getParameter<double>("dzErrMax")),
ptErrMax_(iConfig.getParameter<double>("ptErrMax")),
doMomRes_(iConfig.getParameter<bool>("doMomRes")),
fillNTuples_(iConfig.getParameter<bool>("fillNTuples")),
useCentrality_(iConfig.getParameter<bool>("useCentrality")),
centralitySrc_(consumes<int>(iConfig.getParameter<edm::InputTag>("centralitySrc")))
{
   edm::Service<TFileService> fs;
   initHistos(fs);

   vtxWeightFunc_ = new TF1("vtxWeight","gaus(0)/gaus(3)",-50.,50.);
   // vtxWeightParameters should have size 6,
   // one really should throw an error if not
   if( (int)vtxWeightParameters_.size() == 6 )
   {
     for( unsigned int i=0;i<vtxWeightParameters_.size(); i++)
       vtxWeightFunc_->SetParameter(i,vtxWeightParameters_[i]);
   }

   if( fillNTuples_ )
   {
     trkTree_["rec"] = fs->make<TTree>("recTree","recTree");
     trkTree_["rec"]->Branch("recValues",&treeHelper_.b,treeHelper_.hiTrackLeafString.Data());
     trkTree_["sim"] = fs->make<TTree>("simTree","simTree");
     trkTree_["sim"]->Branch("simValues",&treeHelper_.b,treeHelper_.hiTrackLeafString.Data());
	   recHitTree_ = fs->make<TTree>("recHitTree","recHitTree");
	   treeHelper_.SetRecHitTree(recHitTree_);
   }
}

HITrackProfiler::~HITrackProfiler()
{
   delete vtxWeightFunc_;
}

void
HITrackProfiler::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // obtain collections of simulated particles 
   edm::Handle<TrackingParticleCollection>  TPCollectionHeff, TPCollectionHfake;
   iEvent.getByToken(tpEffSrc_,TPCollectionHeff);
   iEvent.getByToken(tpFakSrc_,TPCollectionHfake);

   // obtain association map between tracks and simulated particles
   reco::RecoToSimCollection recSimColl;
   reco::SimToRecoCollection simRecColl;
   edm::Handle<reco::SimToRecoCollection > simtorecoCollectionH;
   edm::Handle<reco::RecoToSimCollection > recotosimCollectionH;
   iEvent.getByToken(associatorMapSTR_,simtorecoCollectionH);
   simRecColl= *(simtorecoCollectionH.product());
   iEvent.getByToken(associatorMapRTS_,recotosimCollectionH);
   recSimColl= *(recotosimCollectionH.product());

   // obtain reconstructed tracks
   Handle<edm::View<reco::Track> > tcol;
   iEvent.getByToken(trackSrc_, tcol);

   // obtain primary vertices
   Handle<reco::VertexCollection> vertex;
   iEvent.getByToken(vertexSrc_, vertex);
  
   // sort the vertcies by number of tracks in descending order
   reco::VertexCollection vsorted = *vertex;
   std::sort( vsorted.begin(), vsorted.end(), HITrackProfiler::vtxSort );

   TrackerHitAssociator  *theHitAssociator = new TrackerHitAssociator(iEvent, theConfig_);

   // skip events with no PV, this should not happen
   if( vsorted.size() == 0) return;

   // skip events failing vertex cut
   if( applyVertexZCut_)
   {
     if( fabs(vsorted[0].z()) > vertexZMax_ ) return;
   }

   // determine vertex reweighting factor
   double w = 1.0;
   if ( doVtxReweighting_ )
     w *= vtxWeightFunc_->Eval(vsorted[0].z());

   vtxZ_->Fill(vsorted[0].z(),w);

   // determine event multipliticy
   int multiplicity =0;
   for(edm::View<reco::Track>::size_type i=0; i<tcol->size(); ++i){
     edm::RefToBase<reco::Track> track(tcol, i);
     reco::Track* tr=const_cast<reco::Track*>(track.get());
     if( passesTrackCuts(*tr, vsorted[0]) ) 
       multiplicity++;
   }

   // determine centrality if set
   // note if there is no centrality information multiplicity 
   // will be used in place of the centrality
   int cbin = multiplicity;
   if( useCentrality_ )
   {
     edm::Handle<int> centralityBin;
     iEvent.getByToken(centralitySrc_, centralityBin);
     cbin = *centralityBin;
   } 
 
   std::cout << "************\n\n\nThis event has cbin = " << cbin 
             << "\n\n\n************\n";

   // ---------------------
   // loop through reco tracks to fill fake, reco, and secondary histograms
   // ---------------------

   for(edm::View<reco::Track>::size_type i=0; i<tcol->size(); ++i){ 
     edm::RefToBase<reco::Track> track(tcol, i);
     reco::Track* tr=const_cast<reco::Track*>(track.get());
     // skip tracks that fail cuts, using vertex with most tracks as PV       
     if( ! passesTrackCuts(*tr, vsorted[0]) ) continue;
     if( tr->pt() < 5.0 ) continue;
     trkCorr2D_["hrec"]->Fill(tr->eta(), tr->pt(), w);

     // look for match to simulated particle, use first match if it exists
     std::vector<std::pair<TrackingParticleRef, double> > tp;
     const TrackingParticle *mtp=0;

     std::cout << "track ( "
               << tr->pt() << " , " << tr->eta() << " , "
              << tr->phi() << " ) " <<  std   ::endl;
     if(tr->quality(reco::TrackBase::qualityByName("highPurity")) == 1) 
       std::cout << "This track is high purity." << std::endl;
     if(tr->isLooper() == true ) std::cout << "This track is a LOOPER" << std::endl;  
       std::cout << "number of hits = " << tr->numberOfValidHits() << std::endl;

     int rhcount = 0;
     for( auto rechit = tr->recHitsBegin(); rechit != tr->recHitsEnd(); ++rechit ) 
     {
       if( (*rechit)->isValid() ) 
       {
         rhcount++;
         std::cout << "    Rechit # " << rhcount 
                   << " rawId = " << (*rechit)->rawId(); 
 
         int type =(*rechit)->geographicalId().subdetId();
         if(type==int(StripSubdetector::TIB)) std::cout << " TIB "; 
         if(type==int(StripSubdetector::TOB)) std::cout << " TOB "; 
         if(type==int(StripSubdetector::TID)) std::cout << " TID "; 
         if(type==int(StripSubdetector::TEC)) std::cout << " TEC "; 
         if(type==int(PixelSubdetector::PixelBarrel))
         {
           PXBDetId idid = PXBDetId( (*rechit)->rawId() );
           std::cout << " BPIX" << idid.layer() << " ";
         }
         if(type==int(PixelSubdetector::PixelEndcap)) 
         {
           PXFDetId idid = PXFDetId( (*rechit)->rawId() );
           std::cout << " FPIX" << idid.disk() << " ";
         }

         const TrackingRecHit & hit = (**rechit);
         if( hit.surface() != nullptr && hit.isValid() )
         {
           std::cout << " , Global: R = " << hit.globalPosition().perp()
                     << " z = " << hit.globalPosition().z() 
                     << " phi = " << hit.globalPosition().phi(); 
           std::cout << " , Local: x = " << hit.localPosition().x()
                     << " , y = " << hit.localPosition().y();


           const SiPixelRecHit* pixelRecHit = dynamic_cast<const SiPixelRecHit *>( *rechit );
           if( pixelRecHit != 0 )
           {
             std::cout << std::endl << "      Pixel Cluster"
                       << " nPix = " << pixelRecHit->cluster()->size()
                       << " sizeX = " << pixelRecHit->cluster()->sizeX()  
                       << " sizeY = " << pixelRecHit->cluster()->sizeY()
                       << " charge = " << pixelRecHit->cluster()->charge();
           }
           const SiStripRecHit1D* stripRecHit1D = dynamic_cast<const SiStripRecHit1D *>( *rechit );
           if ( stripRecHit1D != 0)
           {
             std::cout << std::endl << "      Strip Cluster 1D"
                       << " charge = " << stripRecHit1D->cluster()->charge()
                       << " firstStrip = " << stripRecHit1D->cluster()->firstStrip();
             std::cout << std::endl << "      ADC: ";
             for( const auto & adc : stripRecHit1D->cluster()->amplitudes() )
               std::cout << (int)adc << " ";
           } 
           const SiStripRecHit2D* stripRecHit2D = dynamic_cast<const SiStripRecHit2D *>( *rechit );
           if ( stripRecHit2D != 0)
           {
             std::cout << std::endl << "      Strip Cluster 2D"
                       << " charge = " << stripRecHit2D->cluster()->charge()
                       << " firstStrip = " << stripRecHit2D->cluster()->firstStrip();
             std::cout << std::endl << "      ADC: ";
             for( const auto & adc : stripRecHit2D->cluster()->amplitudes() )
               std::cout << (int)adc << " ";
			   
             std::vector<PSimHit> simHits = theHitAssociator->associateHit(**rechit);
		     std::cout << "size of simhits = " << simHits.size() << std::endl;
             for (unsigned int hitIter = 0 ; hitIter < simHits.size(); ++hitIter){
               std::cout << "sim hit detunitId = " << simHits[hitIter].detUnitId();
               std::cout << " trackId = " << simHits[hitIter].trackId();
               std::cout << " eventId = " << (int) simHits[hitIter].eventId().event() << std::endl;
			   std::cout << std::endl;
             }
         
             std::cout  << std::endl;
           } 
      
         }

         std::cout  << std::endl;

       }
     }

     if(recSimColl.find(track) != recSimColl.end())
     {
       tp = recSimColl[track];
       mtp = tp.begin()->first.get();  
     
       if( fillNTuples_) treeHelper_.Set(*mtp, *tr, vsorted[0], tp.size(), cbin, true); 
       for( const auto & vtpp : recSimColl[track] )
       { 
         auto vtp = vtpp.first.get();
         std::cout << "  associated to TP ( "
                   << vtp->pt() << " , " << vtp->eta() << " , "
                  << vtp->phi() << " ) "  
                  << " nLayers = " << vtp->numberOfTrackerLayers() <<  std::endl;
         std::cout << "  pdgId = " << vtp->pdgId() 
                   << " , status = " << vtp->status() 
                   << " , vertex rho = " << sqrt( vtp->vx()*vtp->vx() + vtp->vy()*vtp->vy() )
                   << std::endl;         
         std::cout << "  with quality " << vtpp.second << std::endl;
       }
       if( mtp->status() < 0 ) 
       {
         trkCorr2D_["hsec"]->Fill(tr->eta(), tr->pt(), w);     
       }
     }
     else
     {
       if( fillNTuples_) treeHelper_.Set(*tr, vsorted[0], cbin, true); 
       trkCorr2D_["hfak"]->Fill(tr->eta(), tr->pt(), w);
     }
     if( fillNTuples_)
     {
       trkTree_["rec"]->Fill(); 
       recHitTree_->Fill(); 
     }
     std::cout << std::endl;
   }

   // ---------------------
   // loop through sim particles to fill matched, multiple,  and sim histograms 
   // ---------------------
   
   std::cout << "Number of tracking particles = " << TPCollectionHeff->size() << std::endl;
   for(TrackingParticleCollection::size_type i=0; i<TPCollectionHeff->size(); i++) 
   {      
     TrackingParticleRef tpr(TPCollectionHeff, i);
     TrackingParticle* tp=const_cast<TrackingParticle*>(tpr.get());
     std::cout << "Tracking particle (pt, eta, phi) = "<< tp->pt() << " , " << tp->eta() << " , " << tp->phi() << std::endl;  
     if(tp->pt() < 5.0 || fabs(tp->eta()) > 2.4 || tp->charge()==0) continue; //only charged primaries
     
     //std::cout << *tp ;
     std::cout << "TP (pt, eta, phi) : ( " 
               << tp->pt() << " , " << tp->eta() << " , "
               << tp->phi() << " ) " << std::endl;

     std::cout << "  nLayers = " << tp->numberOfTrackerLayers() 
               << " , pdgId = " << tp->pdgId() << std::endl;
     
     trkCorr2D_["hsim"]->Fill(tp->eta(),tp->pt(), w);

     // find number of matched reco tracks that pass cuts
     std::vector<std::pair<edm::RefToBase<reco::Track>, double> > rt;
     size_t nrec=0;
     if(simRecColl.find(tpr) != simRecColl.end())
     {
       rt = (std::vector<std::pair<edm::RefToBase<reco::Track>, double> >) simRecColl[tpr];
       std::vector<std::pair<edm::RefToBase<reco::Track>, double> >::const_iterator rtit;
       for (rtit = rt.begin(); rtit != rt.end(); ++rtit)
       {
         const reco::Track* tmtr = rtit->first.get();
         std::cout << "  associated to track ( " 
                   << tmtr->pt() << " , " << tmtr->eta() << " , "
                   << tmtr->phi() << " ) " <<  std::endl;
         std::cout << " with quality " << rtit->second << std::endl;
         if( ! passesTrackCuts(*tmtr, vsorted[0]) ) continue;
         nrec++;
         if( doMomRes_ ) momRes_->Fill( tp->eta(), tp->pt(), tmtr->pt(), w);
       }
     }
     if( nrec>0 && fillNTuples_ ) treeHelper_.Set(*tp, *(rt.begin()->first.get()), vsorted[0], rt.size(), cbin, true);
     if( nrec==0 && fillNTuples_ ) treeHelper_.Set(*tp, cbin);
     if(nrec>0) trkCorr2D_["heff"]->Fill(tp->eta(),tp->pt(), w);
     if(nrec>1) trkCorr2D_["hmul"]->Fill(tp->eta(),tp->pt(), w);
     if( fillNTuples_) trkTree_["sim"]->Fill(); 
     std::cout << std::endl;
     
     for( auto simtrack = tp->g4Track_begin(); simtrack != tp->g4Track_end(); ++simtrack )
     {
	   TLorentzVector * vsimtrack = new TLorentzVector(simtrack->momentum().x(), simtrack->momentum().y(), simtrack->momentum().z(), simtrack->momentum().t());
       std::cout << "sim track momentum (4-vector) = " << simtrack->momentum() << " , "
                 << "trackID = " << simtrack->trackId() << " , "
	             <<  "( pt, eta, phi ) = " << vsimtrack->Pt() << " , "
	             << vsimtrack->Eta() << " , "
	             << vsimtrack->Phi() << std::endl;
     }

   }
   delete theHitAssociator;
}

bool
HITrackProfiler::passesTrackCuts(const reco::Track & track, const reco::Vertex & vertex)
{
   if ( ! applyTrackCuts_ ) return true;

   math::XYZPoint vtxPoint(0.0,0.0,0.0);
   double vzErr =0.0, vxErr=0.0, vyErr=0.0;
   vtxPoint=vertex.position();
   vzErr=vertex.zError();
   vxErr=vertex.xError();
   vyErr=vertex.yError();

   double dxy=0.0, dz=0.0, dxysigma=0.0, dzsigma=0.0;
   dxy = track.dxy(vtxPoint);
   dz = track.dz(vtxPoint);
   dxysigma = sqrt(track.d0Error()*track.d0Error()+vxErr*vyErr);
   dzsigma = sqrt(track.dzError()*track.dzError()+vzErr*vzErr);
 
   if(track.quality(reco::TrackBase::qualityByName(qualityString_)) != 1)
       return false;
   if(fabs(dxy/dxysigma) > dxyErrMax_) return false;
   if(fabs(dz/dzsigma) > dzErrMax_) return false;
   if(track.ptError() / track.pt() > ptErrMax_) return false;

   return true;
}


void
HITrackProfiler::initHistos(const edm::Service<TFileService> & fs)
{


  std::vector<std::string> hNames2D = { "hsim", "hrec", "hmul", "hfak",
                                        "heff", "hsec" };

  for( auto name : hNames2D )
  {
     trkCorr2D_[name] = fs->make<TH2F>(name.c_str(),";#eta;p_{T}",
                           etaBins_.size()-1, &etaBins_[0],
                           ptBins_.size()-1, &ptBins_[0]);
  }


  vtxZ_ = fs->make<TH1F>("vtxZ","Vertex z position",100,-30,30);

  std::vector<double> ptBinsFine;
  for( unsigned int bin = 0; bin<ptBins_.size()-1; bin++)
  {
    double bStart = ptBins_[bin];
    double bWid = ptBins_[bin+1] - ptBins_[bin];
    for( int i=0;i<5;i++)
      ptBinsFine.push_back( bStart + (double)i * bWid / 5. );
  }
  ptBinsFine.push_back(ptBins_[ptBins_.size()-1]);

  momRes_ = fs->make<TH3F>("momRes","momentum resolution sim vs reco",
                           etaBins_.size()-1, &etaBins_[0],
                           ptBinsFine.size()-1, &ptBinsFine[0],
                           ptBinsFine.size()-1, &ptBinsFine[0]);
}

bool
HITrackProfiler::vtxSort( const reco::Vertex &  a, const reco::Vertex & b )
{
  if( a.tracksSize() != b.tracksSize() )
    return  a.tracksSize() > b.tracksSize() ? true : false ;
  else
    return  a.chi2() < b.chi2() ? true : false ;  
}

void
HITrackProfiler::beginJob()
{
}

void
HITrackProfiler::endJob()
{
}

DEFINE_FWK_MODULE(HITrackProfiler);

#endif
