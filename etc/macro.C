/*
plots mass and tau21 from two Delphes event files
*/

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "external/ExRootAnalysis/ExRootResult.h"
#else
class ExRootTreeReader;
class ExRootResult;
#endif


template<typename T>
void CollectionFilter(const TClonesArray& inColl ,vector<T*>& outColl, Double_t ptMin=30, Double_t etaMax=2.5)
{

  const TObject *object;

  for (Int_t i = 0; i < inColl.GetEntriesFast(); i++)
  {

    object = inColl.At(i);
    const T *t = static_cast<const T*>(object);

    if(t->P4().Pt() < ptMin) continue;
    if(TMath::Abs(t->P4().Eta()) > etaMax) continue;

    outColl.push_back(t);

  }
}


//------------------------------------------------------------------------------

void macro(const char *inputFile1, const char *inputFile2)
{
  gSystem->Load("libDelphes");

  TString inputFile[2];
  inputFile[0] = TString(inputFile1);
  inputFile[1] = TString(inputFile2);

  TH1F *hMass[2];
  TH1F *hTau21[2];


  for (Int_t i = 0; i < 2; i++)
  {

    // Create chain of root trees
    TChain chain("Delphes");
    chain.Add(inputFile[i]);

    // Create object of class ExRootTreeReader
    ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
    Long64_t numberOfEntries = treeReader->GetEntries();

    // Get pointers to branches used in this analysis
    TClonesArray *branchJet = treeReader->UseBranch("Jet");
    TClonesArray *branchElectron = treeReader->UseBranch("Electron");
    TClonesArray *branchMuon     = treeReader->UseBranch("Muon");

    hMass[i] = new TH1F("mass", "", 25, 0.0, 500.0);
    hTau21[i] = new TH1F("tau21", "", 25, 0.0, 1.0);

    // Define variables
    const Jet *jet;

    vector<const Electron*>   *electrons = new vector<const Electron*>();
    vector<const Muon*>       *muons     = new vector<const Muon*>();
    vector<const Jet*>        *jets      = new vector<const Jet*>();

    Double_t mass, tau21;

    // Loop over all events
    for(Int_t entry = 0; entry < numberOfEntries; ++entry)
    {
      // Load selected branches with data from specified event
      treeReader->ReadEntry(entry);

      electrons -> clear();
      muons     -> clear();
      jets      -> clear();

      // Select leptons with pT > 10 GeV and |eta| < 2.5
      CollectionFilter(*branchElectron, *electrons , 20.0 , 2.5);
      CollectionFilter(*branchMuon    , *muons     , 20.0 , 2.5);

      // Select jet with pT > 400 GeV and |eta| < 2.5
      CollectionFilter(*branchJet    , *jets     , 300.0 , 2.5);

      // Select event with 0 or 1 leptons at most
      if(electrons->size() + muons->size() != 0) continue;

      // Select event with at least 1 hard jet
      if(jets->size() == 0) continue;

      jet = jets->at(0);

      // Define electron pair invariant mass
      mass   = jet->Mass;
      tau21  = jet->Tau[0] > 0 ? jet->Tau[1]/jet->Tau[0] : -999;

      // Fill the above quantities in histograms
      hMass[i]  -> Fill(mass, 1/double(numberOfEntries));
      if(tau21 > 0) hTau21[i] -> Fill(tau21, 1/double(numberOfEntries));

    } // end of event loop*/
  }

  // Plot all the above observables

  TCanvas *c1 = new TCanvas("c1","multipads",1200,600);
  gStyle->SetOptStat(0);
  c1->Divide(2,1);

  c1->cd(1);

  hMass[0] -> SetLineWidth(3);
  hMass[0] -> SetLineColor(kBlue);

  hMass[0] -> GetXaxis()->SetTitle("m [GeV]");

  hMass[1] -> SetLineWidth(3);
  hMass[1] -> SetLineColor(kRed);

  hMass[0] -> Draw("hist");
  hMass[1] -> Draw("hist same");

  hMass[0] -> SetMaximum(0.50);

  TLegend *leg1 = new TLegend(0.32,0.65,0.70,0.85);

  leg1->AddEntry(hMass[0], "light jet", "l");
  leg1->AddEntry(hMass[1], "w jet", "l");

  leg1->SetBorderSize(0);
  leg1->SetShadowColor(0);
  leg1->SetFillColor(0);
  leg1->Draw();

  c1->cd(2);

  hTau21[0] -> SetLineWidth(3);
  hTau21[0] -> SetLineColor(kBlue);

  hTau21[0] -> GetXaxis()->SetTitle("#tau_{2,1}");

  hTau21[1] -> SetLineWidth(3);
  hTau21[1] -> SetLineColor(kRed);

  hTau21[0] -> Draw("hist");
  hTau21[1] -> Draw("hist same");

  hTau21[0] -> SetMaximum(0.2);

  TLegend *leg2 = new TLegend(0.55,0.65,0.89,0.85);

  leg2->AddEntry(hTau21[0], "light jet", "l");
  leg2->AddEntry(hTau21[1], "w jet", "l");

  leg2->SetBorderSize(0);
  leg2->SetShadowColor(0);
  leg2->SetFillColor(0);
  leg2->Draw();

  TString fname(inputFile2);
  fname.ReplaceAll("root", "png");

  c1->Print(fname,"png");

}
