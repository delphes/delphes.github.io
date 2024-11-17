# Running Delphes with Pile-Up

## Pile-up implementation in Delphes

Multiple particle interactions per bunch-crossing are now implemented in Delphes. The procedure is divided in two main parts:

- mixing pile-up events with the main interaction
- pile-up subtraction with the fast jet area method

An example card that uses the following is [cards/delphes_card_CMS_PileUp.tcl]($source$/cards/delphes_card_CMS_PileUp.tcl)

### Mixing pile-up

The mixing procedure is done via the `PileUpMerger` module. The user can specify 4 parameters: `PileUpFile`, `MeanPileUp`, `PileUpDistribution`, `ZVertexWidth`, `ZVertexResolution`.

`PileUpFile`

: The event sample containing pile-up events in binary format.

\`\`

: This format allows for faster random event access compared to root trees. Basic information about the event is contained (particle 4-momenta, vertex position, and Particle ID).

\`\`

: This sample has to be generated in advance with an event generator (typically Pythia6/8 or HERWIG) and then converted into binary format (see example below).

`MeanPileUp`

: The average amount of pile-up events per bunch-crossing. For each hard scattering, N pile-up events will be randomly chosen from the `PileUpFile`, where N is a random number following a distribution defined by the parameter `PileUpDistribution` with a mean `MeanPileUp`.

`PileUpDistribution`

: Defines the distribution of the number of pile-up events. 0 for Poisson, 1 for Uniform.

`ZVertexSpread`

: Pile-up and hard scattering events are randomly distributed in time and z position according to some parametrization specified by the user (in meters and second units). It can be either continuous or binned:

  ```
  set VertexDistributionFormula {exp(-(t^2/(2*(0.05/2.99792458E8*exp(-(z^2/(2*(0.05)^2))))^2)))}
  ```

  ```
  set VertexDistributionFormula {(abs(t) <= 1.0e-09) * (abs(z) <= 0.15) * (1.00) +
                                 (abs(t) >  1.0e-09) * (abs(z) <= 0.15) * (0.00) +
                                 (abs(t) <= 1.0e-09) * (abs(z) > 0.15)  * (0.00) +
                                 (abs(t) >  1.0e-09) * (abs(z) > 0.15)  * (0.00)}
  ```

### Time propagation and measurement

The time particle candidate of each particle candidate is then propagated up to the calorimeters. For calorimeter towers and jets, which are composite objects, the final time is simply the average time weighted by sqrt(E) of each individual component.

By default the time information is now stored in each output collection object. However, in order to account for an actual timing measurement, the module `TimeSmearing` should be called. This module simply smears (by a Gaussian) the final time according to some resolution specified by the user, controlled by the parameter

```
set TimeResolution 1.0e-10
```

### Pile-up contamination

For estimating neutral pile-up contribution we use the well known FastJet area method, see for instance [arXiv:0802.1188]($arxiv$/0802.1188), [arXiv:0707.1378]($arxiv$/0707.1378).

First, the user must specify whether to calculate the area while clustering the jets within the `FastJetFinder` module. Several methods for the area calculation can be specified (active area, passive area, Voronoi) via the parameter `AreaAlgorithm`. By default this parameter is set to 0 (no area calculation):

```
# area algorithm: 0 Do not compute area, 1 Active area explicit ghosts, 2 One ghost passive area, 3 Passive area, 4 Voronoi, 5 Active area
set AreaAlgorithm 5
```

Then the median density (in GeV/A) of pile-up contamination (rho) per event can the be computed within the `FastJetFinder` module:

```
set ComputeRho true
set RhoOutputArray rho
```

Note that it is common to use one jet algorithm for the rho density calculation (e.g kt with 0.6 cone) and one for the analysis (anti-kt with 0.5). In such a case, in order to be able to perform the pile-up subtraction (see below), one needs to compute the area also for the jets relevant for the analysis.

It is now possible to specify several eta ranges for the computation of the pile-up density, leading to a more accurate estimate. For instance:

```
add RhoEtaRange 0.0 2.5
add RhoEtaRange 2.5 5.0
```

Since FastJet version 3.1.0, the pile-up density can be computed using a fixed grid, resulting in much faster calculation. This can be done by calling the module FastJetGridMedianEstimator. You can specify different regions as before, and, in addition, the grid-spacing in eta, phi:

```
module FastJetGridMedianEstimator Rho {

