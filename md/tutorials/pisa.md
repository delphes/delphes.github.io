# Pythia8+Delphes Tutorial - Pisa September 2018

## Pre-requisites

To successfully run this tutorial the following prerequisite packages should be installed:

- gcc/tcl:

For linux users gcc/tcl should be already installed. For Mac users you should install XCode.

- ROOT:

can be downloaded from <https://root.cern.ch/downloading-root> Go on latest release, and download a version under "Binary distributions".

- Pythia8:

following instructions from here: [/workbook/pythia8](/workbook/pythia8)

## I) Event generation with Pythia8 + Delphes sample

This exercise will teach how to configure the Pythia8 event generator for a simple production of e+e- -> ZH events. Next, you will generate events and simulate the detector with the DelphesPythia8 executable.

1\) First have a look at the Pythia8 configuration file "examples/Pythia8/configNoLHE.cmnd". In this card identify the parameters that control:

- the number of events to be generated
- the nature of the colliding beams
- the center of mass energy
- the physics process to be generated

2\) Create a Pythia8 configuration card that generates N=10k events of ee->Zh->mumu at sqrt(s)=240 GeV.

Find the above process in the Pythia8 manual (Hint: under "Higgs", then "Standard-Model Higgs, basic processes"):

<http://home.thep.lu.se/~torbjorn/pythia81html/Welcome.html>

Hint1: the code of electron (positron) is 11 (-11).

Hint2: the Z decay can be forced to muons with the following syntax:

```
23:onMode = off
23:onIfAny = 13 -13
```

3\) Produce Delphes events using the above Pythia8 configuration (this command should run Pythia and Delphes on the fly!), using the CEPC detector card "cards/delphes_card_CEPC.tcl"

Hint: find the command to be executed here (adapting it to the above Delphes and Pythia8 cards of course):

[/workbook/pythia8](/workbook/pythia8)

## II) Simple Tree analysis

1\) Open Delphes ROOT tree and explore the branches

```
root -l delphes_ee_zh_zmumu.root
gSystem->Load("libDelphes");
TBrowser t;
```

Note: Most objects are described in terms of pp specific variables (PT, Eta, Phi). This is simply for historical reasons (and makes of course no difference whatsoever) since Delphes was developed originally as a tool for LHC physics. To plot ee-like variables, one needs to write the translation (or make use of the very useful TLorentzVector of ROOT, see part III).

2\) Interactively draw the muon multiplicity and the jet multiplicity. Do you understand these distributions?

## III) Write a simple analysis macro

1\) Write down the formula for the recoil Higgs mass.

2\) You can find a simple analysis macro in "example/Example1.py". It can be executed like this:

```
python examples/Example1.py delphes_ee_zh_zmumu.root
```

This Example1.py macro does not produce anything interesting here (it most likely produce an empty plot). The above command is simply shown as an example for how to run a macro. You should open Example1.py with a text editor, and write a small analysis that first selects events with two muons and then reconstructs and plot the recoil Higgs mass using the formula found in III.1)

## IV) Modify the Delphes detector card

You have now produced a Delphes simulated event with the hypothetical CEPC default detector configuration.

1\) Can you think of 2 detector parameters that determine and drive the sensitivity of the Higgs recoil measurement in this particular final state?

2\) Identify where they are configured in the delphes detector card.

3\) Create two new detector configurations by degrading these two parameters by a sizable factor.

4\) Reproduce a Delphes sample with these new configurations and observe the impact on the recoil mass distribution.
