void JMIDIInObj::close() {
  cs.lock();
  if (!connected) goto CSEND;
  connected = false;
#if defined(WIN32)
  midiInStop((HMIDIIN)handle);
  midiInReset((HMIDIIN)handle);
  midiInUnprepareHeader((HMIDIIN)handle, 
    (MIDIHDR*)(char*)data, sizeof(MIDIHDR));
  midiInClose((HMIDIIN)handle);
#endif
  handle = -1;
  data.Release();
  repaint();
CSEND:;
  cs.unlock();
}