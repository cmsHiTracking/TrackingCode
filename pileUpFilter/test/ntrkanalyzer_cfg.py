import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.Timing = cms.Service("Timing")

process.load("pileUpCorrector.pileUpFilter.pileUpFilter_cff") 

process.ana_PbPb = cms.EDAnalyzer('NtrkAnalyzer',
                      
                		  vertexSrc = cms.string('offlinePrimaryVertices'),
                		  trackSrc = cms.InputTag('generalTracks'),             
				
				  offlineDCA = cms.untracked.double(3.0),
				  offlineptErr = cms.untracked.double(0.1)
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
'/store/data/Run2015E/MinimumBias3/AOD/PromptReco-v1/000/262/167/00000/1274C672-2494-E511-9096-02163E014661.root'
)
)

process.ana_PbPb0 = process.ana_PbPb.clone()
process.ana_PbPb1 = process.ana_PbPb.clone()
process.ana_PbPb2 = process.ana_PbPb.clone()
process.ana_PbPb3 = process.ana_PbPb.clone()
process.ana_PbPb4 = process.ana_PbPb.clone()
process.ana_PbPb5 = process.ana_PbPb.clone()

process.TFileService = cms.Service("TFileService",fileName = cms.string("Ntrk.root"))

process.p = cms.Path( process.ana_PbPb0 )
process.p1 = cms.Path( process.pileUpFilter_baseCut_loose*process.ana_PbPb1 )
process.p2 = cms.Path( process.pileUpFilter_baseCut_tight*process.ana_PbPb2 )
process.p3 = cms.Path( process.pileUpFilter_baseCut_loose_dz1p0*process.ana_PbPb3 )
process.p4 = cms.Path( process.pileUpFilter_baseCut_tight_dz1p0*process.ana_PbPb4 )
process.p5 = cms.Path( process.pileUpFilter_vtx1*process.ana_PbPb5 )
