# Module System

Delphes module system is inspired by the [Folders and Tasks chapter](https://root.cern.ch/root/htmldoc/guides/users-guide/ROOTUsersGuide.html#folders-and-tasks) from the ROOT Users Guide and it's based on the [TTask](http://root.cern.ch/root/html/TTask.html) and [TFolder](http://root.cern.ch/root/html/TFolder.html) classes.

All Delphes modules consume and produce [TObjArrays](http://root.cern.ch/root/html/TObjArray.html) of [Candidates](/workbook/candidate).

Every Delphes module has a corresponding `TFolder` that is used to store `TObjArrays` produced by this module. Any Delphes module can access `TObjArrays` produced by other Delphes modules using `ImportArray("ModuleInstanceName/arrayName")` method.

The contents of all Delphes `TFolders` and `TObjArrays` is browsable. All the modules are accessible from the `"/Delphes/Delphes"` folder and all the `TObjArrays` are accessible from the `"/Delphes/Export"` folder.

![](/img/delphes_folders.png)

Additional classes `ExRootTask` and `DelphesModule` has been developed to provide frequently used services for Delphes. All Delphes modules inherit from `DelphesModule`.

Here is an example of a module declaration:

```
#ifndef ExampleModule_h
#define ExampleModule_h

#include "classes/DelphesModule.h"

#include <deque>

class TObjArray;
class DelphesFormula;

class ExampleModule: public DelphesModule
{
public:

  ExampleModule();
  ~ExampleModule();

  void Init();
  void Process();
  void Finish();

private:

  Int_t fIntParam;
  Double_t fDoubleParam;

  std::deque <Double_t> fArrayParam;

  DelphesFormula *fFormula; //!

  TIterator *fItInputArray; //!

  const TObjArray *fInputArray; //!

  TObjArray *fOutputArray; //!

  ClassDef(ExampleModule, 1)
};

#endif
```

and here is its implementation:

```
#include "modules/ExampleModule.h"

#include "classes/DelphesClasses.h"
#include "classes/DelphesFactory.h"
#include "classes/DelphesFormula.h"

#include "ExRootAnalysis/ExRootResult.h"
#include "ExRootAnalysis/ExRootFilter.h"
#include "ExRootAnalysis/ExRootClassifier.h"

#include "TMath.h"
#include "TString.h"
#include "TFormula.h"
#include "TRandom3.h"
#include "TObjArray.h"
#include "TDatabasePDG.h"
#include "TLorentzVector.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

//------------------------------------------------------------------------------

ExampleModule::ExampleModule() :
  fFormula(0), fItInputArray(0)
{
  fFormula = new DelphesFormula;
}

//------------------------------------------------------------------------------

ExampleModule::~ExampleModule()
{
  if(fFormula) delete fFormula;
}

//------------------------------------------------------------------------------

void ExampleModule::Init()
{
  fIntParam = GetInt("IntParam", 10);

  fDoubleParam = GetDouble("DoubleParam", 1.0);

  fFormula->Compile(GetString("EfficiencyFormula", "0.4"));

  ExRootConfParam param = GetParam("ArrayParam");
  Long_t i, size;
  fArrayParam.clear();

  size = param.GetSize();
  for(i = 0; i < size; ++i)
  {
    fArrayParam.push_back(param[i].GetDouble());
  }

  // import input array(s)

  fInputArray = ImportArray(GetString("InputArray", "FastJetFinder/jets"));
  fItInputArray = fInputArray->MakeIterator();

  // create output array(s)

  fOutputArray = ExportArray(GetString("OutputArray", "jets"));

}

//------------------------------------------------------------------------------

void ExampleModule::Finish()
{
  if(fItInputArray) delete fItInputArray;
}

//------------------------------------------------------------------------------

void ExampleModule::Process()
{
  Candidate *candidate;
  TLorentzVector candidatePosition, candidateMomentum;

  // loop over all input candidates
  fItInputArray->Reset();
  while((candidate = static_cast<Candidate*>(fItInputArray->Next())))
  {
    candidatePosition = candidate->Position;
    candidateMomentum = candidate->Momentum;

    // apply an efficiency formula
    if(gRandom->Uniform() <= fFormula->Eval(candidateMomentum.Pt(), candidatePosition.Eta()))
    {
      fOutputArray->Add(candidate);
    }
  }
}
```
