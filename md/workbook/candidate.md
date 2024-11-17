# Particle Candidate Class

Delphes `Candidate` class is inspired by the BaBar's `BtaCandidate`:

<http://www.slac.stanford.edu/BFROOT/www/doc/workbook/eventinfo/eventinfo.html#btacand>

`Candidate` can represent various levels of processing, various data types:

- generated particle,
- reconstructed object,
- combination of candidates.

The definition of the `Candidate` class can be found in [classes/DelphesClasses.h]($source$/classes/DelphesClasses.h).

Here are the most interesting fields of the `Candidate` class:

`Int_t PID;` - [Particle Data Group identifier](http://pdg.lbl.gov/2012/mcdata/mc_particle_id_contents.html)

`Int_t Status;` - generator specific status code: [HepMC status codes](http://lcgapp.cern.ch/project/simu/HepMC/205/status.html), [Herwig status codes](http://webber.home.cern.ch/webber/hw65_manual.html#htoc96), [Herwig++ status codes](https://herwig.hepforge.org/trac/wiki/FaQs#WhichHepMCstatuscodesareusedWhatdotheymean), [Pythia status codes](http://home.fnal.gov/~mrenna/lutp0613man2/node49.html)

`Int_t Charge;`

`Float_t Mass;`

`TLorentzVector Momentum, Position;` - momentum and position stored in form of [TLorentzVector](http://root.cern.ch/root/html/TLorentzVector.html) data type
