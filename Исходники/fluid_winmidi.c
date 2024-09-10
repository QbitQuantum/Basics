/*
 * delete_fluid_winmidi_driver
 */
int
delete_fluid_winmidi_driver(fluid_midi_driver_t* p)
{
  fluid_winmidi_driver_t* dev = (fluid_winmidi_driver_t*) p;
  if (dev->hmidiin != NULL) {
    midiInStop(dev->hmidiin);
    midiInReset(dev->hmidiin);
    midiInClose(dev->hmidiin);
  }
  FLUID_FREE(dev);
  return 0;
}