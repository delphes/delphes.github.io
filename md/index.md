## A framework for fast simulation of a generic collider experiment

Delphes is a C++ framework, performing a fast multipurpose detector response simulation. The simulation includes a tracking system, embedded into a magnetic field, calorimeters and a muon system. The framework is interfaced to standard file formats (e.g. Les Houches Event File or HepMC) and outputs observables such as isolated leptons, missing transverse energy and collection of jets which can be used for dedicated analyses. The simulation of the detector response takes into account the effect of magnetic field, the granularity of the calorimeters and sub-detector resolutions. Visualization of the final state particles is also built-in using the corresponding ROOT library.

## Community and support

The Delphes development model is community-based. Users willing to participate are encouraged to fork Delphes Git repository and to submit pull requests for improvements and bug fixes. The Delphes core development team from the [CP3 center](https://uclouvain.be/en/research-institutes/irmp/cp3) of the Université catholique de Louvain is in charge of the maintenance, releases, and general support to users via the ticket system.

## Documentation

Documentation is collected in the [Workbook](/workbook). Good starting point is the [Quick Tour](/workbook/quick-tour).

[![CC BY-SA](/img/cc.svg)](https://creativecommons.org/licenses/by-sa/4.0)

The Delphes project documentation is licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License](https://creativecommons.org/licenses/by-sa/4.0).

## References

If you use Delphes as part of a publication, you should include a citation to:

[JHEP 02 (2014) 057](<https://dx.doi.org/10.1007/JHEP02(2014)057>) [\[ arXiv:1307.6346 \[hep-ex\] \]]($arxiv$/1307.6346)

Optionally, you can also include a citation to:

[J.Phys.Conf.Ser. 523 (2014) 012033](https://iopscience.iop.org/1742-6596/523/1/012033/) [\[ inspire link \]](https://inspirehep.net/record/1299908)

[J.Phys.Conf.Ser. 608 (2015) 1, 012045](https://iopscience.iop.org/1742-6596/608/1/012045/) [\[ inspire link \]](https://inspirehep.net/record/1372992)

Also, please note that Delphes relies on a few external packages. If they are used they should be cited as well. For instance, the jet clustering procedure in Delphes is performed via the [FastJet]($fastjet$) package. If your analysis involves jets, you should explicitly include both a reference for the [FastJet]($fastjet$) package and for the relevant clustering algorithm you are using.

For more information on how to properly cite FastJet, please visit [this page]($fastjet$/about.html).

## Git access

The code is now fully on [GitHub](https://github.com/delphes/delphes). You can get the latest version of the code using the following command:

```
git clone https://github.com/delphes/delphes
```
