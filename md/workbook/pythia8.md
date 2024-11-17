# Running Delphes with Pythia8

If you already generated Les Houches event files, and you want to hadronize them, instead of producing large intermediary files by running Pythia8 standalone, you can now run Pythia8 inside Delphes. If you did not generate hard scattering events, you can generate them directly via Pythia8 inside Delphes.

First, you'll need a working [Pythia8](https://pythia.org) installation.

```
wget https://pythia.org/download/pythia82/pythia8235.tgz
tar xzvf pythia8235.tgz
cd pythia8235
./configure --prefix=path_to_PYTHIA8_installation
make install
```

Second, define an environment variable for the path to your PYTHIA installation directory

```
export PYTHIA8=path_to_PYTHIA8_installation
```

and you can then build the `DelphesPythia8` executable with the following command:

```
make HAS_PYTHIA8=true
```

You can run a simple example for generating QCD Pythia8 events within Delphes:

```
./DelphesPythia8 cards/delphes_card_CMS.tcl examples/Pythia8/configNoLHE.cmnd delphes_nolhe.root
```

For instance, if you want to generate a MinBias file to be used for pile-up merging, you'll need to replace the output collection in the converter card:

```
...
module TreeWriter TreeWriter {
# add Branch InputArray BranchName BranchClass
# add Branch Delphes/allParticles Particle GenParticle
  add Branch Delphes/stableParticles Particle GenParticle
}
...
```

and then run:

```
./DelphesPythia8 cards/converter_card.tcl examples/Pythia8/generatePileUp.cmnd MinBias.root
```

If you have your own Les Houches file (the path for the LHE is defined inside the \*.cmnd file):

```
./DelphesPythia8 cards/delphes_card_CMS.tcl examples/Pythia8/configLHE.cmnd delphes_lhe.root
```
