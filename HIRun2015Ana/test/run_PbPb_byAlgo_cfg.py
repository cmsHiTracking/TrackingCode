import FWCore.ParameterSet.Config as cms

process = cms.Process('TRACKANA')
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('TrackingCode.HIRun2015Ana.HITrackCorrectionAnalyzerByAlgo_cfi')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(300)
)

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('file:trk.root')
)

process.load("SimTracker.TrackAssociation.trackingParticleRecoTrackAsssociation_cfi")

process.tpRecoAssocGeneralTracks = process.trackingParticleRecoTrackAsssociation.clone()
process.tpRecoAssocGeneralTracks.label_tr = cms.InputTag("hiGeneralTracks")

process.load("SimTracker.TrackAssociatorProducers.quickTrackAssociatorByHits_cfi")
process.quickTrackAssociatorByHits.SimToRecoDenominator = cms.string('reco')

process.load("SimTracker.TrackerHitAssociation.tpClusterProducer_cfi")

# Input source
process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames =  cms.untracked.vstring(
#'file:../../../RecoHI/HiTracking/config_tmp/step3.root'
'file:step3.root'
#'/store/user/velicanu/Hydjet_Quenched_MinBias_5020GeV_750/Hydjet_Quenched_MinBias_5020GeV_750_RECODEBUG_v0/151117_112112/0000/step3_102.root'
)
)
### centrality ###
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi") 
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")
process.centralityBin.nonDefaultGlauberModel = cms.string("HydjetDrum5")

### Track cuts ###
# input collections
process.HITrackCorrectionsByAlgo.centralitySrc = cms.InputTag("centralityBin","HFtowers")
process.HITrackCorrectionsByAlgo.trackSrc = cms.InputTag("hiGeneralTracks")
process.HITrackCorrectionsByAlgo.qualityString = cms.string("highPurity")
process.HITrackCorrectionsByAlgo.pfCandSrc = cms.InputTag("particleFlowTmp")
process.HITrackCorrectionsByAlgo.jetSrc = cms.InputTag("akPu4CaloJets")
# options
process.HITrackCorrectionsByAlgo.useCentrality = False
process.HITrackCorrectionsByAlgo.applyTrackCuts = False
process.HITrackCorrectionsByAlgo.fillNTuples = False
process.HITrackCorrectionsByAlgo.applyVertexZCut = False
process.HITrackCorrectionsByAlgo.doVtxReweighting = False
process.HITrackCorrectionsByAlgo.doCaloMatched = False
process.HITrackCorrectionsByAlgo.doAlgoSeparation = True
# cut values
#process.HITrackCorrectionsByAlgo.dxyErrMax = 3.0
#process.HITrackCorrectionsByAlgo.dzErrMax = 3.0
#process.HITrackCorrectionsByAlgo.ptErrMax = 0.1
#process.HITrackCorrectionsByAlgo.nhitsMin = 11
#process.HITrackCorrectionsByAlgo.chi2nMax = 0.15
#process.HITrackCorrectionsByAlgo.reso = 0.2
process.HITrackCorrectionsByAlgo.dxyErrMax = 10.0
process.HITrackCorrectionsByAlgo.dzErrMax = 10.0
process.HITrackCorrectionsByAlgo.ptErrMax = 200
process.HITrackCorrectionsByAlgo.nhitsMin = 0
process.HITrackCorrectionsByAlgo.chi2nMax = 30
process.HITrackCorrectionsByAlgo.reso = 0.2
#process.HITrackCorrectionsByAlgo.crossSection = 1.0 #1.0 is no reweigh
#algo 
process.HITrackCorrectionsByAlgo.algoParameters = cms.vint32(4,23,22,24,7,5,8,9,10,11,37,38,39,40,41,42,43,44,45)
# vertex reweight parameters
process.HITrackCorrectionsByAlgo.vtxWeightParameters = cms.vdouble(0.0306789, 0.427748, 5.16555, 0.0228019, -0.02049, 7.01258 )
###
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '90X_upgrade2017_realistic_v6', '')
###
process.p = cms.Path(
                      process.tpClusterProducer *
                      process.quickTrackAssociatorByHits *
                      process.tpRecoAssocGeneralTracks *
#                      process.centralityBin *
                      process.HITrackCorrectionsByAlgo
)
