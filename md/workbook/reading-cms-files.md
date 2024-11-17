# Reading CMS Files

## Generator Events in CMS ROOT Files

It is possible to run Delphes on the generator events stored in CMS ROOT files (FEVT, RECO, AOD).

More details on the generator event format can be found at

<https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookGenParticleCandidate>

## Setting up CMSSW Computing Environment

The instructions on how to setup CMSSW work area and runtime environment can be found at

<https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookSetComputerNode>

## Building Delphes and DelphesCMSFWLite

Commands to download and build Delphes:

```sh
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

wget http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.5.0.tar.gz
tar -zxf Delphes-3.5.0.tar.gz

cd Delphes-3.5.0
make -j 4
```

## Running DelphesCMSFWLite

When running `DelphesCMSFWLite` without parameters or when supplying an invalid command line, the following message will be shown:

```sh
./DelphesCMSFWLite
 Usage: DelphesCMSFWLite config_file output_file input_file(s)
 config_file - configuration file in Tcl format,
 output_file - output file in ROOT format,
 input_file(s) - input file(s) in ROOT format.
```

Running Delphes with CMS ROOT input files:

```sh
./DelphesCMSFWLite cards/delphes_card_CMS.tcl delphes_output.root input.root
```
