# Library Interface

## Introduction

Delphes can be used as a library and be included in a third party application. To do so, download and compile Delphes as explained in the [Quick Tour](/workbook/quick-tour).

This creates among other files the `libDelphes.so` library that can be dynamically linked to any C++ binary. Header files are located in the modules and classes subdirectories:

- `modules/Delphes.h`
- `classes/DelphesClasses.h`
- `classes/DelphesFactory.h`

## Simplified example

The code below shows the basic ingredients to build a standalone application using Delphes. In that template, the `ReadEvent`, `ReadParticle`, `ConvertInput` and `ConvertOutput` functions should be implemented by the user.

```c++
#include <stdexcept>
#include <iostream>

#include "TROOT.h"
#include "TApplication.h"

#include "TObjArray.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TLorentzVector.h"

#include "modules/Delphes.h"
#include "classes/DelphesClasses.h"
#include "classes/DelphesFactory.h"

using namespace std;

void ConvertInput(DelphesFactory *factory, TObjArray *allParticleOutputArray,
  TObjArray *stableParticleOutputArray, TObjArray *partonOutputArray);

void ConvertOutput(Delphes *modularDelphes);

bool ReadEvent() { return true; }

bool ReadParticle() { return true; }

int main()
{
  // Declaration of variables
  ExRootConfReader *confReader;
  Delphes *modularDelphes;
  DelphesFactory *factory;
  TObjArray *allParticleOutputArray;
  TObjArray *stableParticleOutputArray;
  TObjArray *partonOutputArray;

  gROOT->SetBatch();

  int appargc = 1;
  char appName[] = "DelphesExample";
  char *appargv[] = {appName};
  TApplication app(appName, &appargc, appargv);

  try
  {
    // Initialization
    confReader = new ExRootConfReader;
    confReader->ReadFile("cards/delphes_card_CMS.tcl");

    modularDelphes = new Delphes("Delphes");
    modularDelphes->SetConfReader(confReader);

    factory = modularDelphes->GetFactory();

    allParticleOutputArray = modularDelphes->ExportArray("allParticles");
    stableParticleOutputArray = modularDelphes->ExportArray("stableParticles");
    partonOutputArray = modularDelphes->ExportArray("partons");

    modularDelphes->InitTask();

    // Event loop
    while(ReadEvent())
    {
      modularDelphes->Clear();
      ConvertInput(factory, allParticleOutputArray,
        stableParticleOutputArray, partonOutputArray);
      modularDelphes->ProcessTask();
      ConvertOutput(modularDelphes);
    }

    // Finalization
    modularDelphes->FinishTask();
    delete modularDelphes;
    delete confReader;
    return 0;
  }
  catch(runtime_error &e)
  {
    cerr << "** ERROR: " << e.what() << endl;
    return 1;
  }
}

void ConvertInput(DelphesFactory *factory, TObjArray *allParticleOutputArray,
  TObjArray *stableParticleOutputArray, TObjArray *partonOutputArray)
{
  Candidate *candidate;
  TDatabasePDG *pdg;
  TParticlePDG *pdgParticle;
  Int_t pdgCode;

  Int_t pid, status;
  Double_t px, py, pz, e, mass;
  Double_t x, y, z, t;

  pdg = TDatabasePDG::Instance();

  while(ReadParticle())
  {
    candidate = factory->NewCandidate();

    candidate->PID = pid;
    pdgCode = TMath::Abs(candidate->PID);

    candidate->Status = status;

    pdgParticle = pdg->GetParticle(pid);
    candidate->Charge = pdgParticle ? Int_t(pdgParticle->Charge()/3.0) : -999;
    candidate->Mass = mass;

    candidate->Momentum.SetPxPyPzE(px, py, pz, e);

    candidate->Position.SetXYZT(x, y, z, t);

    allParticleOutputArray->Add(candidate);

    if(!pdgParticle) return;

    if(status == 1)
    {
      stableParticleOutputArray->Add(candidate);
    }
    else if(pdgCode <= 5 || pdgCode == 21 || pdgCode == 15)
    {
      partonOutputArray->Add(candidate);
    }
  }
}

void ConvertOutput(Delphes *modularDelphes)
{
  const TObjArray *arrayJets = modularDelphes->ImportArray("FastJetFinder/jets");
  TIter iteratorJets(arrayJets);
  Candidate *candidate;

  iteratorJets.Reset();
  while((candidate = static_cast<Candidate*>(iteratorJets.Next())))
  {
    const TLorentzVector &momentum = candidate->Momentum;
  }
}
```

## Complete example

A fully functional application using the Delphes library can be found in [readers/DelphesSTDHEP.cpp]($source$/readers/DelphesSTDHEP.cpp).
