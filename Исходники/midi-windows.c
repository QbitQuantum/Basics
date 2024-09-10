void midiClose(void) {
  MMRESULT res;
  
  //  printf("stop\n");
  if (MMSYSERR_NOERROR != midiInStop(inHandle)) {
    logPrintf(LOG_ERROR, "input stop error\n");
  }
  //  printf("reset\n");
  if (MMSYSERR_NOERROR != midiInReset(inHandle)) {
    logPrintf(LOG_ERROR, "input reset error\n");
  }

  int retry = 0;
  do {
    res = midiInClose(inHandle);
    if (res != MMSYSERR_NOERROR) {
      logPrintf(LOG_ERROR, "input close error\n");
    }
    if (res == MIDIERR_STILLPLAYING) {
      midiInReset(inHandle);
    }
    Sleep(10);
    retry++;
  } while ((res == MIDIERR_STILLPLAYING) && (retry < 10));
  
  midiInUnprepareHeader(inHandle, &midiHdr, sizeof(MIDIHDR));

  retry = 0;
  res = midiOutReset(outHandle);
  if (res != MMSYSERR_NOERROR) {
    logPrintf(LOG_ERROR, "output reset error\n");
  }
  do {
    res = midiOutClose(outHandle);
    if (res != MMSYSERR_NOERROR) {
      logPrintf(LOG_ERROR, "output close error\n");
    }
    Sleep(10);
    retry++;
  } while ((res == MIDIERR_STILLPLAYING) && (retry < 10));
}