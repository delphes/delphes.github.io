# MG5+Delphes Tutorial - Bologna June 2016

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

## MadGraph5/MadEvent basic tutorial (@Leading Order)

In this part you are going to learn how to generate pardon-level and showered events with MadGraph5 (interfaced with Pythia6).

0\) Create a new directory:

```
mkdir DelphesTutorial
cd DelphesTutorial
```

1\) Download and install MG5 by typing in a terminal:

```
wget https://launchpad.net/mg5amcnlo/2.0/2.4.0/+download/MG5_aMC_v2.4.0.tar.gz
tar xzvf MG5_aMC_v2.4.0.tar.gz
```

2\) Launch MG5:

```
cd MG5_aMC_v2_4_0
./bin/mg5_aMC
```

3\) Install Pythia6 and MadAnalysis:

```
install pythia-pgs
install MadAnalysis
```

4\) Generate a LO Drell-Yan process:

```
generate p p > e+ e-
display diagrams
```

5\) Generate a LO Higgs process:

```
generate p p > h > e+ e- mu+ mu-
```

The diagram generation fails ... do you understand why? Type instead:

```
import model heft
generate p p > h > e+ e- mu+ mu-
display diagrams
```

This generates also diagrams containing photon internal lines. To veto that diagram type the following:

```
generate p p > h > e+ e- mu+ mu-  / a
display diagrams
```

6\) Let's generate some events

```
output pp_h_eemm
launch pp_h_eemm
```

You will be prompted with a screen asking questions ... Type "ENTER". Another screen comes and asks you if you want to edit a bunch of configuration cards:

- `param_card.dat` is where the parameters of the model are stored (masses, couplings)
- `run_card.dat` is where the parameters of run are defined (ecm, number of events, generation level cuts ...)
- `pythia_card.dat` is where parameters of the shower are defined

Open `param_card.dat` and `run_card.dat` by typing respectively `1` and `2`and have a look at them, but do not modify them for now. The editor is `vi`, so to quit type `:q`. Type "ENTER" to launch the parton-level generation.

7\) When it's done, you should be prompted with a web browser. If not quit MG5 by typing `exit`, and open the html file that was created at the end of the run with your web browser:

```
firefox [MG5DIR]/pp_h_eemm/Events/index.html
```

Click on "Results and Event Database" and then on "LHE plots". Have a look at the automatically generated parton-level plots. Explain the Ecm plot (this is the total invariant mass of the system, i.e of the four final state leptons).

8\) Enter in MG5 again, and type:

```
./bin/mg5_aMC
import model heft
```

```
generate p p > h , h > e+ e- mu+ mu- / a
display diagrams
```

Then:

```
output pp_h_eemm_res
launch pp_h_eemm_res
```

Note the different syntax. This time, when you will be prompted with the screen asking questions ... Type `1`. This will activate parton and hadronization with Pythia6, and then type ENTER. When the generation is done, have a look again at the parton-level plots.

9\) Generate a new set of events, this time setting in the param_card mH = 750 GeV. Note that since we are keeping the higgs width value corresponding to mH = 125 GeV, this won't be a proper SM higgs with mH = 750 GeV.

For this we don't need to re-generate the diagrams, we can simply type `launch` and edit the param_card by changing the higgs mass when prompted. If everything worked smoothly you should have two event samples with 10k events each. Events are stored in `[MG5DIR]/pp_h_eemm_res/Events/run_01(02)`

Now to quit MG5, type `exit`. In each run sub-directory, only two files are interesting for us:

- `unweighted_events.lhe` contains hard-interaction events only, pre-hadronization and PS, it is human readable, in so-called Les-Houches Event format (in short LHE)

- `tag_1_pythia_events.hep` contains showered and hadronized events, it is the event file that we are going to give as input to the Delphes simulation.

This ends the very basic introduction to MG5. For an extensive list of tutorials, lectures about this tool (including matching, NLO generation, etc), have a look at the MadGraph School 2015 page:

<https://www.physics.sjtu.edu.cn/madgraphschool/>

## Delphes Tutorial

### Part I - Getting Started

