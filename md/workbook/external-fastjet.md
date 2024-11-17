# Running Delphes with External FastJet

## Introduction

This section explains how you can run your own FastJet code on Delphes particles. We provide two examples in the [examples/ExternalFastJet]($source$/examples/ExternalFastJet) directory, [examples/ExternalFastJet/ExternalFastJetBasic.cpp]($source$/examples/ExternalFastJet/ExternalFastJetBasic.cpp) and [examples/ExternalFastJet/ExternalFastJetHepMC.cpp]($source$/examples/ExternalFastJet/ExternalFastJetHepMC.cpp).

Both examples convert generated events into Delphes candidates, perform event reconstruction, and pass reconstructed particles to anti-kT clustering. `ExternalFastJetHepMC` takes as input an HepMC event file, while `ExternalFastJetBasic` has internally defined input particles.

The [cards/delphes_card_CMS_NoFastJet.tcl]($source$/cards/delphes_card_CMS_NoFastJet.tcl) configuration detector card is a truncated version of the [cards/delphes_card_CMS.tcl]($source$/cards/delphes_card_CMS.tcl), as the reconstruction is stopped after producing collections of calorimeter towers and particle-flow objects, before jet and high level object isolation and identification. Similar cards for the ATLAS and the FCC detectors can be produced by truncating [cards/delphes_card_ATLAS.tcl]($source$/cards/delphes_card_ATLAS.tcl) and [cards/FCC/FCChh.tcl]($source$/cards/FCC/FCChh.tcl) likewise.

The input particle collection to jet clustering are specified inside [examples/ExternalFastJet/ExternalFastJetBasic.cpp]($source$/examples/ExternalFastJet/ExternalFastJetBasic.cpp) and [examples/ExternalFastJet/ExternalFastJetHepMC.cpp]($source$/examples/ExternalFastJet/ExternalFastJetHepMC.cpp) via:

```c++
inputArray = modularDelphes->ImportArray("ModuleInstanceName/arrayName");
```

By default the particle-flow collection `EFlowMerger/eflow` is taken. This can be easily changed to simple calorimeter towers, tracks, or stable generated particles (or any other collection defined in the configuration card) by defining instead:

```c++
inputArray = modularDelphes->ImportArray("EFlowMerger/eflow");  // particle-flow objects
```

or

```c++
inputArray = modularDelphes->ImportArray("Calorimeter/towers"); // calorimeter objects
```

or

```c++
inputArray = modularDelphes->ImportArray("TrackMerger/tracks"); // charged tracks
```

or

```c++
inputArray = modularDelphes->ImportArray("Delphes/stableParticles"); // all gen-level stable particles
```

## Setup and build

In order to run Delphes with your own FastJet installation you first need to install Delphes and FastJet (to install Delphes, see [here](/workbook/quick-tour), for FastJet see [here]($fastjet$/quickstart.html)). In [examples/ExternalFastJet/Makefile]($source$/examples/ExternalFastJet/Makefile) set the paths to your Delphes, FastJet and ROOT installations (`DELPHES_DIR`, `FASTJET_DIR` and `ROOT_DIR`), and simply type in a shell:

```sh
cd examples/ExternalFastJet
make
```

and go to the [Run](#run) section.

Alternatively, here are the instructions necessary for building the examples manually:

Set the paths to your Delphes, FastJet and ROOT installations (`DELPHES_DIR`, `FASTJET_DIR` and `ROOT_DIR`):

```sh
DELPHES_DIR=<path to Delphes installation>  # main Delphes directory
FASTJET_DIR=<path to FastJet installation>  # by default should be xyz/fastjet-install
ROOT_DIR=<path to ROOT installation>
```

Then run the following commands to build the executable:

```sh
DELPHES_LIB="-Wl,-rpath,$DELPHES_DIR -L$DELPHES_DIR -lDelphesNoFastJet"

FASTJET_INC=`$FASTJET_DIR/bin/fastjet-config --cxxflags`
FASTJET_LIB=`$FASTJET_DIR/bin/fastjet-config --libs`

ROOT_INC=`$ROOT_DIR/bin/root-config --incdir`
ROOT_LIB=`$ROOT_DIR/bin/root-config --libs`

CXXFLAGS="$FASTJET_INC -I$ROOT_INC -I$DELPHES_DIR -I$DELPHES_DIR/external"
LDFLAGS="$FASTJET_LIB $ROOT_LIB -lEG $DELPHES_LIB"
```

The `libDelphesNoFastJet.so` library is automatically created when compiling Delphes the first time. This avoids conflict between your FastJet installation and the one in Delphes.

If you have a [FastJet Contrib](https://fastjet.hepforge.org/contrib/) installation, assuming you installed it in the `CONTRIB_DIR` directory (by default FastJet contrib will be installed in the FastJet directory, in that case you can replace in what follows `CONTRIB_DIR` with `FASTJET_DIR`), you have to define:

```sh
CONTRIB_DIR=<path to contrib installation>
CONTRIB_INC=$CONTRIB_DIR/include
CONTRIB_LIB="-Wl,-rpath,$CONTRIB_DIR -L$CONTRIB_DIR -lNsubjettiness -lSoftKiller"
```

and add `CONTRIB_INC` and `CONTRIB_LIB` into `CXXFLAGS` and `LDFLAGS`:

```sh
CXXFLAGS="$FASTJET_INC -I$CONTRIB_INC -I$ROOT_INC -I$DELPHES_DIR -I$DELPHES_DIR/external"
LDFLAGS="$FASTJET_LIB $CONTRIB_LIB $ROOT_LIB -lEG $DELPHES_LIB"
```

then compile:

```sh
g++ $CXXFLAGS examples/ExternalFastJet/ExternalFastJetBasic.cpp $LDFLAGS -o ExternalFastJetBasic
g++ $CXXFLAGS examples/ExternalFastJet/ExternalFastJetHepMC.cpp $LDFLAGS -o ExternalFastJetHepMC
```

## Run

If you need a test HepMC event file, you can take it from:

```sh
curl -O https://cp3.irmp.ucl.ac.be/~demin/test.hepmc.gz
gunzip test.hepmc.gz
```

Then run one of the two examples `ExternalFastJetBasic` or `ExternalFastJetHepMC` (for `ExternalFastJetHepMC` you need an event file in HepMC format as input):

```sh
./ExternalFastJetBasic ../../cards/delphes_card_CMS_NoFastJet.tcl
./ExternalFastJetHepMC ../../cards/delphes_card_CMS_NoFastJet.tcl test.hepmc
```
