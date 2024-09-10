void Mixer::open(unsigned numChannels, unsigned samplingFrequency, unsigned granularityInMS) {
  HMIXER newHMixer = NULL;
  do {
    MIXERCAPS mc;
    if (mixerGetDevCaps(index, &mc, sizeof mc) != MMSYSERR_NOERROR) break;

    #ifdef UNICODE
    // Copy the mixer name:
        wcstombs(name, mc.szPname, MAXPNAMELEN);
    #else
        strncpy(name, mc.szPname, MAXPNAMELEN);
    #endif

    // Find the correct line for this mixer:
    unsigned i, uWavIn;
    unsigned nWavIn = waveInGetNumDevs();
    for (i = 0; i < nWavIn; ++i) {
      WAVEINCAPS wic;
      if (waveInGetDevCaps(i, &wic, sizeof wic) != MMSYSERR_NOERROR) continue;

      MIXERLINE ml;
      ml.cbStruct = sizeof ml;
      ml.Target.dwType  = MIXERLINE_TARGETTYPE_WAVEIN;

    #ifdef UNICODE
          wcsncpy(ml.Target.szPname, wic.szPname, MAXPNAMELEN);
    #else
          strncpy(ml.Target.szPname, wic.szPname, MAXPNAMELEN);
    #endif

      ml.Target.vDriverVersion = wic.vDriverVersion;
      ml.Target.wMid = wic.wMid;
      ml.Target.wPid = wic.wPid;

      if (mixerGetLineInfo((HMIXEROBJ)index, &ml, MIXER_GETLINEINFOF_TARGETTYPE/*|MIXER_OBJECTF_MIXER*/) == MMSYSERR_NOERROR) {
				// this is the right line
	uWavIn = i;
	dwRecLineID = ml.dwLineID;
	break;
      }
    }
    if (i >= nWavIn) break; // error: we couldn't find the right line

    if (mixerOpen(&newHMixer, index, (unsigned long)NULL, (unsigned long)NULL, MIXER_OBJECTF_MIXER) != MMSYSERR_NOERROR) break;
    if (newHMixer == NULL) break;

    // Sanity check: re-call "mixerGetDevCaps()" using the mixer device handle:
    if (mixerGetDevCaps((UINT)newHMixer, &mc, sizeof mc) != MMSYSERR_NOERROR) break;
    if (mc.cDestinations < 1) break; // error: this mixer has no destinations

	if (!WindowsAudioInputDevice_common::openWavInPort(uWavIn, numChannels, samplingFrequency, granularityInMS)) break;

    hMixer = newHMixer;
    return;
  } while (0);

  // An error occurred:
  close();
}