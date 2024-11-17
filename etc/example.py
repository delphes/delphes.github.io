#!/usr/bin/env python3
# example event loop macro

import sys
import ROOT

if len(sys.argv) < 2:
    print(" Usage: python macro.py data.root hist_data.root")
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
branchMissingET = treeReader.UseBranch("MissingET")
branchElectron = treeReader.UseBranch("Electron")

# Book histograms
histMuonMultiplicity = ROOT.TH1F(
    "histMuonMultiplicity", "histMuonMultiplicity", 5, -0.5, 4.5
)
histLeadingMuonPt = ROOT.TH1F("histLeadingMuonPt", "histLeadingMuonPt", 50, 0.0, 100.0)
histMissingET = ROOT.TH1F("histMissingET", "histMissingET", 50, 0.0, 100.0)

# Loop over all events
for entry in range(0, numberOfEntries):
    # Load selected branches with data from specified event
    treeReader.ReadEntry(entry)

    # loop over lepton collections
    # store in an array only isolated muons above some pT
    selected_muons = []
    for muon in branchMuon:
        if muon.PT < 15.0 or abs(muon.Eta) > 4.0 or muon.IsolationVar > 0.25:
            continue
        selected_muons.append(muon)

    selected_electrons = []
    for elec in branchElectron:
        if elec.PT < 15.0 or abs(elec.Eta) > 4.0 or elec.IsolationVar > 0.12:
            continue
        selected_electrons.append(elec)

    histMuonMultiplicity.Fill(len(selected_muons))

    if len(selected_muons) > 0:
        histLeadingMuonPt.Fill(selected_muons[0].P4().Pt())

    # fill missing tranvserse energy

    met = branchMissingET[0].MET
    histMissingET.Fill(met)


out_root = ROOT.TFile(outputFile, "RECREATE")

histMuonMultiplicity.Write()
histLeadingMuonPt.Write()
histMissingET.Write()
