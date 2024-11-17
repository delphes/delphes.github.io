# List of Modules

## AngularSmearing

Performs transverse angular resolution smearing.

- input:
  - InputArray
- output:
  - OutputArray
- parameters:
  - EtaResolutionFormula - eta resolution specified as a function of transverse momentum and pseudo-rapidity
  - PhiResolutionFormula - phi resolution specified as a function of transverse momentum and pseudo-rapidity

## BTagging

Determines origin of jet, applies b-tagging efficiency (miss identification rate) formulas and sets b-tagging flags

- input:

  - PartonInputArray
  - JetInputArray

- output:

  - OutputArray

- parameters:

  - DeltaR
  - PartonPTMin
  - PartonEtaMax
  - EfficiencyFormula - efficiency (miss identification rate) specified for a PDG code as a function of transverse momentum and pseudo-rapidity
  - BitNumber (default 0)

Starting from version 3.0.7 it is possible to test several (up to 32) b-tagging working points per jet. The BTag variable in the Jet class can store up to 32 bits. If the user specifies BitNumber = 0 in the BTagging module, that particular bit will be stored in the first position. If BitNumber = 1, it will be in the second position, etc ...

In order to check whether a jet has passed the b-tagging criteria defined by the BitNumber = i, just do:

```
Bool_t BtagOk = ( jet->BTag & (1 << i) );
```

## TrackCountingBTagging

For information on this module, see [this presentation](/etc/btagging_v2.pdf).

## PhotonConversions

For information on this module, see [this presentation](/etc/delphes_conversions.pdf).

## SimpleCalorimeter

Fills calorimeter towers, performs calorimeter resolution smearing, pre-selects towers hit by photons and performs an energy flow algorithm.

- input:

  - ParticleInputArray
  - TrackInputArray

- output:

  - TowerOutputArray
  - EFlowTowerOutputArray

- parameters:

  - EtaPhiBins
  - EnergyFraction
  - SmearTowerCenter
  - EnergyMin
  - EnergySignificanceMin
  - ResolutionFormula - energy resolution as a function of energy and pseudo-rapidity

## Calorimeter

Fills calorimeter towers for both ECAL and HCAL, performs calorimeter resolution smearing, preselects towers hit by photons and performs an energy flow algorithm. ECAL and HCAL are tied together and have the same granularity. For more flexibility use SimpleCalorimeter.

- input:

  - ParticleInputArray
  - TrackInputArray

- output:

  - TowerOutputArray
  - PhotonOutputArray
  - EFlowTrackOutputArray
  - EFlowPhotonOutputArray
  - EFlowNeutralHadronOutputArray

- parameters:

  - EtaPhiBins
  - EnergyFraction
  - SmearTowerCenter
  - ECalEnergyMin
  - HCalEnergyMin
  - ECalEnergySignificanceMin
  - HCalEnergySignificanceMin
  - ECalResolutionFormula - energy resolution as a function of energy and pseudo-rapidity
  - HCalResolutionFormula - energy resolution as a function of energy and pseudo-rapidity

## Efficiency

Selects candidates from the InputArray according to the efficiency formula

- input:

  - InputArray

- output:

  - OutputArray

- parameters:

  - EfficiencyFormula - efficiency specified as a function of transverse momentum and pseudo-rapidity

## EnergySmearing

Performs energy resolution smearing

- input:

  - InputArray

- output:

  - OutputArray

- parameters:

  - ResolutionFormula - energy resolution specified as a function of transverse momentum and pseudo-rapidity

## EnergyScale

Applies an energy scale to the specified object collection

- input:

  - InputArray

- output:

  - OutputArray

- parameters:

  - ResolutionFormula - energy scale specified as a function of transverse momentum and pseudo-rapidity

## FastJetFinder

Finds jets using the [FastJet]($fastjet$) library, for more information about parameters see chapters 4 and 5 of the [FasJet user manual]($fastjet$/repo/fastjet-doc-3.1.0.pdf)

- input:

  - InputArray

- output:

  - OutputArray

- parameters:

  - JetAlgorithm - 1 CDFJetClu, 2 MidPoint, 3 SIScone, 4 kt, 5 Cambridge/Aachen, 6 anti-kt, 7 anti-kt with winner-take-all axis (for N-subjettiness), 8 N-jettiness
  - ParameterR
  - ConeRadius
  - SeedThreshold
  - ConeAreaFraction
  - AdjacencyCut
  - OverlapThreshold
  - MaxIterations
  - MaxPairSize
  - Iratch
  - JetPTMin

To compute N-subjettiness variables (see JHEP 1103:015 (2011) and JHEP 1202:093 (2012)), use option 7.

- parameters:

  - ComputeNsubjettiness 0 (off), 1 (on)
  - AxisMode - 1 wta kt axes, 2 optimised wta kt axes, 3 kt axes, 4 optimized kt axes
  - Beta

