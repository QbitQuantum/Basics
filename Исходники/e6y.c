void I_midiOutSetVolumes(int volume)
{
  // NSM changed to work on the 0-15 volume scale,
  // and to check mus_extend_volume itself.
  
  MMRESULT result;
  int calcVolume;
  MIDIOUTCAPS capabilities;
  unsigned int i;

  if (volume > 15)
    volume = 15;
  if (volume < 0)
    volume = 0;
  calcVolume = (65535 * volume / 15);

  //SDL_LockAudio(); // this function doesn't touch anything the audio callback touches

  //Device loop
  for (i = 0; i < midiOutGetNumDevs(); i++)
  {
    //Get device capabilities
    result = midiOutGetDevCaps(i, &capabilities, sizeof(capabilities));
    if (result == MMSYSERR_NOERROR)
    {
      //Adjust volume on this candidate
      if ((capabilities.dwSupport & MIDICAPS_VOLUME))
      {
        midiOutSetVolume((HMIDIOUT)i, MAKELONG(calcVolume, calcVolume));
      }
    }
  }

  //SDL_UnlockAudio();
}