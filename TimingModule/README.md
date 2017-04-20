In order to get timeing info for running Modules, need to add the Timing service into configuration file:

process.Timing = cms.Service("Timing",
  		summaryOnly = cms.untracked.bool(False),
	  	useJobReport = cms.untracked.bool(True)
		)

(ref: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideEDMTimingAndMemory )

and using cmsRun config.py &> output.txt & save the timing info screen output to file.

then run the timeRecord.sh , ( replace PbPbste3.txt with your output.txt name)


In the output file, TimingModule.txt,

first part is average timing per Module, Second part is average Timing per label.

they are listed by descending order along with percentage timing compare to a event,

thus you can easily find which module take the most of time.





p.s.

The output file is quite lenghty and size is big if you want to process lots of events.

I am trying to switch to different approach, something like DQM tools, which can directly

grab info and save it into root file. 

Previously Stanislav Lisniak has done that here : https://twiki.cern.ch/twiki/bin/view/Main/HiTimeAnalyzer

but unfortuantly the package he developed is lost after he left, It would be good if someone happened to have a copy of it,

or I would try to re-invent the wheel again. 