- recommended values for Beta:

  - beta with kt_axes: 2.0
  - beta with wta_kt_axes: anything greater than 0.0 (particularly good for 1.0)
  - beta with onepass_kt_axes or onepass_wta_kt_axes: between 1.0 and 3.0

To apply jet grooming such as Trimming ([arXiv:0912.1342]($arxiv$/0912.1342)) , Pruning ([arXiv:0912.0033]($arxiv$/0912.0033)), and SoftDrop ([arXiv:1402.2657]($arxiv$/1402.2657))

- parameters:

  - ComputeTrimming 0 (off), 1 (on)
  - ComputePruning 0 (off), 1 (on)
  - ComputeSoftDrop 0 (off), 1 (on)

- default values:

  - RTrim 0.2 (triming)
  - PtFracTrim 0.05 (triming)
  - ZcutPrun 0.1 (pruning)
  - RcutPrun 0.5 (pruning)
  - RPrun 0.8 (pruning)
  - BetaSoftDrop 0.0 (soft-drop)
  - SymmetryCutSoftDrop 0.1 (soft-drop)
  - R0SoftDrop 0.8 (soft-drop)

- Example:

```
module FastJetFinder FastJetFinder {

 set InputArray EFlowMerger/eflow

 set OutputArray jets

  set JetAlgorithm 5
  set ParameterR 1.0

  set ComputeNsubjettiness 1
  set Beta 1.0
  set AxisMode 1

  set ComputeTrimming 1
  set RTrim 0.2
  set PtFracTrim 0.05

  set ComputePruning 1
  set ZcutPrun 0.1
  set RcutPrun 0.5
  set RPrun 0.8

  set ComputeSoftDrop 1
  set BetaSoftDrop 0.0
  set SymmetryCutSoftDrop 0.1
  set R0SoftDrop 0.8

  set JetPTMin 200.0
}

```

- To cluster jets with N-jettiness, use

```
set JetAlgorithm 8
```

}}}

## Hector

Hector takes care of propagating particle within the beam line up to a certain point. (see JINST 2:P09005 (2007))

- input:

  - InputArray

- output:

  - OutputArray (propagated particles)

- parameters:

  - Direction
  - BeamLineLength
  - Distance
  - OffsetX
  - OffsetS
  - SigmaE
  - SigmaX
  - SigmaY
  - SigmaT
  - EtaMin
  - BeamLineFile
  - IPName

## IdentificationMap

This module was written specifically for LHCb, but can be used for any detector. It consists in a generalized version of the Efficiency module. The user can specify not only the probably of reconstructing a particle with a given efficiency but also the probability of being misidentified as another particle. A working example is provided in the [LHCb card]($source$/cards/delphes_card_LHCb.tcl).

- input:

  - InputArray

- output:

  - OutputArray

- parameters:

  - EfficiencyFormula (usage: {PID in} {PID out} {formula})

- Example for efficiency map:

- Make sure "PID in" and "PID out" have the same charge (e.g {-13} {211} or {-321} {211}) Also, {211} {-13} is equivalent to {-211} {13} (and needs to be written once only...)

- Make sure that for a given (pt, eta) the sum of probabilities do not exceed 1.

```
## --- pions ---
add EfficiencyFormula {211} {211} {(eta <= 2.0)                           * (0.00) +
                                   (eta > 2.0 && eta <= 5.0) * (pt < 0.8) * (0.00) +
                                   (eta > 2.0 && eta <= 5.0) * (pt >= 0.8)* (0.95) +
                                   (eta > 5.0)                            * (0.00)}

add EfficiencyFormula {211} {-13} {(eta <= 2.0)                           * (0.00) +
                                   (eta > 2.0 && eta <= 5.0) * (pt < 0.8) * (0.00) +
                                   (eta > 2.0 && eta <= 5.0) * (pt >= 0.8)* (0.005 + 0.0663*exp(-0.13*pt*cosh(eta))) +
                                   (eta > 5.0)                            * (0.00)}

## --- kaons ---

add EfficiencyFormula {321} {321} {(eta <= 2.0)              * (0.00) +
                                   (eta > 2.0 && eta <= 5.0) * (pt < 0.8) * (0.00) +
                                   (eta > 2.0 && eta <= 5.0) * (pt >= 0.8)* (0.95) +
                                   (eta > 5.0)               * (0.00)}

add EfficiencyFormula {321} {-13} {(eta <= 2.0)              * (0.00) +
                                   (eta > 2.0 && eta <= 5.0) * (pt < 0.8) * (0.00) +
                                   (eta > 2.0 && eta <= 5.0) * (pt >= 0.8)* (0.005 + 0.086*exp(-0.11*pt*cosh(eta))) +
                                   (eta > 5.0) * (0.00)}

## --- protons ---

add EfficiencyFormula {2212} {2212} {(eta <= 2.0) * (0.00) +
                                     (eta > 2.0 && eta <= 5.0) * (pt < 0.8) * (0.00) +
                                     (eta > 2.0 && eta <= 5.0) * (pt >= 0.8)* (0.95) +
                                     (eta > 5.0) * (0.00)}

add EfficiencyFormula {2212} {-13} {(eta <= 2.0) * (0.00) +
                                    (eta > 2.0 && eta <= 5.0) * (pt < 0.8) * (0.00) +
                                    (eta > 2.0 && eta <= 5.0) * (pt >= 0.8)* (0.002) +
                                    (eta > 5.0) * (0.00)}
## --- muons ---

add EfficiencyFormula {-13} {-13} {(eta <= 2.0) * (0.00) +
                                   (eta > 2.0 && eta <= 5.0) * (pt < 0.8)* (0.00) +
                                   (eta > 2.0 && eta <= 5.0) * (pt >= 0.8)* (0.97) +
                                   (eta > 5.0) * (0.00)}

## efficiency for other charged particles (should be always {0} {0} {formula})

add EfficiencyFormula {0} {0} {(eta <= 2.0) * (0.00) +
                               (eta > 2.0 && eta <= 5.0) * (pt < 0.8) * (0.00) +
                               (eta > 2.0 && eta <= 5.0) * (pt > 0.8) * (0.95) +
                               (eta > 5.0) * (0.00)}
}
```

