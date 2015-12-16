import FWCore.ParameterSet.Config as cms

import TrackingCode.pileUpFilter.pileUpFilter_cfi

pileUpFilter_default = TrackingCode.pileUpFilter.pileUpFilter_cfi.pileupVertexFilter.clone() 

### define your own filter ###

pileUpFilter_baseCut_loose = pileUpFilter_default.clone(
                                                           dzCutByNtrk = cms.vdouble(
                                                                                    999.,999.,999.,4.8,1.9,
                                                                                     1.2, 0.8, 0.8,0.8,0.6,
                                                                                     0.5, 0.4, 0.4,0.3,0.2,
                                                                                     0.2, 0.2, 0.2,0.2,0.2,
                                                                                     0.1, 0.1, 0.1,0.1,0.1,
                                                                                     0.1, 0.1, 0.1,0.1,0.1,
                                                                                     0.1, 0.0
                                                                                    ),  
                                                           dxyVeto = cms.double(0.05)
                                                       )

pileUpFilter_baseCut_tight = pileUpFilter_default.clone(
                                                           dzCutByNtrk = cms.vdouble(
                                                                                    999.,999.,4.0,1.5,1.0,
                                                                                     0.6, 0.5,0.4,0.3,0.3,
                                                                                     0.3, 0.2,0.2,0.2,0.1,
                                                                                     0.1, 0.1,0.1,0.1,0.1,
                                                                                     0.1, 0.1,0.1,0.0
                                                                                    ),
                                                           dxyVeto = cms.double(0.05) 
                                                       )

pileUpFilter_baseCut_loose_dz1p0 = pileUpFilter_default.clone(
                                                           dzCutByNtrk = cms.vdouble(
                                                                                    999.,999.,999.,4.8,1.9,
                                                                                     1.2, 0.8, 0.8,0.8,0.6,
                                                                                     0.5, 0.4, 0.4,0.3,0.2,
                                                                                     0.2, 0.2, 0.2,0.2,0.2,
                                                                                     0.1, 0.1, 0.1,0.1,0.1,
                                                                                     0.1, 0.1, 0.1,0.1,0.1,
                                                                                     0.1, 0.0
                                                                                    ),
                                                           dxyVeto = cms.double(0.05),
                                                           dzTolerance = cms.double(1.0)
                                                       )

pileUpFilter_baseCut_tight_dz1p0 = pileUpFilter_default.clone(
                                                           dzCutByNtrk = cms.vdouble(
                                                                                    999.,999.,4.0,1.5,1.0,
                                                                                     0.6, 0.5,0.4,0.3,0.3,
                                                                                     0.3, 0.2,0.2,0.2,0.1,
                                                                                     0.1, 0.1,0.1,0.1,0.1,
                                                                                     0.1, 0.1,0.1,0.0
                                                                                    ),
                                                           dxyVeto = cms.double(0.05),
                                                           dzTolerance = cms.double(1.0)
                                                       )

pileUpFilter_vtx1 = pileUpFilter_default.clone(
                                                           dzCutByNtrk = cms.vdouble(
                                                                                     999.,0.0,0.0,0.0,0.0
                                                                                    ),
                                                           dzTolerance = cms.double(9999.0)

                                                )                                      



