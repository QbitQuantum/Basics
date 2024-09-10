//________________________________________________________________
static Boolean IsInternalSynth (char *name)
{
	UINT i, n = midiOutGetNumDevs ();
	for (i=0; i<n; i++) {
		MIDIOUTCAPS caps; 
		MMRESULT res = midiOutGetDevCaps (i, &caps, sizeof(caps));
		if (res == MMSYSERR_NOERROR) {
			if (caps.wTechnology != MOD_MIDIPORT)
				return strcmp (name, caps.szPname) == 0;
		}
	}
	return FALSE;
}