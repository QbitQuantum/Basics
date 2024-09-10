static void MidiIntSetVolume(int vol)
{
	DWORD v = (vol * 65535 / 127);
	midiOutSetVolume((HMIDIOUT)_midi.devid, v + (v << 16));
}