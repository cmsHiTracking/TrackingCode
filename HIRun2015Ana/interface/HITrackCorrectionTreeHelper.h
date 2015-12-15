#ifndef HIRun2015Ana_HITrackCorrectionTreeHelper
#define HIRun2015Ana_HITrackCorrectionTreeHelper

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit2D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit1D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHit.h"
#include <DataFormats/VertexReco/interface/Vertex.h>
#include <DataFormats/VertexReco/interface/VertexFwd.h>

#include <TString.h>
#include <TTree.h>

#define maxhits 30
#define maxadc 30

// Branches for track correction analysis ntuples

// Simulated Particle (one) -> Reco Track (many)
// or
// Reco Track (one) -> Simulated Particle (many)
//
// only best match is stored

typedef struct
{
  // sim particle PDG id, and status (i.e. -99 is secondary)
  Int_t ids;
  Int_t status;

  // simulated particle kinematics
  Int_t charges;
  Float_t pts;
  Float_t etas;
  Float_t phis;

  // G4SimHits of simulated particle
  Int_t hits;

  // number of matched tracks or particles
  Int_t nmatch;

  // kinematics of the reco track
  Int_t charger;
  Float_t ptr;
  Float_t etar;
  Float_t phir;

  Float_t pterr;
  Float_t etaerr;
  Float_t phierr;

  // vertex compatibility of reco track
  Float_t d0;
  Float_t d0err;
  Float_t dz;
  Float_t dzerr;

  // reconstructed hits of reco track and goodness of fit
  Int_t hitr;
  Float_t chi2r;

  // Iteration of reco track
  Int_t algo;

  // Event centrality bin
  Int_t cbin;

  // reco track highpurity bit
  // note that this must be last due to padding incompatibilties
  Bool_t highPurityr;

} HITrackBranches_t;

typedef struct
{
  Int_t hitr;
  Int_t hitrType[maxhits];
  Int_t hitrRawId[maxhits];
  Float_t hitrR[maxhits];
  Float_t hitrPhi[maxhits];
  Float_t hitrZ[maxhits];
  Float_t hitrLocX[maxhits];
  Float_t hitrLocY[maxhits];
  Int_t hitrCharge[maxhits];
  Int_t nadc[maxhits];
  Int_t nadcX[maxhits];
  Int_t nadcY[maxhits];
  Int_t adc[maxhits][maxadc];
  Int_t adcX[maxhits][maxadc];
  Int_t adcY[maxhits][maxadc];
  
} HIHitBranches_t;

// Helper class for producing track correction ntuples

class HITrackCorrectionTreeHelper 
{
  public:

    HITrackCorrectionTreeHelper();

    void Set(const TrackingParticle &, const reco::Track &, const reco::Vertex &, int, int, bool setRecHits = false );

    // need polymorphic Set functions for unmatched case where there is no Track or TP
    void Set(const reco::Track &, const reco::Vertex &, int, bool setRecHits = false);
    void Set(const TrackingParticle &, int);

    HITrackBranches_t b;
    HIHitBranches_t bhit;
    TString hiTrackLeafString;
    void SetRecHitTree(TTree *);  

  private:
    // these are just to factorize setting the Track or TP information
    void SetTrack(const reco::Track &, const reco::Vertex &, bool setRecHits = false);
    void SetTP(const TrackingParticle &);  
    void SetRecHits(const reco::Track &);  
    void ResetRecHits();

};

#endif 
