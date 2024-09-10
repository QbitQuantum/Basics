/* IDirectMusic8Impl IDirectMusic part: */
static HRESULT WINAPI IDirectMusic8Impl_EnumPort(LPDIRECTMUSIC8 iface, DWORD dwIndex, LPDMUS_PORTCAPS pPortCaps) {
	IDirectMusic8Impl *This = (IDirectMusic8Impl *)iface;
	TRACE("(%p, %d, %p)\n", This, dwIndex, pPortCaps);
	if (NULL == pPortCaps) { return E_POINTER; }
	/* i guess the first port shown is always software synthesizer */
	if (dwIndex == 0) 
	{
		IDirectMusicSynth8* synth;
		TRACE("enumerating 'Microsoft Software Synthesizer' port\n");
		CoCreateInstance (&CLSID_DirectMusicSynth, NULL, CLSCTX_INPROC_SERVER, &IID_IDirectMusicSynth8, (void**)&synth);
		IDirectMusicSynth8_GetPortCaps (synth, pPortCaps);
		IDirectMusicSynth8_Release (synth);
		return S_OK;
	}

/* it seems that the rest of devices are obtained thru dmusic32.EnumLegacyDevices...*sigh*...which is undocumented*/
#if 0
	int numMIDI = midiOutGetNumDevs();
	int numWAVE = waveOutGetNumDevs();
	int i;
	/* then return digital sound ports */
	for (i = 1; i <= numWAVE; i++)
	{
		TRACE("enumerating 'digital sound' ports\n");	
		if (i == dwIndex)
		{
			DirectSoundEnumerateA(register_waveport, pPortCaps);
			return S_OK;	
		}
	}
	/* finally, list all *real* MIDI ports*/
	for (i = numWAVE + 1; i <= numWAVE + numMIDI; i++) 
	{
		TRACE("enumerating 'real MIDI' ports\n");		
		if (i == dwIndex)
			FIXME("Found MIDI port, but *real* MIDI ports not supported yet\n");
	}
#endif	
	return S_FALSE;
}