from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

import FWCore.ParameterSet.Config as cms
#load the cfi file and rewrite cross section parameter each time:
process = cms.Process('TRACKANA')
process.load("TrackingCode.HIRun2015Ana.HITrackCorrectionAnalyzer_cfi")
cs = [0.00005269, 0.000003455, 4.068e-7, 4.959e-8, 7.096e-9, 1.223e-9, 3.031e-10, 7.746e-11, 1.41e-11, 3.216e-12,1.001e-12]

config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_PbPb_cfg.py'
config.Data.inputDataset = '/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/dgulhan-Pythia8_Dijet15_pp_TuneCUETP8M1_Hydjet_MinBias_5020GeV_RECODEBUG_758_PrivMC-3e72696a43b93eac877e11bff9ae8846/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'multicrab_PbPb_dijet'

config.Site.storageSite = 'T2_US_MIT'

if __name__ == '__main__':
   from CRABAPI.RawCommand import crabCommand
   from CRABClient.ClientExceptions import ClientException
   from httplib import HTTPException

   config.General.workArea = 'multicrab_PbPb_dijet_v2'

   def submit(config):
      try:
           crabCommand('submit', config = config)
      except HTTPException as hte:
           print "Failed submitting task: %s" % (hte.headers)
      except ClientException as cle:
          print "Failed submitting task: %s" % (cle)
   
   sampleName = [15,30,50,80,120,170,220,280,370,460,540]

   for num in range(0,11):

       print "double check the dijet%r sample with the corresponding cross section %r " % (sampleName[num], cs[num])
 
       process.HITrackCorrections.crossSection = cs[num]       
 
       RequestName = 'multicrab_PbPb_dijet_'+str(num)
       DataSetName = '/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/dgulhan-Pythia8_Dijet'+ str(sampleName[num]) +'_pp_TuneCUETP8M1_Hydjet_MinBias_5020GeV_RECODEBUG_758_PrivMC-3e72696a43b93eac877e11bff9ae8846/USER'
       config.General.requestName = RequestName
       config.Data.inputDataset = DataSetName
       submit(config)

# python crab3_ppTrackingAnalyzer.py to execute 
# ./multicrab -c status -w crab_projects/ to check status 
