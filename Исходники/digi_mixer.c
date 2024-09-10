void digi_mixer_set_midi_volume( int mvolume ) {
#ifdef _WIN32
  int mm_volume;

  if (mvolume < 0)
    midi_volume = 0;
  else if (mvolume > 127)
    midi_volume = 127;
  else
    midi_volume = mvolume;

  // scale up from 0-127 to 0-0xffff
  mm_volume = (midi_volume << 1) | (midi_volume & 1);
  mm_volume |= (mm_volume << 8);

  if (hmp)
    midiOutSetVolume((HMIDIOUT)hmp->hmidi, mm_volume | mm_volume << 16);
#endif
  midi_volume = mvolume;
  if (!digi_initialised) return;
  mix_set_music_volume(mvolume);
}