## Isolation

Sums transverse momenta of isolation objects (tracks, calorimeter towers, etc) within a DeltaRMax cone around a candidate, calculates fraction of this sum to the candidate's transverse momentum and outputs candidates that have the transverse momenta fraction less than PTRatioMax.

- input:

  - CandidateInputArray
  - IsolationInputArray

- output:

  - OutputArray

- parameters:

  - UsePTSum
  - DeltaRMax
  - PTMin
  - PTRatioMax (if UsePTSum is false)
  - PTSumMax (if UsePTSum is true)

By default the isolation variable is defined as relative. To use an absolute isolation criterion, declare UsePTSum as true, and declare the parameter PTSumMax instead of PTRatioMax.

## Merger

Merges multiple input arrays into one output array, sums transverse momenta and transverse energies of all input objects

- input:

  - InputArray - list of input arrays and corresponding selection criteria as functions of transverse momentum and pseudo-rapidity

- output:

  - OutputArray
  - MomentumOutputArray
  - EnergyOutputArray

## MomentumSmearing

Performs transverse momentum resolution smearing

- input:

  - InputArray

- output:

  - OutputArray

- parameters:

  - ResolutionFormula - transverse momentum resolution specified as a function of transverse momentum and pseudo-rapidity

## ParticlePropagator

Propagates charged and neutral particles from a given vertex to a cylinder defined by its radius, its half-length, centered at (0,0,0) and with its axis oriented along the z-axis

- input:

  - InputArray

- output:

  - OutputArray
  - ChargedHadronOutputArray
  - ElectronOutputArray
  - MuonOutputArray

- parameters:

  - Radius
  - HalfLength
  - Bz
  - RadiusMax
  - HalfLengthMax

RadiusMax and HalfLengthMax can be used to keep decay products of the long-lived particles. If the decay products appear between Radius and RadiusMax or between HalfLength and HalfLengthMax, then they are kept in the OutputArray collection. These particles aren't propagated. They aren't used for electron/muon/charged particle identification. They can only create energy deposits in the calorimeters.

## PdgCodeFilter

Removes particles with specific pdg code from given collection.

- input:

  - InputArray

- output:

  - OutputArray

- parameters:

  - PTMin (min pt of particle to be removed)
  - PdgCode (list of pdg codes to be vetoed)

- Example (to remove neutrinos from stable gen particles):

```
module PdgCodeFilter NeutrinoFilter {
  set InputArray Delphes/stableParticles
  set OutputArray filteredParticles
  set PTMin 0.0
  add PdgCode {12}
  add PdgCode {14}
  add PdgCode {16}
  add PdgCode {-12}
  add PdgCode {-14}
  add PdgCode {-16}
}
```

## TauTagging

Determines origin of jet, applies tau-tagging efficiency (miss identification rate) formulas and sets tau-tagging flags

- input:

  - ParticleInputArray
  - PartonInputArray
  - JetInputArray

- output:

  - OutputArray

- parameters:

  - DeltaR
  - TauPTMin
  - TauEtaMax
  - EfficiencyFormula - efficiency (miss identification rate) specified for a PDG code as a function of transverse momentum and pseudo-rapidity

## TreeWriter

Fills ROOT tree branches

- parameters:
  - Branch - list of input arrays, corresponding ROOT tree branches and ROOT classes

## UniqueObjectFinder

Finds uniquely identified photons, electrons, taus and jets

- parameters:
  - InputArray - list of input and output arrays there earlier arrays take precedence over later ones
