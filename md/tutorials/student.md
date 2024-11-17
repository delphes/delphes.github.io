# Student Project BND - Spa September 2019

## Pre-requisites

To successfully run this tutorial the following prerequisite packages should be installed:

- gfortran/gcc/tcl:

For Linux users gcc/tcl should be already installed. For Mac users you should install XCode.

- ROOT:

Can be downloaded from <https://root.cern/install/all_releases>. Go to the latest release, and download a version under "Binary distributions".

- MadGraph5

a version of MG5 can be downloaded here: <https://launchpad.net/mg5amcnlo/2.0/2.5.x/+download/MG5_aMC_v2.5.5.tar.gz>

- Delphes

start from here: <https://delphes.github.io/workbook/quick-tour>

- Pythia8:

following instructions from here (or using the Pythia8 installation in MadGraph):

<https://delphes.github.io/workbook/pythia8>

## 0) Download data sample

From the Delphes main directory, download the pseudo-data file `data.root` :

```
wget -O data.root https://cernbox.cern.ch/index.php/s/MIjpBmZmXjHmNm2/download
```

## 1) Access information in the ROOT file

Open the ROOT file (ignore the various warnings) and visualize its content via the `TBrowser`.

```
root -l data.root
TBrowser t;
```

Open the Delphes Tree and then Event branch (by double-clicking). How many events are in this dataset? Likewise explore the Tree content by looking at other branches.

Non trivial information can also be plotted from the command line.

```
TFile *f = TFile::Open("data.root");
TBrowser browser;
f->Get("Delphes")->Draw("Muon.PT");
```

Some information is not directly accessible from the browser interface but can nevertheless be access via command line. Every Delphes object has a 4-vector (called `P4()`) member of type `TLorentzVector` (see here for documentation: <https://root.cern/doc/master/classTLorentzVector.html>)

So for example to plot the magnitude of the 3-momenta of the jets, or the jet invariant mass:

In order to perform an event-loop with a more sophisticated event selection you will have to write a small python macro. This macro takes as input the `data.root` and produce an output file that contains a couple of histograms. Download the file called [example.py](/etc/example.py), and run it via the command from the Delphes directory:

```
python example.py data.root hist_data.root
```

This will create a file called `hist_data.root` that can be browsed as done earlier with `data.root`.

## 2) Characterisation of a BSM excess

a) The provided data corresponds to LHC events that contains at least two isolated leptons (lepton=electron/muon) with pT > 15. Prove it
b) The data contains contains an excess corresponding to a new physical state. Find the observable that makes this excess explicit.

c) What is the new particle's mass?

d) What does it decay into?

e) For each decay channel define an event selection (the signal region) that enhances the significance of observation of this new state. A signal (10K generated events) and background (50K generated events) Monte Carlo samples can be downloaded here:

```
wget -O s.root https://cernbox.cern.ch/index.php/s/JcxNJON13BLJxtj/download
wget -O b.root https://cernbox.cern.ch/index.php/s/jVhihEWpZOa2UiL/download
```

f) For each decay channel, express the cross section times branching ratio as a function of the number of observed events (Nobs) and the number of background events (Nb) in the signal region, the integrated luminosity (L) and the event selection efficiency.

g) Express the number of background events in the signal region as function on the number of background events in some control region and the selection efficiency of background events in both the signal and control region. For both the decay channels.

h) Measure the background yield (Nb) from this data in "control region" using the data sample.

i) Measure the selection efficiency of background events in both the signal and control region from background Monte Carlo events. This sample contains initially respectively 25k ee and 25k mumu events.

j) Derive the background yield in the signal region using the formula derived in g).

k) Measure the signal efficiency from the signal Monte Carlo sample. The signal sample include total 10k events of which 5k into ee and 5k into mumu.

l) Compute the cross-section times branching ratio of this process with the available data in each decay channel. The dataset corresponds to 60 pb-1 of integrated luminosity.

m) Compute the uncertainty on the cross section in each channel including the uncertainties. It is a good custom to split the various uncertainty contributions into statistical, systematic, and luminosity. Assume 3% luminosity uncertainty. Assume 1% uncertainty on the muon efficiency and 2% for the electron efficiency.

n) Compute the ratio of the branching ratios into electrons and muons (with the associated uncertainties).

o) Produce a stacked plot of data signal and background in both the decay channels (hint: use `THStack` class of root if you want to write your own code, or make use of the [plotStack.py](/etc/plotStack.py) macro).

p) Identify another process that can that can reveal the presence of this particle (hint: this particle is massive).

q) Find an observable that explicitly reveals the process found in p).
