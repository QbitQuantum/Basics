static int BlockOut(NativeMidiSong *song)
{
  MMRESULT err;
  int BlockSize;

  if ((song->MusicLoaded) && (song->NewEvents))
  {
    // proff 12/8/98: Added for savety
    midiOutUnprepareHeader((HMIDIOUT)hMidiStream,&song->MidiStreamHdr,sizeof(MIDIHDR));
    if (song->NewPos>=song->Size)
      return 0;
    BlockSize=(song->Size-song->NewPos);
    if (BlockSize<=0)
      return 0;
    if (BlockSize>36000)
      BlockSize=36000;
    song->MidiStreamHdr.lpData=(void *)((unsigned char *)song->NewEvents+song->NewPos);
    song->NewPos+=BlockSize;
    song->MidiStreamHdr.dwBufferLength=BlockSize;
    song->MidiStreamHdr.dwBytesRecorded=BlockSize;
    song->MidiStreamHdr.dwFlags=0;
    err=midiOutPrepareHeader((HMIDIOUT)hMidiStream,&song->MidiStreamHdr,sizeof(MIDIHDR));
    if (err!=MMSYSERR_NOERROR)
      return 0;
    err=midiStreamOut(hMidiStream,&song->MidiStreamHdr,sizeof(MIDIHDR));
      return 0;
  }
  return 1;
}