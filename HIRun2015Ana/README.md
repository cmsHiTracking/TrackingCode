# Tracking Efficiency Corrections 

This Repo can help you obtain the tracking performance plots and tracking efficiency correction table for both pp and PbPb. Besides <strong> highPurity </strong>, there are a few more track cuts that have been applied in default, please check in the config file at /HIRun2015Ana/test/run_PbPb_cfg.py (or run_pp_cfg.py). Also see detail documentation in <strong> /HIRun2015Ana/notebook/TrackingEfficiencyMustRead.ipynb </strong>

- Go to /HIRun2015Ana/test/run_PbPb_cfg.py
- Double check the block "Track Cuts" to see if the track cuts are set correctly
	- track-trigger cuts or non-track-trigger cuts
	- vertex reweigh
	- cross section reweigh (if dijet samples)
	- centrality
	- calo matching
- Choose the corresponding sample (GlobalTag is needed for Centrality object)
- cmsRun 

The output is a few 2D and 3D histograms in default. Option of filling Ntuple is also available in config. 

- Go to /macros/
- run <pre><code> root -l plotHist2D.C </pre></code> for performance plots with overall centrality 
- run <pre><code> root -l plotHist3D.C </pre></code> for performance plots with different centrality 
- See <strong> Demo.C </strong> for correction table


<strong> Additional information: if there is anything needs to be changed in source code, for example adding new variables for cuts, please contact the tracking team. </strong>



