# Particle Candidate Class

Delphes `Candidate` class is inspired by the BaBar's `BtaCandidate`:

<https://www.slac.stanford.edu/BFROOT/www/doc/workbook/eventinfo/eventinfo.html#btacand>

`Candidate` can represent various levels of processing, various data types:

- generated particle,
- reconstructed object,
- combination of candidates.

The definition of the `Candidate` class can be found in [classes/DelphesClasses.h]($source$/classes/DelphesClasses.h).

Here are the most interesting fields of the `Candidate` class:

`Int_t PID;` - [Particle Data Group identifier](https://pdg.lbl.gov/2012/mcdata/mc_particle_id_contents.html)

`Int_t Status;` - generator specific status code

`Int_t Charge;`

`Float_t Mass;`

`TLorentzVector Momentum, Position;` - momentum and position stored in form of [TLorentzVector](https://root.cern/doc/master/classTLorentzVector.html) data type
