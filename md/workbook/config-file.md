# Configuration File

## Introduction

The Delphes configuration file is based on [Tcl scripting language](https://www.tcl.tk/about/language.html).

[Tcl Fundamentals](http://www.beedub.com/book/3rd/Tclintro.pdf) chapter from [Practical Programming in Tcl and Tk](http://www.beedub.com/book/) describes the basic syntax rules for the Tcl scripting language.

Delphes uses a safe subset of [Tcl 8.0.5](https://www.tcl.tk/man/tcl8.0/TclCmd/contents.htm) with 2 additional commands: `module` and `add`.

## Basic Commands

Here are the most important commands:

`set ParamName value`
: this command sets the value of the parameter given by `ParamName` to `value`

`add ParamName value value value ...`
: this command treats the parameter given by `ParamName` as a list and appends each of the `value` arguments to that list as a separate element.

`module ModuleClass ModuleName ModuleConfigurationBody`
: this command activates a module of class `ModuleClass` called `ModuleName` and evaluates module's configuration commands contained in `ModuleConfigurationBody`:

```tcl
module Efficiency ElectronEfficiency {
  set InputArray ElectronEnergySmearing/electrons
  set OutputArray electrons

  # set EfficiencyFormula {efficiency formula as a function of eta and pt}

  # efficiency formula for electrons
  set EfficiencyFormula {                                      (pt <= 10.0) * (0.00) +
                                           (abs(eta) <= 1.5) * (pt > 10.0)  * (0.95) +
                         (abs(eta) > 1.5 && abs(eta) <= 2.5) * (pt > 10.0)  * (0.85) +
                         (abs(eta) > 2.5)                                   * (0.00)}
}
```

`set ExecutionPath ListOfModuleNames`
: the global parameter called `ExecutionPath` defines the order of execution of various modules:

```tcl
set ExecutionPath {
  ParticlePropagator

  ChargedHadronTrackingEfficiency
  ElectronTrackingEfficiency
  MuonTrackingEfficiency

  ChargedHadronMomentumSmearing
  ElectronEnergySmearing
  MuonMomentumSmearing

  TrackMerger
  Calorimeter
  EFlowMerger

  PhotonEfficiency
  PhotonIsolation

  ElectronEfficiency
  ElectronIsolation

  MuonEfficiency
  MuonIsolation

  MissingET

  FastJetFinder
  BTagging
  TauTagging

  UniqueObjectFinder

  ScalarHT

  TreeWriter
}
```

## Global parameters

It is possible to specify the following global parameters: `MaxEvents`, `SkipEvents` and `RandomSeed`.

For instance, the following configuration allows to specify a particular random seed, skip the first 100 events and process the following 1000 events.

```tcl
set RandomSeed 23
set SkipEvents 100
set MaxEvents 1000
```

## Comments

A Tcl comment line begins with `#`.

## Variable Substitution

A dollar sign together with an immediately following variable name will be substituted by the value of the variable.
