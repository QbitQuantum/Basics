//
// I_ResetMidiVolume()
//
// [SL] 2011-12-31 - Set all midi devices' output volume to maximum in the OS.
// This function is used to work around shortcomings of the SDL_Mixer library
// on the Windows Vista/7 platform, where PCM and MIDI volumes are linked
// together in the OS's audio mixer.  Because SDL_Mixer sets the volume of
// midi output devices to 0 when not playing music, all sound
// output (PCM & MIDI) becomes muted in Odamex (see Odamex bug 443).
//
void I_ResetMidiVolume()
{
	#if defined(_WIN32) && !defined(_XBOX)
	SDL_LockAudio();

	for (UINT device = MIDI_MAPPER; device != midiOutGetNumDevs(); device++)
	{
		MIDIOUTCAPS caps;
		// Can this midi device change volume?
		MMRESULT result = midiOutGetDevCaps(device, &caps, sizeof(caps));

		// Set the midi device's volume
		static const DWORD volume = 0xFFFFFFFF;		// maximum volume		
		if (result == MMSYSERR_NOERROR && (caps.dwSupport & MIDICAPS_VOLUME))
			midiOutSetVolume((HMIDIOUT)device, volume);			
	}

	SDL_UnlockAudio();
	#endif	// _WIN32
}