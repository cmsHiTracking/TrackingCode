Note that all configs only generate a few events by default; you might have to change the number of events or input files as you wish.


1) For generating samples:
code comes from runTheMatrix workflow 158.0

GENSIM step:

Config defaults to b=12 events (peripheral)
You can easily get heavy (central) events by changing bFixed to 0 (b=0 evts)
For MinBias, set cFlag=1 (overwrites bFixed parameter above)

cmsRun Hydjet_Quenched_B12_5020GeV_cfi_GEN_SIM.py

DIGI RAW:

cmsRun step2_DIGI_L1_DIGI2RAW_HLT_PU.py





2) Running Reconstruction (works on output of step 1 OR official MC.  If you want to test performance, the input MC MUST BE RAWDEBUG OR Full Event Content)
code comes from runTheMatrix workflow 158.0

RECO (pp_on_AA era):

Defaults to RECODEBUG event content.  If you want to check event sizes, etc. you need to change the output module data type to AODSIM.  The timing information is stored to out.txt.  If you do not want timing info, you can omit everything after '.py'.

cmsRun step3_RAW2DIGI_L1Reco_RECO.py > out.txt 2>&1 &




3) Checking timing
code written by cheng-chieh peng


Copy out.txt into the Timing directory, and then run Timing/timeRecord.sh:

cp out.txt Timing/; cd Timing; ./timeRecord.sh

A timing summary can then be found in Timing/TimingModule.txt





4) Checking performance
Standard tracking group efficiency code + HIForest-style tree for debugging

navigate to the analyzer directory:
cd HITrackingStudies/test/

edit run_PbPb_cfg.py to get the settings you want (the cuts are the most relevant thing here)

cmsRun run_PbPb_cfg.py

Output file is trk.root
