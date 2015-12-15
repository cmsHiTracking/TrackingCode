#include "TrackingCode/HIRun2015Ana/interface/HITrackCorrectionTreeHelper.h"

HITrackCorrectionTreeHelper::HITrackCorrectionTreeHelper()
{
  hiTrackLeafString = "ids/I:status/I:charges/I:pts/F:etas/F:phis/F:hits/I";
  hiTrackLeafString += ":nmatch/I";
  hiTrackLeafString += ":charger/I:ptr/F:etar/F:phir/F:pterr/F:etaerr/F:phierr/F";
  hiTrackLeafString += ":d0/F:d0err/F:dz/F:dzerr/F:hitr/I:chi2r/F:algo/I";
  hiTrackLeafString += ":cbin/I:highPurityr/O";
}

void
HITrackCorrectionTreeHelper::Set(const TrackingParticle & p, const reco::Track & t, const reco::Vertex & v, int matches, int cbin, bool setRecHits)
{

  SetTP(p);
  SetTrack(t,v,setRecHits); 
  b.nmatch = matches;
  b.cbin = cbin;
}

void
HITrackCorrectionTreeHelper::Set(const reco::Track & t, const reco::Vertex & v, int cbin, bool setRecHits)
{
  SetTrack(t,v, setRecHits);
  b.nmatch = 0;
  b.cbin = cbin;
}

void
HITrackCorrectionTreeHelper::Set(const TrackingParticle & p, int cbin)
{
  SetTP(p);
  b.nmatch = 0;
  b.cbin = cbin;
}

void
HITrackCorrectionTreeHelper::SetTrack(const reco::Track & t, const reco::Vertex & v, bool setRecHits)
{
  b.charger = t.charge();
  b.ptr = t.pt();
  b.etar = t.eta();
  b.phir = t.phi();
  b.pterr = t.ptError();
  b.etaerr = t.etaError();
  b.phierr = t.phiError();

  math::XYZPoint vtxPoint(0.0,0.0,0.0);
  double vzErr =0.0, vxErr=0.0, vyErr=0.0;
  vtxPoint=v.position();
  vzErr=v.zError();
  vxErr=v.xError();
  vyErr=v.yError();

  double dxy=0.0, dz=0.0, dxysigma=0.0, dzsigma=0.0;
  dxy = t.dxy(vtxPoint);
  dz = t.dz(vtxPoint);
  dxysigma = sqrt(t.d0Error()*t.d0Error()+vxErr*vyErr);
  dzsigma = sqrt(t.dzError()*t.dzError()+vzErr*vzErr); 

  b.d0 = dxy;
  b.d0err = dxy/dxysigma;
  b.dz = dz;
  b.dzerr = dz/dzsigma;

  b.hitr = t.numberOfValidHits();
  b.chi2r = t.normalizedChi2();
  b.algo = t.algo();
  b.highPurityr = t.quality(reco::TrackBase::qualityByName("highPurity"));
  
  if( setRecHits )
      SetRecHits(t);
}

void
HITrackCorrectionTreeHelper::SetTP(const TrackingParticle & p)
{
  b.ids = p.pdgId();
  b.status = p.status();  
  b.charges = p.charge();
  b.pts = p.pt();
  b.etas = p.eta();
  b.phis = p.phi();
  b.hits = p.numberOfTrackerLayers();
}

