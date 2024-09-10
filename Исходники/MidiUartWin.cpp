MidiUartWinClass::~MidiUartWinClass() {
  if (inHandle != (HMIDIIN)-1) {
    if (midiInStop(inHandle) != MMSYSERR_NOERROR) {
      throw "Could not stop MIDI input";
    }
    if (midiInReset(inHandle) != MMSYSERR_NOERROR) {
      throw "Could reset MIDI input";
    }
    if (midiInClose(inHandle) != MMSYSERR_NOERROR) {
      throw "Could not close MIDI input";
    }
		
    midiInUnprepareHeader(inHandle, &midiHdr, sizeof(MIDIHDR));
  }

  if (outHandle != (HMIDIOUT)-1) {
    midiOutClose(outHandle);
  }
}