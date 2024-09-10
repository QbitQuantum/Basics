//---------------------------------------------------------------------------
static void TVPMIDIOut(tjs_uint8 *data,int len)
{
	if(!TVPMIDIOutHandle) return;
	TVPCheckMIDIDelay();
	MIDIHDR hdr;
	hdr.lpData = (char*)data;
	hdr.dwFlags = 0;
	hdr.dwBufferLength = len;
	midiOutPrepareHeader(TVPMIDIOutHandle, &hdr, sizeof(MIDIHDR));
	midiOutLongMsg(TVPMIDIOutHandle, &hdr, sizeof(MIDIHDR));
	midiOutUnprepareHeader(TVPMIDIOutHandle, &hdr, sizeof(MIDIHDR));
}