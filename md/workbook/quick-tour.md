# Quick Tour

## Installing Delphes from Source

To successfully build Delphes the following prerequisite packages should be installed:

- [ROOT Data Analysis Framework](https://root.cern/install)
- [Tcl scripting language](https://www.tcl.tk)

Then configure your environment for ROOT and GCC. If you are on lxplus, you can do it this way:

```sh
source /cvmfs/sft.cern.ch/lcg/views/LCG_105/x86_64-el9-gcc12-opt/setup.sh
```

Finally, download and build Delphes:

```sh
wget http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.5.0.tar.gz
tar -zxf Delphes-3.5.0.tar.gz

cd Delphes-3.5.0
make -j 4
```

Or, to install with CMake

```sh
cd Delphes-3.5.0
mkdir build
cd build

cmake -DCMAKE_INSTALL_PREFIX=../install ..
make -j 4 install
```

## Running Delphes

When running Delphes without parameters or when supplying an invalid command line, the following message will be shown:

```sh
./DelphesHepMC3
 Usage: DelphesHepMC3 config_file output_file [input_file(s)]
 config_file - configuration file in Tcl format,
 output_file - output file in ROOT format,
 input_file(s) - input file(s) in HepMC format,
 with no input_file, or when input_file is -, read standard input.
```

Running Delphes with HepMC input files:

```sh
./DelphesHepMC3 cards/delphes_card_CMS.tcl output.root input.hepmc
```

Running Delphes with STDHEP (XDR) input files:

```sh
./DelphesSTDHEP cards/delphes_card_CMS.tcl delphes_output.root input.hep
```

Running Delphes with LHEF input files:

```sh
./DelphesLHEF cards/delphes_card_CMS.tcl delphes_output.root input.lhef
```

Running Delphes with files accessible via HTTP:

```sh
curl https://cp3.irmp.ucl.ac.be/~demin/test.hepmc3.gz | gunzip | ./DelphesHepMC3 cards/delphes_card_CMS.tcl delphes_output.root
```

## Analyzing Delphes Output

Delphes output can be analyzed with the ROOT data analysis framework. This can be done in simple cases with `TTree::Draw`, or with macros for more advanced cases. Examples and mini analysis frameworks are provided in C++ (using ExRootAnalysis) and Python (using [DelphesAnalysis](/workbook/delphes-analysis)).

### Simple analysis using TTree::Draw

Start ROOT and load Delphes shared library:

```sh
root
```

```c++
gSystem->Load("libDelphes");
```

Open ROOT tree file and do some basic analysis using Draw or TBrowser:

```c++
TFile *f = TFile::Open("delphes_output.root");
f->Get("Delphes")->Draw("Electron.PT");
TBrowser browser;
```

Notes:

- `Delphes` is the tree name. It can be learned e.g. from `TBrowser`.
- `Electron` is the branch name.
- `PT` is a variable (leaf) of this branch.

Complete description of all branches can be found at [this link](/workbook/root-tree-description).

### Macro-based analysis

The [examples]($source$/examples) directory contains a basic ROOT analysis macro called [Example1.C]($source$/examples/Example1.C). This ROOT analysis macro consists of histogram booking, event loop (histogram filling), histogram display.

Here are commands to run this macro:

```sh
root
```

```c++
gSystem->Load("libDelphes");
.X examples/Example1.C("delphes_output.root");
```

And here is the full source code of this macro:

```c++
void Example1(const char *inputFile)
{
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");

  // Book histograms
  TH1 *histJetPT = new TH1F("jet_pt", "jet P_{T}", 100, 0.0, 100.0);
  TH1 *histMass = new TH1F("mass", "M_{inv}(e_{1}, e_{2})", 100, 40.0, 140.0);

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    // If event contains at least 1 jet
    if(branchJet->GetEntries() > 0)
    {
      // Take first jet
      Jet *jet = (Jet*) branchJet->At(0);

      // Plot jet transverse momentum
      histJetPT->Fill(jet->PT);

      // Print jet transverse momentum
      cout << jet->PT << endl;
    }

    Electron *elec1, *elec2;

    // If event contains at least 2 electrons
    if(branchElectron->GetEntries() > 1)
    {
      // Take first two electrons
      elec1 = (Electron *) branchElectron->At(0);
      elec2 = (Electron *) branchElectron->At(1);

      // Plot their invariant mass
      histMass->Fill(((elec1->P4()) + (elec2->P4())).M());
    }
  }

  // Show resulting histograms
  histJetPT->Draw();
  histMass->Draw();
}
```

### More advanced macro-based analysis

The [examples]($source$/examples) directory contains a ROOT macro called [Example2.C]($source$/examples/Example2.C) demonstrating how to use class `ExRootTreeReader` to access data and class `ExRootResult` to manage histograms booking and output.

This macro can be run with the following command:

```sh
root -l examples/Example2.C'("delphes_output.root")'
```

### Analysis in Python

[DelphesAnalysis](/workbook/delphes-analysis) is an analysis framework written in Python where a clear separation is maintained between the standard code and what the user has to implement. This makes it easy to apprehend and generic, still retaining full flexibility and scalability. It is configured in a single configuration file.

More details and examples on the [dedicated page](/workbook/delphes-analysis).
