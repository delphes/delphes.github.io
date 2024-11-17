# Releases

3 June 2021: [Delphes 3.5.0](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.5.0.tar.gz)

- fixed validation code
- fixed weighted time and tower position in calorimeter modules
- fixed propagation of charged particles with low transverse momentum (thanks to Olmo Cerri)
- updated FastJet library to 3.3.4 and FastJet Contrib library to 1.045
- removed zero mass assumption for all tracks
- added support for HepMC3 format
- added particle-density dependence to formula parameterization (thanks to Roberto Preghenella)
- added DecayFilter module for LLP decay in flight
- added PFcandidate class to ROOT tree writer
- added neutral and charged energy fraction to jets
- added generalized ee kT clustering
- added covariance matrix for track parameters smearing (thanks to Franco Bedeschi)
- added IDEA card with track covariance
- added generic ILC detector model
- added muon collider detector model
- added LHeC and FCCeh cards

23 August 2019: [Delphes 3.4.2](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.4.2.tar.gz)

- added DenseTrackFilter for modelling tracking inefficiencies in boosted, dense environments
- added detector cards for CLIC, HL-LHC and IDEA detectors
- added muons to Tower collection used for jets reconstruction and MET calculation in the ATLAS card ([#1118](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/1118))
- added Weight branch to HepMC
- added Jet constituent output to FastJetFinder (allows more complex schemes of MET calculation) ([#1349](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/1349))
- added Valencia jet algorithm from FastJet Contrib library and exclusive jet clustering for e+e- collisions (thanks to Ulrike Schnoor)
- added possibility to read cross section from LHE files produced with Wizard event generator
- added NeutralOutputArray in ParticlePropagator
- added various information in StatusPidFilter (B and tau decay products, photons, SUSY particles, W daughters)
- added DelphesProIO reader for ProIO data format (thanks to Sergei Chekanov)
- improved TrackSmearing and updated TrackCountingBTagging (thanks to Kevin Pedro)
- adapted Efficiency and DelphesFormula to long-lived particles
- adapted Python analysis code to recent ROOT versions (thanks to Kerim Suruliz)
- updated class version of LHEFEvent, HepMCEvent, Photon, Electron, Muon, Jet and Candidate ([#1363](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/1363))
- updated FastJet library to 3.3.2 and FastJet Contrib library to 1.041
- updated copyright and licensing information
- removed dependency on the RPC and XDR libraries from STDHEP reader ([#1310](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/1310))
- fixed Delphes class destructor (TList::Clear error) ([#1320](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/1320))
- corrected ECAL granularity in the ILD detector configuration

26 April 2017: [Delphes 3.4.1](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.4.1.tar.gz)

- added RadiusMax and HalfLengthMax to ParticlePropagator to keep decay products of the long-lived particles ([#1084](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/1084))
- fixed compilation of Validation.cpp
- improved CMake configuration
- fixed weights in LHEFReader
- fixed bug in Charged Hadron Subtraction (CHS)
- promoted z vertex resolution to TFormula
- fixed bugs in DelphesDisplay
- added jet substructure to default CMS and FCC cards
- updated tracker and calorimeter resolution in the FCC card
- added preliminary FCC-hh card with pile-up
- corrected ECAL granularity in the ILD detector configuration

10 November 2016: [Delphes 3.4.0](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.4.0.tar.gz)

- corrected granularities for ECAL and HCAL in ATLAS and CMS cards
- included latest FCC-hh and CEPC detector cards
- improved particle flow algorithm
- updated FastJet library to 3.2.1
- updated Nsubjettiness library to 2.2.4
- added script that produce validation plots
- added DelphesROOT reader
- added TrackSmearing and BeamSpotFilter modules
- completed TimeSmearing module
- added preliminary version of vertex clustering algorithm in 3/4D, VertexFinder and VertexFinder4D (special thanks to A. Hart and L. Gray)
- fixed muon efficiency at high energy
- replaced gaussian smearing with lognormal in MomentumSmearing module
- made pyROOT Example1.py compatible with ROOT

24 August 2016: [Delphes 3.3.3](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.3.3.tar.gz)

- improved compatibility with ROOT >= 6.04
- removed test of praticle stability based on ROOT pdgtable ([#347](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/347), [#753](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/753), [#821](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/821), [#855](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/855))
- fixed bugs in DelphesCMSFWLite
- fixed bugs in PUPPI
- fixed compiler and linker flags for Pythia8
- added CMS Phase II cards
- added particle gun to DelphesPythia8
- added jet merging to DelphesPythia8 based on Pythia8 main32.cc
- added UseMiniCone option in Isolation module
- added RecoPuFilter module
- added back OldCalorimeter for CheckMate bwd compatibilty ([#591](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/591))
- updated tracking and calorimeter resolution in CMS cards

16 December 2015: [Delphes 3.3.2](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.3.2.tar.gz)

- added pre-validated card for CMS upgrade Phase II studies
- added TrackCountingTauTagging module (a la CheckMate)
- updated tau-tagging efficiency according to ATL-PHYS-PUB-2015-045

20 November 2015: [Delphes 3.3.1](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.3.1.tar.gz)

- corrected light parton mistag rate in b-tagging formula for CMS and ILD cards
- added tracks to output in ILD card to enable root2lhco conversion
- fixed muon collection in ILD card
- added example for pileup generation with Pythia8
- moved to loose isolation working points for ATLAS and CMS cards
- added UseRhoCorrection switch to decide which isolation variable to use for selection (true by default)
- switch to Rapidity selector (SelectorRapRange) for pile-up density computation in FastJet to ensure backward compatibility
- addressed N-subjettiness warnings in 2.2.1 version

9 October 2015: [Delphes 3.3.0](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.3.0.tar.gz)

- improved energy-flow algorithm for high momentum
- updated b-tagging parameterisations to recent ATLAS and CMS publications
- updated FastJet library to 3.1.3
- updated Nsubjettiness library to 2.2.1
- added a detector card for the ILD detector (for ILC) based on [http://arxiv.org/abs/1306.6329]($arxiv$/1306.6329)
- adapted examples, EventDisplay, DelphesFormula and DelphesTF2 to ROOT 6.04
- fixed tau-tagging for events without tau (thanks to Sho Iwamoto)
- fixed UniqueObjectFinder ([#728](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/728))
- added JetFakeParticle module
- added PhotonConversions module
- added TaggingParticlesSkimmer module
- added phi and energy dependence to AngularSmearing, BTagging, Efficiency, EnergyScale, EnergySmearing, IdentificationMap, ImpactParameterSmearing and MomentumSmearing
- added IsRecoPU flag and PTMin parameter to TrackPileUpSubtractor
- added Invert and Status options to PdgCodeFilter (thanks to Chase Shimmin)
- added new isolation variables to Candidate, Electron, Muon and Photon classes (thanks to Raffaele Gerosa)
- added code from CMS to PileUpMerger and PileUpMergerPythia8
- added timing information to Calorimeter
- added new PileUpJetID version (thanks to Seth Senz)
- added Area 4-vector to jet class
- added PUPPI algorithm and RunPUPPI module
- added RecursiveTools package from fastjet contribs
- replaced N-subjettiness with an array in Jet class (same as in Candidate class)
- added Trimming, Pruning and SoftDrop to FastJetFinder
- added possibility to use DelphesPythia8 with LHE files
- added Pythia8 examples
- added JetFlavorAssociation module with Physics and Algorithmic definitions of the jet flavor
- added new jet flavor definitions to the BTagging module (available only when running DelphesPythia8 with LHE files)

22 December 2014: [Delphes 3.2.0](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.2.0.tar.gz)

- moved code repository to [GitHub](http://github.com/delphes/delphes)
- moved configuration files from examples to cards directory
- new event display, with automatic discovery of the object collections, navigation controls, and 3D geometry sketch (for more details, see [EventDisplay](/workbook/event-display))
- updated FastJet library to 3.1.0
- added zero suppression to Calorimeter and SimpleCalorimeter modules
- added SmearTowerCenter configuration parameter to Calorimeter and SimpleCalorimeter modules ([#363](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/363))
- added FastJetGridMedianEstimator module (provides much faster pile-up subtraction based on a fixed grid eta-dependent average pile-up density computation)
- added AngularSmearing module (to smear track eta,phi)
- added PdgCodeFilter (to veto particle with given PID from collections)
- added IdentificationMap (allows to apply (mis)-identification)
- added Example4.C (provides an example on how to compute the jet energy scale)
- added examples (examples/ExternalFastJet) on how to run Delphes as a library with external FastJet installation
- updated card for FCC studies (cards/delphes_card_FCC_basic.tcl)
- added card for LHCb studies (cards/delphes_card_LHCb.tcl)
- made interface with Pythia 8 turned off by default
- adapted Isolation module to new energy-flow photons and neutral hadrons ([#362](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/362))
- fixed jet mass calculation for anti-kt with winner-take-all ([#355](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/355))
- fixed crashing of root2lhco when ROOT file doesn't contain all required branches ([#340](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/340))
- added possibility to build Delphes with CMake ([#313](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/313))

6 May 2014: [Delphes 3.1.2](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.1.2.tar.gz)

- fixed smearing of (z,t) vertex distribution in the PileUpMerger module
- adapted DelphesSTDHEP to the latest version of the STDHEP format introduced in MadGraph5_aMC@NLO 2.1.2
- added Hector module (fast simulator for the transport of particles in beam lines, see JINST 2:P09005 (2007))
- added N-subjettiness and N-jettiness (identify boosted hadronically-decaying objects like electroweak bosons and top quarks, see JHEP 1103:015 (2011), 1202:093 (2012) and 1404:017 (2014))
- added SimpleCalorimeter module (to study effects of different granularity in ECAL and HCAL)
- added ImpactParameterSmearing module (to smear transverse and longitudinal track impact parameter needed for track counting b-tagging)
- added TrackCountingBTagging module (for simple b-tagging algorithm based on counting tracks with large impact parameter)
- added example card for FCC studies (examples/delphes_card_FCC_basic.tcl)

25 April 2014: [Delphes 3.1.1](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.1.1.tar.gz)

- adapted DelphesSTDHEP to the latest version of the STDHEP format introduced in MadGraph5_aMC@NLO 2.1.2

17 April 2014: [Delphes 3.1.0](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.1.0.tar.gz)

- added Hector module (fast simulator for the transport of particles in beam lines, see JINST 2:P09005 (2007))
- added N-subjettiness and N-jettiness (identify boosted hadronically-decaying objects like electroweak bosons and top quarks, see JHEP 1103:015 (2011), 1202:093 (2012) and 1404:017 (2014))
- added SimpleCalorimeter module (to study effects of different granularity in ECAL and HCAL)
- added ImpactParameterSmearing module (to smear transverse and longitudinal track impact parameter needed for track counting b-tagging)
- added TrackCountingBTagging module (for simple b-tagging algorithm based on counting tracks with large impact parameter)
- added example card for FCC studies (examples/delphes_card_FCC_basic.tcl)

20 January 2014: [Delphes 3.0.12](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.0.12.tar.gz)

- updated FastJet library to 3.0.6
- added smearing of (z,t) vertex distribution in the PileUpMerger module
- propagation time computed for every output collection
- added TimeSmearing module (for propagation time measurement)
- added PileUpJetId module (thanks to Seth Senz)

14 November 2013: [Delphes 3.0.11](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.0.11.tar.gz)

- new energy-flow algorithm, optimized for better compatibility with pile-up subtraction
- added possibility of computing pile-up density in different eta regions via the RhoEtaRange parameter in FastJetFinder module
- implemented correct efficiency/resolution for high pt muons in CMS cards
- removed pile-up subtraction on missing energy
- added possibility to read re-weighting information from LHEF input files
- added UsePTSum and PTSumMax parameters to isolation module
- added possibility of specifying the shape of pile-up distribution (via the PileUpDistribution parameter in the PileUpMerger module)
- added pile-up Vertex collection to the output tree

19 August 2013: [Delphes 3.0.10](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.0.10.tar.gz)

- new readers (DelphesProMC.cpp, DelphesProMC.py ([#220](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/220)), DelphesPythia8)
- new modules (EnergyScale, PileUpMergerPythia8, Weighter)
- new module parameters (absolute/relative isolation ([#187](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/187)), flat/poisson pile-up distribution)
- new global parameters (max number of events, skip events ([#183](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/183)), random seed ([#202](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/202)) )
- new branches (pile-up event density rho, MC event weight)
- updated CMS and ALTAS detector cards (and added ATLAS pile-up detector card)
- calorimeter smearing is now performed according to a logNormal distribution
- improved particle-flow algorithm ([#204](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/204))
- added calculation of particle propagation time in the tracker
- fixed tau-jet matching by only considering visible hadronic tau ([#208](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/208))
- read masses from MC event file ([#195](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/195), [#201](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/201))
- bug fixes in DelphesCMSFWLite ([#196](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/196))
- compilable analysis macro examples ([#182](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/182))
- ability to read MC re-weighting information from LHE files

23 May 2013: [Delphes 3.0.9](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.0.9.tar.gz)

- fixed reading of weighted STDHEP events ([#181](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/181))
- fixed script building Delphes with CMSFWLite ([#180](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/180))
- added more particles to StatusPidFilter ([#179](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/179))

17 May 2013: [Delphes 3.0.8](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.0.8.tar.gz)

- fixed treatment of units in HepMC format ([#175](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/175))
- added Weight to HepMCEvent branch to store the event weight ([#173](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/173))
- added Rho branch to store the rho energy density ([#176](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/176))
- added random rotation of pile-up events around the z-axis

26 April 2013: [Delphes 3.0.7](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.0.7.tar.gz)

- added separate make rule for the event display to fix the compilation problem for systems without OpenGL libraries ([#168](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/168), [#127](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/127))
- added Cloner module
- modified BTagging module (several BTagging bits can be stored for the same jet collection, see [Modules](/workbook/modules))

15 April 2013: [Delphes 3.0.6](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.0.6.tar.gz)

- fixed filtering of the partons used for b- and tau-tagging ([#163](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/163))
- fixed artefacts in jet eta distribution ([#169](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/169))
- fixed direction of MissingET ([#170](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/170))
- modified DelphesFormula to filter out the end-of-line characters
- added TrackPileUpSubtractor to fix the problem with the charged pile-up particles outside of the tracker coverage
- added ConstituentFilter module
- added StatusPidFilter module
- added hepmc2pileup and stdhep2pileup converters

8 March 2013: [Delphes 3.0.5](http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.0.5.tar.gz)

- fixed compilation of the PileUpMerger on MacOSX
- added support for large HepMC and STDHEP files on 32-bit systems (ticket [#163](https://cp3.irmp.ucl.ac.be/projects/delphes/ticket/163))
