# Delphes Tutorial - MC4BSM July 2016

## Pre-requisites

To successfully build Delphes the following prerequisite packages should be installed:

- gcc/tcl:

For Linux users gcc/tcl should be already installed. For Mac users you should install XCode.

- ROOT:

Can be downloaded from <https://root.cern/install/all_releases>. Go to the latest release, and download a version under "Binary distributions".

Once it is installed, type:

```
source [path_to_installation]/root/bin/thisroot.sh
```

Then simply type in a terminal:

```
echo $ROOTSYS
```

If a path is shown then root is properly installed.

## Part I - Getting Started

0\) Create a tutorial directory:

```
mkdir DelphesTutorial
cd DelphesTutorial
```

1\) Get Delphes:

```
git clone https://github.com/delphes/delphes
cd delphes
```

OR, if you don't have Git installed, simply type (NOTE: you do not need to execute this step if you already cloned Delphes with git):

```
wget http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.3.2.tar.gz
tar -zxf Delphes-3.3.2.tar.gz
mv Delphes-3.3.2 delphes
cd delphes
```

2\) Install it:

```
./configure
make -j 4
```

3\) Download Z' (m= 2 TeV) to WW and dijet (pT > 1 TeV) events in stdhep format

```
wget http://cp3.irmp.ucl.ac.be/downloads/delphes_tuto/pp_zp_ww.hep.gz
wget http://cp3.irmp.ucl.ac.be/downloads/delphes_tuto/pp_jj.hep.gz
gunzip pp_zp_ww.hep.gz
gunzip pp_jj.hep.gz
```

4\) Finally, let's run Delphes. If the compilation went right, you should have three executables:

- `DelphesLHEF` -> should not be used
- `DelphesHepMC3` -> to be used on HepMC input format (\*.hepmc)
- `DelphesSTDHEP` -> to be used on STDHEP input format (\*.hep)

Type for instructions (note that output file comes before input file):

```
./DelphesSTDHEP
```

To run on our your input file, type:

```
./DelphesSTDHEP cards/delphes_card_CMS.tcl out_pp_zp_ww.root pp_zp_ww.hep
```

5\) Open freshly produced Delphes output with ROOT, and explore it.

```
root -l  out_pp_zp_ww.root
TBrowser t;
```

In the browser, double click on the `out_pp_zp_ww.root`, and then on the "Delphes" tree. Play around by double clicking on the various branches/observables.

You can then plot important observable with a simple selection with the following syntax:

```
Delphes->Draw("Muon.PT", "Muon.PT > 20");
Delphes->Draw("Electron.PT", "Electron.PT > 20");
```

Notes:

- `Delphes` is the tree name. It can be learned e.g. from `TBrowser`.
- `Muon` and `Electron` are the branch names.
- `PT` is a variable (leaf) of these branches.

```
Delphes->Draw("Jet.Mass","Electron_size + Muon_size == 1");
Delphes->Draw("Jet.Mass","Electron_size + Muon_size == 1 && Jet.PT > 500");
```

Objects are already ordered in PT, you can then plot the leading jet observables in this way:

```
Delphes->Draw("Jet[0].Mass");
Delphes->Draw("Jet[0].PT");
```

For more information on ROOT trees:

<https://delphes.github.io/workbook/root-tree-description>

## Part II - Understand and modify the configuration file

The Delphes card can be schematically divided in three parts:

- The `ExecutionPath` is where the simulation/reconstruction sequence of modules is defined
- The list of modules configurations.
- The `TreeWriter`, where the user defines which objects he stores in the output tree.

You can find an explanation for most Delphes modules here: <https://delphes.github.io/workbook/modules>

0\) Open the card `cards/delphes_card_CMS.tcl` with your favorite editor and try to make sense of it.

1\) Then configure the `FastJetFinder` module by switching on the options for jet substructure:

