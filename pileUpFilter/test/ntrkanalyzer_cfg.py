import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.Timing = cms.Service("Timing")

process.load("TrackingCode.pileUpFilter.pileUpFilter_cff") 

process.ana_PbPb = cms.EDAnalyzer('NtrkAnalyzer',
                      
                		  vertexSrc = cms.InputTag('offlinePrimaryVertices'),
                		  trackSrc = cms.InputTag('generalTracks'),             
				
				  offlineDCA = cms.untracked.double(3.0),
				  offlineptErr = cms.untracked.double(0.1)
)

process.pPbPileup = cms.EDAnalyzer('ppPileupFilter',
    trackSrc = cms.InputTag("generalTracks"),
    vertexSrc = cms.InputTag("offlinePrimaryVertices"),
    vertexZMax = cms.double(15.0),
    ptBins = cms.vdouble(
        0,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.4,1.6,1.8,2.0,2.2,2.4,3.2,4.0,4.8,5.6,6.4,7.2,9.6,
        12.0,14.4,19.2,24.0,28.8,35.2,41.6,48.0,60.8,73.6,86.4,103.6,120.8
    ),
    qualityString = cms.string("highPurity"),
    dxySigMax = cms.double(3.0),
    dzSigMax = cms.double(3.0),
    ptErrOverptMax = cms.double(0.1)
)


### standard includes
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')

process.options   = cms.untracked.PSet( wantSummary =
cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#'/store/data/Run2015E/MinimumBias3/AOD/PromptReco-v1/000/262/167/00000/1274C672-2494-E511-9096-02163E014661.root'
#'/store/user/gsfs/ReggeGribovPartonMC_EposLHC_pPb_4080_4080/EPOS_pileup1_pPb_RECODEBUG_11102016/161110_214657/0000/step3_EPOS_pileup1_pPb_RAW2DIGI_L1Reco_RECO_1.root'
'/store/express/PARun2016C/ExpressPhysicsPA/FEVT/Express-v1/000/285/480/00000/00D0A34F-5BAD-E611-9B86-02163E0134CD.root'
)
)

process.ana_PbPb0 = process.ana_PbPb.clone()
process.ana_PbPb1 = process.ana_PbPb.clone()
process.ana_PbPb2 = process.ana_PbPb.clone()
process.ana_PbPb3 = process.ana_PbPb.clone()

process.TFileService = cms.Service("TFileService",fileName = cms.string("Ntrk.root"))

process.p = cms.Path( process.ana_PbPb0*process.pPbPileup )
process.p1 = cms.Path( process.pileUpFilter_pPb8TeV_vtx1*process.ana_PbPb1 )
process.p2 = cms.Path( process.pileUpFilter_pPb8TeV_Gplus*process.ana_PbPb2 )
process.p3 = cms.Path( process.olvFilter_pPb8TeV_dz1p0*process.ana_PbPb3 )
