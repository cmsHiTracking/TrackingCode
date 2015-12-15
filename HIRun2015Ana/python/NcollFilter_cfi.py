import FWCore.ParameterSet.Config as cms

ncollFilter  = cms.EDFilter('NcollFilter',
    generators = cms.VInputTag(cms.InputTag("generator")),
    ncollmax = cms.int32(3000)
)
