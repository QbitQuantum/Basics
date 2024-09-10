void WinMIDIDevice::Stop()
{
	if (PlayerThread != nullptr)
	{
		SetEvent(ExitEvent);
		WaitForSingleObject(PlayerThread, INFINITE);
		CloseHandle(PlayerThread);
		PlayerThread = nullptr;
	}

	midiStreamStop(MidiOut);
	midiOutReset((HMIDIOUT)MidiOut);
	if (VolumeWorks)
	{
		midiOutSetVolume((HMIDIOUT)MidiOut, SavedVolume);
	}
}