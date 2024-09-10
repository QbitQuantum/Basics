value rtmidi_out_closeport(value obj) {
  RtMidiOut *midiout = (RtMidiOut *)(intptr_t)val_float(obj);
  midiout->closePort();
  return alloc_null();
}