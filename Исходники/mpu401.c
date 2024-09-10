/*---------------------------------------------------------------------
   Function: MPU_SendMidiImmediate

   Sends a MIDI message immediately to the the music device.
---------------------------------------------------------------------*/
void MPU_SendMidiImmediate( char *data, int count )
{
	MIDIHDR mhdr;
	static int masks[3] = { 0x00ffffffl, 0x0000ffffl, 0x000000ffl };

	if (!count) return;
	if (count<=3) midiOutShortMsg((HMIDIOUT)hmido, (*((long*)data)) & masks[count-1]);
	else {
		ZeroMemory(&mhdr, sizeof(mhdr));
		mhdr.lpData = data;
		mhdr.dwBufferLength = count;
		midiOutPrepareHeader((HMIDIOUT)hmido, &mhdr, sizeof(MIDIHDR));
		midiOutLongMsg((HMIDIOUT)hmido, &mhdr, sizeof(MIDIHDR));
		while (!(mhdr.dwFlags & MHDR_DONE)) ;
		midiOutUnprepareHeader((HMIDIOUT)hmido, &mhdr, sizeof(MIDIHDR));
	}
}