  set InputArray Calorimeter/towers
  set RhoOutputArray rho

  # etamin etamax gridsize_eta gridsize_phi

  add GridRange 0.0 2.5 0.5 0.5
  add GridRange 2.5 5.0 0.5 0.5
```

Both the ATLAS and CMS pile-up card are released equipped with FastJetGridMedianEstimator since Delphes 3.2.0.

### Charged Pile-up subtraction

The charged pile-up subtraction is done via the TrackPileUpSubtractor module. It simply removes from the specified input collections tracks that are distant enough from the primary vertex. The distance is controlled by the following parameter:

`ZVertexResolution`

\:

\`\`

: For |z| \< ZVertexResolution the hard interaction vertex cannot be distinguished from pile-up vertices.

\`\`

: For |z| > ZVertexResolution the hard interaction vertex can be distinguished from pile-up vertices.

  ```
  module TrackPileUpSubtractor TrackPileUpSubtractor {

    add InputArray Calorimeter/eflowTracks eflowTracks
    add InputArray ElectronEnergySmearing/electrons electrons
    add InputArray MuonMomentumSmearing/muons muons

    set ZVertexResolution 0.0001
  }
  ```

### Neutral Pile-up subtraction

Since charged particles have already been subtracted to some extent, pile-up contamination only affects the jet energy resolution and the lepton/photon isolation.

- Jet pile-up subtraction is done via the `JetPileUpSubtractor` module that takes as input the jet collection and rho:

  ```
  set JetInputArray FastJetFinder/jets
  set RhoInputArray rho
  ```

- Isolation subtraction is done inside the `Isolation` module itself just by adding the line in the Delphes card:

  ```
  set RhoInputArray rho
  ```

### Pile-Up Jet Id (by Seth Zenz based on CMS Physics Analysis Summary JME-13-005)

This module computes jet id variables that are stored by default in the output Jet Collection. The ID variables can be computed either using the jet constituents:

```
set UseConstituents 1
```

or using all the neutral and charged particle-flow objects in a cone around the jet axis

```
set UseConstituents 0
```

The following variables are computed:

`NCharged`
: number of charged constituents

`NNeutrals`
: number of neutral constituents

`Beta`
: (sum pt of charged pile-up constituents)/(sum pt of charged constituents)

`BetaStar`
: (sum pt of charged constituents coming from hard interaction)/(sum pt of charged constituents)

`MeanSqDeltaR`
: average distance (squared) between constituent and jet weighted by pt (squared) of constituent.

`PTD`
: average pt between constituent and jet weighted by pt of constituent.

`FracPt[i]`
: (sum pt of constituent within a ring 0.1\*i\<DeltaR\<0.1\*(i+1) )/(sum pt)

## Isolation with pile-up

If UseRhoCorrection is set to true the rho-corrected variable is used for isolation:

```
IsolationVarRhoCorr = sumChargedNoPU + max(sumNeutral - max(rho, 0.0)*pi*R^2, 0.0)
```

Otherwise the beta variable is used:

```
IsolationVar = sumChargedNoPU + max(sumNeutral - 0.5*sumChargedPU, 0.0)
```

## Running Delphes with Pile-Up

Convert your minimum bias sample from hepmc, stdhep or root format into binary format:

```
./stdhep2pileup MinBias.pileup MinBias.hep
./hepmc2pileup MinBias.pileup MinBias.hepmc
./root2pileup MinBias.pileup MinBias.root
```

or, alternatively, you can use the MinBias.pileup distributed in each release. This small file contains only 1k minimum bias p p collisions at 13 TeV produced with Pythia8.

For large event generations it is recommended to generate a bigger MinBias sample. If you want to generate your own MinBias file, an example configuration file for Pythia8 is provided in [examples/Pythia8/generatePileUp.cmnd]($source$/examples/Pythia8/generatePileUp.cmnd). Instructions for how to generate directly a MinBias root output within Delphes using that configuration file is given [here](/workbook/pythia8).

Run Delphes on your sample X with pile-up:

```
./DelphesSTDHEP cards/delphes_card_CMS_PileUp.tcl X_PileUp.root X.hep
./DelphesSTDHEP cards/delphes_card_ATLAS_PileUp.tcl X_PileUp.root X.hep
```