void
HITrackCorrectionTreeHelper::SetRecHits(const reco::Track & t)
{ 
  ResetRecHits();
  bhit.hitr = t.numberOfValidHits();
  
  int hitCount = 0;
  for( trackingRecHit_iterator rechit = t.recHitsBegin(); rechit != t.recHitsEnd(); ++rechit ) 
  {
    if( (*rechit)->isValid() )
    {
      bhit.hitrType[hitCount] = (*rechit)->geographicalId().subdetId();
      bhit.hitrRawId[hitCount] = (*rechit)->rawId();
      bhit.hitrR[hitCount] = (*rechit)->globalPosition().perp();
      bhit.hitrPhi[hitCount] = (*rechit)->globalPosition().phi();
      bhit.hitrZ[hitCount] = (*rechit)->globalPosition().z();
      bhit.hitrLocX[hitCount] = (*rechit)->localPosition().x();
      bhit.hitrLocY[hitCount] = (*rechit)->localPosition().y();
      
      const SiPixelRecHit* pixelRecHit = dynamic_cast<const SiPixelRecHit *>( *rechit );
      if( pixelRecHit != 0 )
      {
        bhit.hitrCharge[hitCount] = pixelRecHit->cluster()->charge();
        bhit.nadc[hitCount] = pixelRecHit->cluster()->size();
        bhit.nadcX[hitCount] = pixelRecHit->cluster()->sizeX();
        bhit.nadcY[hitCount] = pixelRecHit->cluster()->sizeY();
        int adcCount = 0;
        for( const auto & adc : pixelRecHit->cluster()->pixelADC() )
        { 
          bhit.adc[hitCount][adcCount] = (int)adc;
          bhit.adcX[hitCount][adcCount] = pixelRecHit->cluster()->pixel(adcCount).x; 
          bhit.adcY[hitCount][adcCount] = pixelRecHit->cluster()->pixel(adcCount).y; 
        }
        adcCount++;
      }
      
      const SiStripRecHit1D* stripRecHit1D = dynamic_cast<const SiStripRecHit1D *>( *rechit );
      if ( stripRecHit1D != 0)
      { 
        bhit.hitrCharge[hitCount] = stripRecHit1D->cluster()->charge();
        bhit.nadc[hitCount] = stripRecHit1D->cluster()->amplitudes().size();
        bhit.nadcX[hitCount] = bhit.nadc[hitCount];
        bhit.nadcY[hitCount] = 1;
        int adcCount = 0;
        for( const auto & adc : stripRecHit1D->cluster()->amplitudes() ){
          bhit.adc[hitCount][adcCount] = (int)adc;
          if( adcCount==0 )
            bhit.adcX[hitCount][adcCount] = stripRecHit1D->cluster()->firstStrip();
          else 
            bhit.adcX[hitCount][adcCount] = bhit.adcX[hitCount][adcCount-1] + 1; 
          bhit.adcY[hitCount][adcCount] = 0;
          adcCount++;
        }
      }
      
      const SiStripRecHit2D* stripRecHit2D = dynamic_cast<const SiStripRecHit2D *>( *rechit );
      if ( stripRecHit2D != 0)
      { 
        bhit.hitrCharge[hitCount] = stripRecHit2D->cluster()->charge();
        bhit.nadc[hitCount] = stripRecHit2D->cluster()->amplitudes().size();
        bhit.nadcX[hitCount] = bhit.nadc[hitCount];
        bhit.nadcY[hitCount] = 1;
        int adcCount = 0;
        for( const auto & adc : stripRecHit2D->cluster()->amplitudes() ){
          bhit.adc[hitCount][adcCount] = (int)adc;
          if( adcCount==0 )
            bhit.adcX[hitCount][adcCount] = stripRecHit2D->cluster()->firstStrip();
          else 
            bhit.adcX[hitCount][adcCount] = bhit.adcX[hitCount][adcCount-1] + 1; 
          bhit.adcY[hitCount][adcCount] = 0;
          adcCount++;
        }
      }
      hitCount++;
    }
  } 
}


void
HITrackCorrectionTreeHelper::ResetRecHits()
{ 
  for( int hitCount = 0; hitCount < maxhits; hitCount++ )
  {
    bhit.hitrType[hitCount] = -999;
    bhit.hitrRawId[hitCount] = -999;
    bhit.hitrR[hitCount] = -999;
    bhit.hitrPhi[hitCount] = -999;
    bhit.hitrZ[hitCount] = -999;
    bhit.hitrLocX[hitCount] = -999;
    bhit.hitrLocY[hitCount] = -999;
    bhit.hitrCharge[hitCount] = -999;
    bhit.nadc[hitCount] = -999;
    bhit.nadcX[hitCount] = -999;
    bhit.nadcY[hitCount] = -999;
    for( int adcCount = 0; adcCount < maxadc; adcCount++ )
   	{
      bhit.adc[hitCount][adcCount] = -999;
      bhit.adcX[hitCount][adcCount] = -999;
      bhit.adcY[hitCount][adcCount] = -999;
     } 
  }  
}

void
HITrackCorrectionTreeHelper::SetRecHitTree(TTree * tree)
{
  tree->Branch("hitr", &bhit.hitr, "hitr/I");
  tree->Branch("hitrType", bhit.hitrType, "hitrType[hitr]/I");
  tree->Branch("hitrRawId", bhit.hitrRawId, "hitrRawId[hitr]/I");
  tree->Branch("hitrR", bhit.hitrR, "hitrR[hitr]/F");
  tree->Branch("hitrPhi", bhit.hitrPhi, "hitrPhi[hitr]/F");
  tree->Branch("hitrZ", bhit.hitrZ, "hitrZ[hitr]/F");
  tree->Branch("hitrLocX", bhit.hitrLocX, "hitrLocX[hitr]/F");
  tree->Branch("hitrLocY", bhit.hitrLocY, "hitrLocY[hitr]/F");
  tree->Branch("nadc", bhit.nadc, "nadc[hitr]/I");
  tree->Branch("nadcX", bhit.nadcX, "nadcX[hitr]/I");
  tree->Branch("nadcY", bhit.nadcY, "nadcY[hitr]/I");
  tree->Branch("adc", bhit.adc, Form("adc[%d][%d]/I",maxhits,maxadc));
  tree->Branch("adcX", bhit.adcX, Form("adcX[%d][%d]/I",maxhits,maxadc));
  tree->Branch("adcY", bhit.adcY, Form("adcY[%d][%d]/I",maxhits,maxadc));
}
