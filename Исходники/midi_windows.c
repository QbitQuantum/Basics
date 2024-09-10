int
flushMidiDevice (MidiDevice *midi) {
  int ok = 1;

  if (midi->count > 0) {
    MMRESULT error;
    MIDIHDR header;
    
    header.lpData = midi->buffer;
    header.dwBufferLength = midi->count;
    header.dwFlags = 0;

    if ((error = midiOutPrepareHeader(midi->handle, &header, sizeof(header))) == MMSYSERR_NOERROR) {
      if ((error = midiOutLongMsg(midi->handle, &header, sizeof(header))) == MMSYSERR_NOERROR) {
        midi->count = 0;
      } else {
        logMidiOutError(error, LOG_ERR, "midiOutLongMsg");
        ok = 0;
      }

      while ((error = midiOutUnprepareHeader(midi->handle, &header, sizeof(header))) == MIDIERR_STILLPLAYING) {
        approximateDelay(1);
      }

      if (error != MMSYSERR_NOERROR) {
        logMidiOutError(error, LOG_ERR, "midiOutUnprepareHeader");
      }
    } else {
      logMidiOutError(error, LOG_ERR, "midiOutPrepareHeader");
      ok = 0;
    }
  }

  return ok;
}