0\) Go back to the DelphesTutorial directory

1\) Get Delphes:

```
git clone https://github.com/delphes/delphes
cd delphes
```

or, if you don't have Git installed, simply type:

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

3\) Unzip the event files previously generated with MG5, and move them in your `delphes` directory

```
gunzip ../MG5_aMC_v2_4_0/pp_h_eemm_res/Events/run_01/tag_1_pythia_events.hep.gz
gunzip ../MG5_aMC_v2_4_0/pp_h_eemm_res/Events/run_02/tag_1_pythia_events.hep.gz
```

```
mkdir -p input
mv ../MG5_aMC_v2_4_0/pp_h_eemm_res/Events/run_01/tag_1_pythia_events.hep input/pp_h_eemm_m125.hep
mv ../MG5_aMC_v2_4_0/pp_h_eemm_res/Events/run_02/tag_1_pythia_events.hep input/pp_h_eemm_m750.hep
```

4\) Finally, let's run Delphes. If the compilation went right, you should have three executables:

- `DelphesLHEF` -> should not be used
- `DelphesHepMC` -> to be used on HepMC input format (`*.hepmc`)
- `DelphesSTDHEP` -> to be used on STDHEP input format (`*.hep`)

Type for instructions (note that output file comes before input file):

```
./DelphesSTDHEP
```

To run on our your input file, type:

```
./DelphesSTDHEP cards/delphes_card_CMS.tcl delphes_output_m125.root input/pp_h_eemm_m125.hep
```

5\) Open freshly produced Delphes output with ROOT, and explore it.

```
root -l delphes_output_m125.root
TBrowser t;
```

In the browser, double click on the `delphes_output_m125.root`, and then on the "Delphes" tree. Play around by double clicking on the various branches/observables.

You can then play plot important observable with a simple selection with the following syntax:

```
Delphes->Draw("Muon.PT", "Muon.PT > 20");
Delphes->Draw("Electron.PT", "Electron.PT > 20");
```

Notes:

- `Delphes` is the tree name. It can be learned e.g. from `TBrowser`.
- `Muon` and `Electron` are the branch names.
- `PT` is a variable (leaf) of these branches.

```
Delphes->Draw("Muon.Eta", "Muon.PT > 20");
Delphes->Draw("Electron.Eta", "Electron.PT > 20");
Delphes->Draw("Jet_size","Electron_size > 1 && Muon_size > 1");
```

Objects are already ordered in PT, you can then plot leading ele/mu in this way:

```
Delphes->Draw("Muon[0].PT", "Muon.PT > 20");
Delphes->Draw("Electron[0].PT", "Electron.PT > 20");
```

For more information on ROOT trees:

<https://delphes.github.io/workbook/root-tree-description>

### Part II - Run a macro-based analysis on Delphes output

1\) The macro examples/Example3.C produces resolution plots comparing reconstructed vs MC truth quantities. Run it on the delphes output:

```
root -b -q examples/Example3.C'("delphes_output_m125.root")'
```

It produces a bunch of plots in PNG format. Open them with your favorite image viewer:

```
open *.png
```

or

```
eog *.png
```

or

```
firefox *.png
```

or

```
display *.png
```

Understand:

- Why is the eta resolution plot for electron and muons different compared to photons?
- Where do photons come from?
- Why is the jet resolution plot shifted?

2\) Let's now run a real event selection, and plot some interesting quantities. We select events with:

- \>= 2 opposite sign isolated electrons, pT > 10 GeV, |eta| \< 2.5
- \>= 2 opposite sign isolated muons, pT > 10 GeV, |eta| \< 2.5

Construct 3 invariant masses and fill them in histograms:

- min( m(e+ e-), m(mu+ mu-) )
- max( m(e+ e-), m(mu+ mu-) )
- m (e+ e- mu+ mu-)

Download the [HZZ.C](/etc/HZZ.C) macro and save in the `examples` directory. Then open it with your favorite text editor, and make sure you understand what it does. Then run it:

```
root -b -q  examples/HZZ.C'("delphes_output_m125.root")';
```

