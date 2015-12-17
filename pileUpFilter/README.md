# pileUpCorrector
pileUp filter for Run2 pp analysis

- pileUp filter candidates
	- <strong> pileUpFilter_baseCut_loose </strong>, apply a dzNtrk loose cut + dxy cut
	- <strong> pileUpFilter_baseCut_tight </strong>, apply a dzNtrk tight cut + dxy cut
	- <strong> pileUpFilter_baseCut_loose_dz1p0 </strong>, apply a dzNtrk loose cut + dxy cut + dz cut
	- <strong> pileUpFilter_baseCut_tight_dz1p0 </strong>, apply a dzNtrk tight cut + dxy cut + dz cut
	- <strong> pileUpFilter_vtx1 </strong>, the extreme cut, accept events with only 1 vertex exsit

See details in pileUpFilter/notebook/pileUpFilterMustRead.ipynb

## Instructions to add pileUp filter

if you haven't "git clone " the whole package, then do it now:

<pre><code> git clone https://github.com/cmsHiTracking/TrackingCode.git </code></pre>

assuming you have the <strong> TrackingCode </strong> in place and compiled, then

- go to your config file that runs, add the following line where you load includes 
<pre><code> process.load("TrackingCode.pileUpFilter.pileUpFilter_cff") </pre></code>
- add your filter candidate process in the <strong> cms.Path() </strong>, for example: <pre><code> process.pileUpFilter_baseCut_loose </pre></code>

Enjoy!

HI Tracking team


