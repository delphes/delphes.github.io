# Delphes Tutorial - Hefei November 2018

## Pre-requisites

To successfully run this tutorial the following prerequisite packages should be installed:

- gcc/tcl:

For Linux users gcc/tcl should be already installed. For Mac users you should install XCode.

- ROOT:

Can be downloaded from <https://root.cern/install/all_releases>. Go to the latest release, and download a version under "Binary distributions".

- Pythia8:

following instructions from here (or using the Pythia8 installation in MadGraph):

<https://delphes.github.io/workbook/pythia8>

The solutions for all the exercises can be found in [tutorial_solution.txt](/etc/tutorial_solution.txt).

## I) Event generation with Pythia8 + Delphes sample

This exercise will teach how to configure the Pythia8 event generator for a simple production of e+e- -> ZH events. Next, you will generate events and simulate the detector with the DelphesPythia8 executable.

1\) Create a Pythia8 configuration card that generates N=10k events of ee->Zh->mumu at sqrt(s)=240 GeV (call it `examples/Pythia8/config_ee_zh_zmumu.cmd`).

```
Main:numberOfEvents = 10000         ! number of events to generate

Beams:idA = 11                   ! first beam, e- = -11
Beams:idB = -11                  ! second beam, e+ = 11
Beams:eCM = 240.                 ! CM energy of collision

! Higgsstrahlung process
HiggsSM:ffbar2HZ = on

! 5) Force the Z decays to muons
23:onMode = off
23:onIfAny = 13 -13
```

2\) Produce Delphes events using the above Pythia8 configuration (this command should run Pythia and Delphes on the fly), using the CEPC detector card `cards/delphes_card_CEPC.tcl`

```
./DelphesPythia8 cards/delphes_card_CEPC.tcl examples/Pythia8/config_ee_zh_zmumu.cmd delphes_ee_zh_zmumu.root
```

## II) Simple Tree analysis

1\) Open Delphes ROOT tree and explore the branches

```
root -l delphes_ee_zh_zmumu.root
gSystem->Load("libDelphes");
TBrowser t;
```

Note: Most objects are described in terms of pp specific variables (`PT`, `Eta`, `Phi`). This is simply for historical reasons (and makes of course no difference whatsoever) since Delphes was developed originally as a tool for LHC physics. To plot ee-like variables, one needs to write the translation (or make use of the very useful `TLorentzVector` of ROOT, see part III).

2\) Interactively draw the muon multiplicity and the jet multiplicity. You first have to double-click on the root file icon in the `TBrowser`. Do you understand these distributions?

```
Delphes->Draw("Muon_size");
Delphes->Draw("Jet_size");
```

## III) Write a simple analysis macro

1\) Write down the formula for the recoil Higgs mass.

2\) You can find a simple analysis macro in `example/Example1.py`. It can be executed like this:

```
python examples/Example1.py delphes_ee_zh_zmumu.root out.root
```

This `Example1.py` macro does not produce anything interesting here (it most likely produce an empty plot). The above command is simply shown as an example for how to run a macro. You should open `Example1.py` with a text editor, and write a small analysis that first selects events with two muons and then reconstructs and plot the recoil Higgs mass using the formula found in III.1)

Solution:

```
# Recoil Mass macro
#!/usr/bin/env python

import sys
import ROOT

if len(sys.argv) < 2:
  print " Usage: python examples/MissingMass.py delphes_ee_zh_zmumu.root hist_mrec.root"
  sys.exit(1)

ROOT.gSystem.Load("libDelphes")

try:
  ROOT.gInterpreter.Declare('#include "classes/SortableObject.h"')
  ROOT.gInterpreter.Declare('#include "classes/DelphesClasses.h"')
  ROOT.gInterpreter.Declare('#include "external/ExRootAnalysis/ExRootTreeReader.h"')
except:
  pass

inputFile = sys.argv[1]
outputFile = sys.argv[2]

# Create chain of root trees
chain = ROOT.TChain("Delphes")
chain.Add(inputFile)

# Create object of class ExRootTreeReader
treeReader = ROOT.ExRootTreeReader(chain)
numberOfEntries = treeReader.GetEntries()

# Get pointers to branches used in this analysis
branchMuon = treeReader.UseBranch("Muon")

# Book histograms
histMass = ROOT.TH1F("mass", "M_{recoil} [GeV]", 60, 100.0, 160.0)

ptot = ROOT.TLorentzVector(0.,0.,0.,240.)
# Loop over all events
for entry in range(0, numberOfEntries):
  # Load selected branches with data from specified event
  treeReader.ReadEntry(entry)

  # If event contains at least 2 muons
  if branchMuon.GetEntries() > 1:

    mu1 = branchMuon.At(0)
    mu2 = branchMuon.At(1)

    pll = mu1.P4() + mu2.P4()
    ph = ptot - pll

    histMass.Fill(ph.M())

out_root = ROOT.TFile(outputFile,"RECREATE")
histMass.Write()
```

## IV) Modify the Delphes detector card

You have now produced a Delphes simulated event with the hypothetical CEPC default detector configuration.

1\) Can you think of 2 detector parameters that determine and drive the sensitivity of the Higgs recoil measurement in this particular final state?

2\) Identify where they are configured in the Delphes detector card.

3\) Create two new detector configurations by degrading these two parameters by a sizable factor.

4\) Reproduce a Delphes sample with these new configurations and observe the impact on the recoil mass distribution.