Some plots are produced. Open the produced png file.

- Explain the left plot.
- Appreciate the effect of detector resolution by comparing the gen and reco histograms

Now redo this analysis, but this time using the mH = 750 GeV input file. Do not edit directly the `HZZ.C` file, make a copy of it and edit the copy rather.

- Spot the differences with the mH = 125 GeV case and explain them.

### Part III - The detector card (or configuration file)

Delphes is a modular framework. The modular system allows the user to configure and schedule modules via a configuration file, add modules, change data flow, alter output information.

A module is schematically a piece of code that takes as input one or more arrays of objects (`TObjArray`) and produces one or more arrays of objects. It has a set of configurable parameters (i.e. resolutions, efficiencies parametrization, magnetic field value, calorimeter granularity, ...).

All the modules and data-flow are configured in the detector card. You can find several pre-configured detector cards in the `cards` directory.

0\) Open the CMS card with your favorite and try to understand it:

The card can be schematically divided in three parts:

- The `ExecutionPath` is where the simulation/reconstruction sequence of modules is defined.
- The list of modules configurations.
- The `TreeWriter`, where the user defines which objects he stores in the output tree.

You can find an explanation for most modules here:

<https://delphes.github.io/workbook/modules>

1\) Modify the muon resolution. First copy the existing card. We will edit that later.

```
cp cards/delphes_card_CMS.tcl cards/delphes_card_CMS_mod.tcl
```

In the newly copied card `cards/delphes_card_CMS_mod.tcl` find where the muon resolutions are defined and make them worse by a factor 5.

Re-run the simulation and analysis, and appreciate the effect of worsening the smearing.

```
./DelphesSTDHEP cards/delphes_card_CMS_mod.tcl delphes_output_m125_mures5x.root input/pp_h_eemm_m125.hep
root -b -q examples/HZZ.C'("delphes_output_m125_mures5x.root")'
```

2\) Now, apply a similar worsening on the electrons, and re-run:

```
./DelphesSTDHEP cards/delphes_card_CMS_mod.tcl delphes_output_m125_mures5x_ele5x.root input/pp_h_eemm_m125.hep
root -l examples/HZZ.C'("delphes_output_m125_mures5x_ele5x.root")'
```

What do you see? Explain ... (hint: Particle-Flow)

Now find the ECAL resolution and apply the same 5x worsening, and re-run:

```
./DelphesSTDHEP cards/delphes_card_CMS_mod.tcl delphes_output_m125_mures5x_ele5x_v2.root input/pp_h_eemm_m125.hep
root -l examples/HZZ.C'("delphes_output_m125_mures5x_ele5x_v2.root")'
```

### Part IV - Write a new module

In this section we are going to create a module called Timing. This module will take as input a collection of particles. It will produce an output collection of particles with a smeared time variable according to some user defined resolution. It will also store the initial and final time pre-smearing.

0\) Copy the template module to the new one:

```
cp modules/ExampleModule.h modules/Timing.h
cp modules/ExampleModule.cc modules/Timing.cc
```

In these two files replace all `ExampleModule` with `Timing`.

1\) Add the Timing module in modules/ModulesLinkDef.h:

```
#include "modules/Timing.h"
...
#pragma link C++ class Timing+;
```

2\) In the main `delphes` dir, type:

```
./configure
make
```

You have just added your first empty module in Delphes.

3\) Understand the following piece of code and replace the existing `Process()` method in the newly created module. Then edit the rest of the Timing class (both the .cc and .h), in order to be able to compile.

