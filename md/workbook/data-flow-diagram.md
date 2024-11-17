# Data Flow Diagram

Complete data-flow diagram can be generated from a configuration file with the following command:

```sh
./doc/data_flow.sh cards/delphes_card_CMS.tcl
```

This script requires GraphViz to be installed.

Here is a simplified data-flow diagram of the Delphes fast simulation.

![data-flow diagram](/img/delphes_diagram.png)

- Event files coming from external Monte-Carlo generators are first processed by a reader stage.
- Pile-up events are then overlapped onto the hard scattering event.
- Long-lived particles are propagated to the calorimeters within a uniform magnetic field.
- Particles reaching the calorimeters deposit their energy in the calorimeters.
- The particle-flow algorithm produces four collections of 4-vectors: electrons, photons, particle-flow tracks and towers.
- Muons are selected from the stable particles and their 4-vectors are smeared.
- Charged hadrons coming from pile-up vertices are discarded and the residual event pile-up density is calculated.
- The pile-up density is then used to perform pile-up subtraction on jets and on the isolation parameter for muons, electrons and photons. No pile-up subtraction is performed on the missing energy.
- At the final stage, the duplicates of the reconstructed objects are removed.
- The output data are stored in a ROOT tree format and can be analyzed and visualized with the help of the ROOT data analysis framework. The ROOT tree files can be also converted to the LHCO file format.
- Each step is controlled by the configuration file.
