# pileUpCorrector
pileUp filter for Run2 analysis

- pileUp filter candidates
	- 5TeV pp
	- <strong> pileUpFilter_pp5TeV_vtx1 </strong>, the extreme cut, accept events with only 1 vertex 
	- <strong> pileUpFilter_pp5TeV_Gplus </strong>, apply a dzNtrk cut 
	- <strong> olvFilter_pp5TeV_dz1p0 </strong>, apply a dzNtrk cut + dz cut at 1 cm
	- 8TeV pPb
	- <strong> pileUpFilter_pPb8TeV_vtx1 </strong>, the extreme cut, accept events with only 1 vertex 
	- <strong> pileUpFilter_pPb8TeV_Gplus </strong>, apply a dzNtrk cut 
	- <strong> olvFilter_pPb8TeV_dz1p0 </strong>, apply a dzNtrk cut + dz cut at 1 cm

See details in pileUpFilter/notebook/pileUpFilterMustRead.ipynb

## Instructions to add pileUp filter

if you haven't "git clone " the whole package, then do it now:

<pre><code> git clone https://github.com/cmsHiTracking/TrackingCode.git </code></pre>

assuming you have the <strong> TrackingCode </strong> in place and compiled, then

- go to your cmsRun config file that runs, add the following line where you load the includes 
<pre><code> process.load("TrackingCode.pileUpFilter.pileUpFilter_cff") </pre></code>
- add your favorite filter candidate process in the <strong> cms.Path() </strong>, for example: <pre><code> process.pileUpFilter_pPb8TeV_vtx1 </pre></code>

Enjoy!

HI Tracking team


