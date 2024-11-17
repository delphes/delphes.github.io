# Using DelphesAnalysis to write analysis code in Python

## Introduction

Delphes comes with all the ExRootAnalysis framework/facilities. It is powerful and very practical. Written in C++, it has all the nice (fast) and bad (heavy) aspects of that language. On the contrary, Python is an interpreted scripting language that allows for a fast development cycle. It is therefore (becoming) the preferred language for high-level applications.

- Introspection makes the code easy to extend
- Run-time type evaluation removes the need for templates

DelphesAnalysis is an analysis framework written in Python where a clear separation is maintained between the standard code and what the user has to implement. This makes it easy to apprehend and generic, still retaining full flexibility and scalability. The framework is built out of:

- `AnalysisEvent` class: interface to the ROOT tree + many more
- Base `ControlPlots` class: interface to create plots
- Base `EventSelection` class: interface to code cuts/categories

All that can be configured in a single configuration file.

## The AnalysisEvent class

AnalysisEvent is an interface to the tree data. It provides new functionality w.r.t. the bare access:

- **A list of event products used in the analysis**\
  It allows to centralize the definition of the collections to use, and provides convenient aliases that you can use in your analysis to access the various objects/products.

- **A list of "producers" of analysis high-level quantities**\
  This is sometimes known as "Analysis on demand". You don't have to explicitly call the analysis routines that were previously declared. Once registered, they are run when needed. Results are cached, so that the methods are called once per event. That functionality reduces a lot the number of import statements and contributes to the optimization of the analysis code.

- **A centralized weight infrastructure**\
  The user can define a set of weight classes where an event weight is computed based on event quantities. AnalysisEvent keeps track of every weight and caches the intermediate and final values. Beware that the caching mechanism for weights is based on the arguments passed to them... don't use object quantities that may change.

- **A volatile dictionary to cache temporarily reconstructed products**\
  Any high-level quantity can be "put in the event" and retrieved when needed. This means that if your analysis is split into modules, there is no need to pass many arguments to the various functions. Just pass the event instance and use the event to store what is needed.

```
class AnalysisEvent(ROOT.TChain)
  |
  |  __init__(self, inputFiles='', maxEvents=0)
  |      Initialize the AnalysisEvent like a standard Event, plus additional features.
  |
  |  addCollection(self, name, inputTag)
  |      Register an event collection as used by the analysis.
  |      Example: addCollection("myjets","jets")
  |      Note that the direct access to the branch is still possible but unsafe.
  |
  |  removeCollection(self, name)
  |      Forget about the named event collection.
  |      This method will delete both the product from the cache (if any) and the definition.
  |      To simply clear the cache, use "del event.name" instead.
  |
  |  getCollection(self, name)
  |      Retrieve the event product or return the cached collection.
  |      Note that the prefered way to get the collection is instead to access the "event.name" attribute.
  |
  |  addProducer(self, name, producer, **kwargs)
  |      Register a producer to create new high-level analysis objects.
  |
  |  removeProducer(self, name)
  |      Forget about the producer.
  |      This method will delete both the product from the cache (if any) and the producer.
  |      To simply clear the cache, use "del event.name" instead.
  |
  |  addWeight(self, name, weightClass)
  |      Declare a new class (engine) to compute the weights.
  |      weightClass must have a weight() method returning a float.
  |
  |  delWeight(self, name)
  |      Remove one weight engine from the internal list.
  |
  |  weight(self, weightList=None, **kwargs)
  |      Return the event weight. Arguments:
  |       * weightList is the list of engines to use, as a list of strings.
  |            Default: all defined engines.
  |       * the other named arguments are forwarded to the engines.
  |      The output is the product of the selected individual weights.
  |
  |  event(self)
  |      Event number
  |
  |  to(self, event)
  |      Jump to some event
  |
  |  (...)
```

## The BaseControlPlots class and its subclasses

That class allows to define/fill/save a set of histograms or ntuple variables, following the traditional scheme in such cases. Still, it makes use of a simplified and unified approach to minimize the amount of code needed while maintaining all the functionality of the ROOT back-end.

As a user, you must create a derived class where the following two methods are implemented:

`beginJob(self)`
: That method is called before the event loop. You should declare the histograms, using `self.add(/*TH1 arguments*/)`, and do any needed initialization.

`process(self, event)`
: That method is called for each event. A proper implement should do the processing, taking all information from the input event. Remember to take benefit from the caching, producers, and other features of AnalysisEvent. The method must return a dictionary varName:value(s) that will be used internally by the framework to fill histograms or ntuple variables. It can be a list of values when more than one entry per event, but this is then only supported for histograms, not for ntuples (the corresponding ntuple branches will be empty).

```
class BaseControlPlots
  |
  |  __init__(self, dir=None, purpose='generic', dataset=None, mode='plots')
  |      Initialize the ControlPlots, creating output file if needed. If no file is given, it means it is delegated.
  |
  |  add(self, *args)
  |      Add one item to the list of products. Arguments are as for TH1F.
  |
  |  beginJob(self)
  |      Declare histograms, and for derived classes instantiate handles. Must be overloaded.
  |
  |  defineCategories(self, categories)
  |      Define the categories, given a list of names. Only works for datasets
  |
  |  endJob(self)
  |      Save and close.
  |
  |  fill(self, data, weight=1.0)
  |      Fills whatever must be filled in
  |
  |  process(self, event)
  |      Process event data to extract histogrammables. Must be overloaded.
  |
  |  processEvent(self, event, weight=1.0)
  |      process event and fill histograms
  |
  |  setCategories(self, categories)
  |      Set the categories, given a list of booleans. Only works for datasets
  |
  |  (...)
```