```
#############
  Jet finder
#############

module FastJetFinder FastJetFinder {
  set InputArray EFlowMerger/eflow

  set OutputArray jets

  # algorithm: 1 CDFJetClu, 2 MidPoint, 3 SIScone, 4 kt, 5 Cambridge/Aachen, 6 antikt
  set JetAlgorithm 5
  set ParameterR 0.8

  set ComputeNsubjettiness 1
  set Beta 1.0
  set AxisMode 4

  set ComputeTrimming 1
  set RTrim 0.2
  set PtFracTrim 0.05

  set ComputePruning 1
  set ZcutPrun 0.1
  set RcutPrun 0.5
  set RPrun 0.8

  set ComputeSoftDrop 1
  set BetaSoftDrop 0.0
  set SymmetryCutSoftDrop 0.1
  set R0SoftDrop 0.8

  set JetPTMin 20.0
}
```

2\) Now run Delphes with the newly modified card on both the dijet and Z' samples:

```
./DelphesSTDHEP cards/delphes_card_CMS.tcl out_pp_zp_ww_js.root pp_zp_ww.hep
./DelphesSTDHEP cards/delphes_card_CMS.tcl out_pp_jj_js.root pp_jj.hep
```

3\) Open the files with ROOT `TBrowser` as in the Getting Started section, and make sure that the new jet substructure variables are properly stored.

4\) Now download [macro.C](/etc/macro.C) and run this simple event selection macro. It will plot two crucial jet observables that can help in discriminating between a w-jet and a light jet: the jet mass, and the N-subjettiness ratio tau2/tau1.

```
wget hhttps://delphes.github.io/etc/macro.C --directory-prefix=examples
root examples/macro.C'("out_pp_jj_js.root","out_pp_zp_ww_js.root")'
```

5\) Now create a copy of the existing CMS card:

```
cp cards/delphes_card_CMS.tcl cards/delphes_card_CMS_nc.tcl
```

6\) Now edit the copy `cards/delphes_card_CMS_nc.tcl` to improve the calorimeter resolution, both energy and angular resolutions (by a factor 20):

```
#############
# Calorimeter
#############

...

# switching to 0.005 x 0.005 (eta,phi) calorimeter cell size for this tutorial

set PhiBins {}
  for {set i -360} {$i <= 360} {incr i} {
    add PhiBins [expr {$i * $pi/360.0}]
  }

  # 0.01 unit in eta up to eta = 2.5
  for {set i -1000} {$i <= 1000} {incr i} {
    set eta [expr {$i * 0.005}]
    add EtaPhiBins $eta $PhiBins
  }

 ...

# improve the energy resolution by a factor 0.05

  set ECalResolutionFormula {                  (abs(eta) <= 1.5) *0.05*(1+0.64*eta^2) * sqrt(energy^2*0.008^2 + energy*0.11^2 + 0.40^2) +
                             (abs(eta) > 1.5 && abs(eta) <= 2.5) *0.05* (2.16 + 5.6*(abs(eta)-2)^2) * sqrt(energy^2*0.008^2 + energy*0.11^2 + 0.40^2) +
                             (abs(eta) > 2.5 && abs(eta) <= 5.0) *0.05* sqrt(energy^2*0.107^2 + energy*2.08^2)}

  set HCalResolutionFormula {                  (abs(eta) <= 3.0) *0.05* sqrt(energy^2*0.050^2 + energy*1.50^2) +
                             (abs(eta) > 3.0 && abs(eta) <= 5.0) *0.05* sqrt(energy^2*0.130^2 + energy*2.70^2)}

```

7\) Re-run Delphes simulation and `macro.C` with the new configuration and appreciate the effect of improved resolution on the final distributions:

```
./DelphesSTDHEP cards/delphes_card_CMS_nc.tcl out_pp_zp_ww_js_nc.root pp_zp_ww.hep
./DelphesSTDHEP cards/delphes_card_CMS_nc.tcl out_pp_jj_js_nc.root pp_jj.hep
root examples/macro.C'("out_pp_jj_js_nc.root","out_pp_zp_ww_js_nc.root")'
```

## Part III - Event display

0\) Compile Delphes event display

```
make display
```

1\) Open event display on reconstructed events:

```
root -l examples/EventDisplay.C'("cards/delphes_card_CMS_nc.tcl","out_pp_zp_ww_js_nc.root")'
```

2\) A browser will open up. You can browse event from the "Event control tab". In the "Eve" tab you have access to the details of the event.

3\) Identify an event featuring dileptonic Z-> WW decay.

4\) Identify an event featuring a fully hadronic decay, where at least one of the two fatjets displays the characteristic two-prong structure of a boosted W.
