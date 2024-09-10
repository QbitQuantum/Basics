void MIDISong2::Stop ()
{
	if (PlayerThread)
	{
		SetEvent (ExitEvent);
		WaitForSingleObject (PlayerThread, INFINITE);
		CloseHandle (PlayerThread);
		PlayerThread = NULL;
	}
	if (MidiOut)
	{
		midiOutReset (MidiOut);
		if (VolumeWorks)
		{
			midiOutSetVolume (MidiOut, SavedVolume);
		}
		midiOutClose (MidiOut);
		MidiOut = NULL;
	}
}