## The BaseWeight class

That class has to be subclassed to compute event weights. The base class itself does nothing... it is mostly there as a documentation of what you have to implement in a subclass. Namely,

the constructor
: A simple constructor should be implemented, with any needed parameters to initialize the calculation.

`weight(self, event)`
: Method returning the weight value for the current event. The implementation should be based on the event content and on a set of options passed as argument. Beware that the caching mechanism for weights is based on the arguments passed to them... don't use quantities that may change during the event processing.

```
class BaseWeightClass
  |
  |  weight(self, event)
  |      Lepton eff weight
```

## The Event selection

The EventSelection module contains the set of functions needed to select and classify events. A proper implementation of the event selection will at least define the following:

`categoryNames`
: an ordered list of the names of each category.

`eventCategory(event)`
: a method that computes a tuple containing the data needed to sort events in the categories named above in its simplest form. It can be a tuple of bools, or may contain more detailed information but should always be kept simple to make the isInCategory method fast.

`isInCategory(cat, categoryData)`
: that method returns a boolean to tell if the event is in the category cat, definition, from category data contained in categoryData.

```
FUNCTIONS
    eventCategory(event)
        Check analysis requirements for various steps
        and return a tuple of data used to decide
        to what category an event belong

    isInCategory(category, categoryData)
        Check if the event enters category X, given the tuple computed by eventCategory.

DATA
    categoryNames = [ ]
```

## Steering code and Configuration file

The framework is contained in `python/DelphesAnalsys`. No file in that directory should ever be modified.

The main script is `ControlPlots`. This is a single code to generate a full set of histograms for your analysis, organized in logical groups by ControlPlot class and by category. The same code will generate a ntuple if the proper parameter is changed in the configuration file. Internally, `ControlPlots` steers the user-defined codes: event selection and control plots.

`DumpEventInfo` is another script that will output all the information available on a given event.

All that is configured through a simple configuration script. The script used is defined via the `DelphesAnalysisCfg` environment variable, or optionally via the command line in the case of `ControlPlots`. The configuration file is where the control plot class and event selection module are declared and where the event collections, producers and weights are set.

```python
# configuration of the ControlPlot machinery

from collections import namedtuple

controlPlot     = namedtuple("controlPlot",    ["label","module","classname","kwargs"])
eventCollection = namedtuple("eventCollection",["label","collection"])
eventProducer   = namedtuple("eventProducer",  ["label","module","function","kwargs"])
eventWeight     = namedtuple("eventWeight",    ["label","module","classname","kwargs"])

class configuration:
  # default I/O
  defaultFilename = "controlPlots"
  RDSname = "rds_delphes"
  WSname = "workspace_ras"

  # mode: plots or dataset
  runningMode = "plots"

  # event selection class
  eventSelection = ""

  # control plot classes
  controlPlots = [ ]

  # event content: lists of eventCollection, eventProducer, and eventWeight objects respectively.
  eventCollections = [ ]
  eventProducers   = [ ]
  eventWeights     = [ ]

class eventDumpConfig:
  # fine-tuning of the event content for display
  productsToPrint   = [ ] # list of product to display (use the producer label)
  collectionsToHide = [ ] # collections used in the analysis but not printed (use the collection label)

# import the actual implementation of the configuration
import os

theConfig = os.getenv("DelphesAnalysisCfg")
if theConfig is not None:
  configImplementation = __import__(os.path.splitext(theConfig)[0])
  configuration = configImplementation.configuration
  eventDumpConfig = configImplementation.eventDumpConfig
```

## Implementing an analysis

In order to implement an analysis, one should

- implement the specific control plot class(es), with the plots that you want to see.
- implement an event selection module, with the cuts that should be applied.
- declare everything in the configuration file (name given as argument of `ControlPlots` or set as `DelphesAnalysisCfg` environment variable).

The release includes two examples.

- Simple analysis.
  - `simpleConfig.py`
  - `SimpleEventSelection.py`
  - `LeptonControlPlots.py`
- Basic ttbar analysis
  - `topConfig.py`
  - `TtbarEventSelection.py`
  - `TopReconstruction.py`
  - `JetControlPlots.py`
  - `LeptonControlPlots.py`
  - `TopControlPlots.py`

The following commands can be run from the Delphes directory:

```sh
# setup path
. DelphesEnv.sh
cd python

# run the analysis
python3 DelphesAnalysis/ControlPlots.py -i ../files/ -o controlPlots_demo.root --all -c topConfig.py

# dump a list of events in category 5 (ttbar candidates)
export DelphesAnalysisCfg="topConfig.py"
python3 DelphesAnalysis/DumpEventList.py 5 ../delphes_output.root

# for each of them, print details
for i in `cat eventlist.txt | cut -d' ' -f 2`; { python3 DelphesAnalysis/DumpEventInfo.py $i ../delphes_output.root; }
```
