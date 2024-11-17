# Delphes Tutorial - DESY March 2020

## Pre-requisites

To successfully run this tutorial the Delphes virtual machine should be installed, see here for more information:

<https://twiki.cern.ch/twiki/bin/view/VBSCan/PREFIT20>

If you have successfully produced Pythia8 event files in the MadGraph and Parton Shower lecture (Admir Greljo, Ilaria Brivio), copy (or move) the pp->ll (SM and BSM) into the Delphes directory Delphes-3.5.0

FIXME: find out how these files were named during tutorial

If not you can download the files from here (but it might take a while):

```
cd Delphes-3.5.0
wget -O pp_ll_sm.hepmc https://cernbox.cern.ch/index.php/s/4rnlQ0bybBYvLTS/download
wget -O pp_ll_bsm.hepmc https://cernbox.cern.ch/index.php/s/Y71ZOw8ZiWWE0p2/download
```

The solution for these (simple) exercises can be found in the file [tutorial_solution_1.txt](/etc/tutorial_solution_1.txt). Consult it if you are stuck but before try to solve the question by yourself.

## I) Produce Delphes root files

In this section you will run Delphes Fast Detector simulation using the default CMS card. Delphes will produce a ROOT file starting from the HepMC format produced by MG5+Pythia8.

Produce two delphes output files, one for the sample SM and one for the BSM sample (`pp_ll_sm.root` and `pp_ll_bsm.root`), using the `DelphesHepMC2` executable and the CMS configuration card `cards/delphes_card_CMS.tcl`.

Hint: the command to produce a Delphes output

```
./DelphesHepMC2 cards/delphes_card.tcl output.root input.hepmc
```

## II) Simple Interactive Tree analysis

1\) Open the (`pp_ll_sm.root` Delphes ROOT tree and explore the branches, plot the electrons transverse momentum.

2\) Draw the muon and electron multiplicity via the ROOT command line.Do you understand these distributions?

3\) Compare the leading muon transverse momentum and pseudo-rapidity in the SM and the BSM sample.

## III) Write a simple analysis macro

1\) Write a python analysis macro `examples/InvariantMass.py` that selects two electrons or muons and produces the histograms of the invariant mass. To see an example check out `examples/Example1.py`.

2\) Run the analysis macro on the `pp_ll_sm.root` and `pp_ll_bsm.root` samples.

3\) Plot the di-electron and di-muon invariant on the same plot for both the SM sample. Which final state provides the best resolution? Why?

4\) Plot the di-electron and di-muon invariant on the same plot for both the BSM sample. Which final state provides the best resolution? Why?

## IV) Modify the Delphes detector card

We will now focus solely on the BSM sample `pp_ll_bsm.root` in the mu mu final state.

1\) Can you think of 2 detector parameters that determine and drive the sensitivity of the Z' -> mu mu search?

2\) Identify where they are configured in the Delphes detector card `cards/delphes_card_CMS.tcl`.

3\) Create two new detector configurations `cards/delphes_card_CMS_mod1.tcl` and `cards/delphes_card_CMS_mod2.tcl` by degrading these two parameters by a sizable factor.

4\) Reproduce a Delphes sample with these new configurations and observe the impact on the reconstructed Z' invariant mass distribution.
