### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()
config.General.requestName = 'PbPb_eff_v5'
config.General.workArea = 'PbPb_eff_v5'
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_PbPb_cfg.py'

config.Data.inputDBS = 'phys03'
config.Data.inputDataset = '/Hydjet_Quenched_MinBias_5020GeV_750/velicanu-Hydjet_Quenched_MinBias_5020GeV_750_RECODEBUG_v0-eb8cf5655150b59e96d879ea397567ad/USER'
#config.Data.inputDataset = '/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/velicanu-Pythia8_Dijet80_pp_TuneCUETP8M1_Hydjet_MinBias_5020GeV_PrivMC-282baa650b1997daa0dd8689f6a69785/USER'
config.Data.splitting = 'FileBased'
config.Data.ignoreLocality = False
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Site.storageSite = 'T2_US_MIT'
config.Site.whitelist = ['T2_US_MIT']
