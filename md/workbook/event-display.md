# Event Display

Delphes event display is based on the [Event Visualization Environment of ROOT](http://root.cern.ch/drupal/content/eve).

It can be run with the following commands:

```
make display
root -l examples/EventDisplay.C'("cards/delphes_card_CMS.tcl","delphes_output.root")'
```

![](/img/delphes_event_display_1.png)

The same examples shows how to generate a 3D representation of the geometry, which may be useful to spot trivial bugs in defining the acceptance of sub-detectors. The figure below shows for example the view generated for the default FCC card, showing the two calorimeters, their towers, as well as the acceptance of muon, calorimeters and tracker subsystems.

![](/img/delphes_event_display_2.png)