```
void Timing::Process()
{
  Candidate *candidate, *mother, *particle;
  Double_t t0, tf, t0_smeared, tf_smeared;
  const Double_t c_light = 2.99792458E8;

  fItInputArray->Reset();
  while((candidate = static_cast<Candidate*>(fItInputArray->Next())))
  {

    //access particle before delphes processing
    particle = static_cast<Candidate*>(candidate->GetCandidates()->At(0));

    //4-position before propagation
    const TLorentzVector &initialPosition = particle->Position;
    //4-position after propagation
    const TLorentzVector &finalPosition   = candidate->Position;

    //initial and final time (in mm)
    t0 = initialPosition.T();
    tf = finalPosition.T();

    // apply time smearing on time after propagation
    tf_smeared = gRandom->Gaus(tf, fTimeResolution*1.0E3*c_light);

    // correct initial time
    t0_smeared = t0 + tf_smeared - tf;

    //now store these new variables
    mother = candidate;
    candidate = static_cast<Candidate*>(candidate->Clone());
    candidate->AddCandidate(mother);

    candidate->genT0 = t0;
    candidate->genTF = tf;
    candidate->T0 = t0_smeared;
    candidate->TF = tf_smeared;
    candidate->ErrorT = (tf_smeared - tf);

    fOutputArray->Add(candidate);

  }
}
```

4\) Add the new variables `T0`, `TF`, `genT0`, `genTF`, `ErrorT` to the `Candidate` class. For this, you will have to edit the files `classes/DelphesClasses.h` and `classes/DelphesClasses.cc`. The `Candidate` class is defined in `classes/DelphesClasses.h`. Other methods involving the `Candidate` class are defined in `classes/DelphesClasses.cc`:

- `Candidate` (constructor)
- `Copy`
- `Clear`

If you did things properly you should be able to compile.

```
./configure
make
```

We are not done yet... The newly computed timing information is now properly stored and propagated inside Delphes. However, we have to decide which objects will display this new information.

5\) Let's store this information in Tracks. Find this classes in `classes/DelphesClasses.h` and add the new variables. Compile.

6\) Now we have to tell Delphes that we want these variables to appear in our final root tree.

```
entry->T0 = (candidate -> T0)*1.0E-3/c_light;
entry->TF = (candidate -> TF)*1.0E-3/c_light;
entry->genT0 = (candidate -> genT0)*1.0E-3/c_light;
entry->genTF = (candidate -> genTF)*1.0E-3/c_light;
entry->ErrorT = (candidate -> ErrorT)*1.0E-3/c_light;
```

Store these variables in the `Track` objects by editing the `ProcessTracks` method in `modules/TreeWriter.cc`. Compile.

7\) Now first call the `Timing` module in the execution path the `delphes_card_CMS_PileUp.tcl` card:

```
set ExecutionPath {

  PileUpMerger
  ParticlePropagator

  ChargedHadronTrackingEfficiency
  ElectronTrackingEfficiency
  MuonTrackingEfficiency

  ChargedHadronMomentumSmearing
  ElectronMomentumSmearing
  MuonMomentumSmearing

  TrackMerger
  Timing

  TreeWriter
}

```

Then configure the `Timing` module:

```

module Timing Timing {
  set InputArray TrackMerger/tracks
  set OutputArray tracks

  # assume 20 ps resolution for now
  set TimeResolution 20E-12
}
```

Then store the the `Track` branch in the root output tree (replace the existing `TreeWriter` section):

```
module TreeWriter TreeWriter {
# add Branch InputArray BranchName BranchClass
  add Branch Timing/tracks Track Track
  add Branch PileUpMerger/vertices Vertex Vertex
}
```

8\) Set the average pile-up to 200 in the card in the `PileUpMerger` module.

```
module PileUpMerger PileUpMerger {
  set InputArray Delphes/stableParticles
   ...
  # average expected pile up
  set MeanPileUp 200
  ...
}

```

9\) Simplify detector card that produces only `Tracks` out of the `Timing` module.

10\) Add the following at the top of the card to run on 1k events only:

```
set MaxEvents 1000
```

11\) Make three different runs with 20/100/500ps time resolution. Open the output trees and plot the new variables.

```
./DelphesSTDHEP cards/delphes_card_CMS_PileUp.tcl test_20ps.root input/pp_h_eemm_m125.hep
```

12\) Download [TimingAnalysis.C](/etc/TimingAnalysis.C) macro and run it. This macro isolates the four highest PT tracks. The hard vertex is taken to be that given by the most energetic track. The difference in time between the first and the fourth track is plotted. Explain what you see.

```
root -l examples/TimingAnalysis.C'("test_20ps.root")'
```
