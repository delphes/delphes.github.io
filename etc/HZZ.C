/*
Prints complete input particle arborescence for the first 100 events. Useful for debugging purposes.
root -l examples/Example5.C'("delphes_output.root")'
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

void HZZ(const char *inputFile)
{
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon     = treeReader->UseBranch("Muon");

  // Book histograms
  TH1F *histMinMass = new TH1F("mass_min", "", 50, 00.0, 140.0);
  TH1F *histMaxMass = new TH1F("mass_max", "", 50, 00.0, 140.0);
  TH1F *histMass = new TH1F("mass", "", 50, 100, 150);

  TH1F *histMinMassGen = new TH1F("mass_min_gen", "", 50, 0.0, 140.0);
  TH1F *histMaxMassGen = new TH1F("mass_max_gen", "", 50, 00.0, 140.0);
  TH1F *histMassGen = new TH1F("mass_gen", "", 50, 100, 150);

  // Define variables
  const Electron *elec1, *elec2;
  const Muon     *muon1, *muon2;

  const GenParticle *gen_elec1, *gen_elec2;
  const GenParticle *gen_muon1, *gen_muon2;

  vector<const Electron*>   *electrons = new vector<const Electron*>();;
  vector<const Muon*>           *muons = new vector<const Muon*>();;

  Double_t massMin, massMax, mass, massEE, massMM;
  Double_t gen_massMin, gen_massMax, gen_mass, gen_massEE, gen_massMM;

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    electrons -> clear();
    muons     -> clear();

    // Select leptons with pT > 10 GeV and |eta| < 2.5
    CollectionFilter(*branchElectron, *electrons , 10.0 , 2.5);
    CollectionFilter(*branchMuon    , *muons     , 10.0 , 2.5);

    // Select event with at least 2 electrons and 2 muons
    if(electrons->size() < 2) continue;
    if(muons->size() < 2)     continue;

    // Define leading and subleading leptons
    elec1 = electrons->at(0);
    elec2 = electrons->at(1);
    muon1 = muons->at(0);
    muon2 = muons->at(1);

    // Define leading and subleading leptons at gen level
    gen_elec1 = (GenParticle*) elec1->Particle.GetObject();
    gen_elec2 = (GenParticle*) elec2->Particle.GetObject();
    gen_muon1 = (GenParticle*) muon1->Particle.GetObject();
    gen_muon2 = (GenParticle*) muon2->Particle.GetObject();

    // Delect events with opposite charge leptons
    if(elec1->Charge == elec2->Charge) continue;
    if(muon1->Charge == muon2->Charge) continue;

    // Define electron pair invariant mass
    massEE = ((elec1->P4()) + (elec2->P4())).M();
    gen_massEE = ((gen_elec1->P4()) + (gen_elec2->P4())).M();

    // Define muon pair invariant mass
    massMM = ((muon1->P4()) + (muon2->P4())).M();
    gen_massMM = ((gen_muon1->P4()) + (gen_muon2->P4())).M();

    // Define the four leptons invariant mass
    mass   = ((elec1->P4()) + (elec2->P4()) + (muon1->P4()) + (muon2->P4())).M();
    gen_mass   = ((gen_elec1->P4()) + (gen_elec2->P4()) + (gen_muon1->P4()) + (gen_muon2->P4())).M();

    // Define the minimum invariant mass between m_ee and m_mumu
    massMin = min( massEE, massMM );
    gen_massMin = min( gen_massEE, gen_massMM );

    // Define the maximum invariant mass between m_ee and m_mumu
    massMax = max( massEE, massMM );
    gen_massMax = max( gen_massEE, gen_massMM );


    // Fill the above quantities in histograms
    histMinMass -> Fill(massMin);
    histMaxMass -> Fill(massMax);
    histMass    -> Fill(mass);

    histMinMassGen -> Fill(gen_massMin);
    histMaxMassGen -> Fill(gen_massMax);
    histMassGen    -> Fill(gen_mass);


  } // end of event loop

  // Plot all the above observables

  TCanvas *c1 = new TCanvas("c1","multipads",1200,600);
  gStyle->SetOptStat(0);
  c1->Divide(2,1);

  c1->cd(1);

  histMaxMassGen -> SetLineWidth(2);
  histMaxMassGen -> SetLineColor(kBlue);
  histMaxMassGen -> SetLineStyle(2);

  histMaxMassGen -> GetXaxis()->SetTitle("m(l^{+}l^{-}) [GeV]");

  histMaxMass -> SetLineWidth(2);
  histMaxMass -> SetLineColor(kBlue);

  histMinMassGen -> SetLineWidth(2);
  histMinMassGen -> SetLineColor(kRed);
  histMinMassGen -> SetLineStyle(2);

  histMinMass -> SetLineWidth(2);
  histMinMass -> SetLineColor(kRed);

  histMaxMassGen -> Draw("hist");
  histMaxMass    -> Draw("hist same");
  histMinMassGen -> Draw("hist same");
  histMinMass -> Draw("hist same");

  TLegend *leg1 = new TLegend(0.32,0.65,0.70,0.85);

  leg1->AddEntry(histMaxMass, "max( m(e_{1}, e_{2}) , m(#mu_{1}, #mu_{2}) ) (reco)", "l");
  leg1->AddEntry(histMaxMassGen, "max( m(e_{1}, e_{2}) , m(#mu_{1}, #mu_{2}) ) (gen)", "l");
  leg1->AddEntry(histMinMass, "min( m(e_{1}, e_{2}) , m(#mu_{1}, #mu_{2}) ) (reco)", "l");
  leg1->AddEntry(histMinMassGen, "min( m(e_{1}, e_{2}) , m(#mu_{1}, #mu_{2}) ) (gen)", "l");

  leg1->SetBorderSize(0);
  leg1->SetShadowColor(0);
  leg1->SetFillColor(0);
  leg1->Draw();

  c1->cd(2);

  histMassGen -> SetLineWidth(2);
  histMassGen -> SetLineStyle(2);

  histMassGen -> GetXaxis()->SetTitle("m(e^{+}e^{-}#mu^{+}#mu^{-}) [GeV]");

  histMass -> SetLineWidth(2);

  histMassGen -> Draw("hist");
  histMass    -> Draw("hist same");

  TLegend *leg2 = new TLegend(0.55,0.65,0.89,0.85);

  leg2->AddEntry(histMass, "m(e^{+}e^{-}#mu^{+}#mu^{-}) (reco)", "l");
  leg2->AddEntry(histMassGen, "m(e^{+}e^{-}#mu^{+}#mu^{-}) (gen)", "l");

  leg2->SetBorderSize(0);
  leg2->SetShadowColor(0);
  leg2->SetFillColor(0);
  leg2->Draw();

  TString fname(inputFile);
  fname.ReplaceAll("root", "png");

  c1->Print(fname,"png");

}
