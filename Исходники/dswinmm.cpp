static void shutdownMixer(void)
{
    if(!initMixerOk)
        return; // Can't uninitialize if not inited.

    // Restore the original mixer volumes, if possible.
    mixer4i(MIX_MIDI, MIX_SET, MIX_VOLUME, origVol);
    if(origCDVol != MIX_ERROR)
        mixer4i(MIX_CDAUDIO, MIX_SET, MIX_VOLUME, origCDVol);

    mixerClose(mixer);
    mixer = NULL;
    initMixerOk = false;
}