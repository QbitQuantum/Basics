void
cancelPcmOutput (PcmDevice *pcm) {
  waveOutReset(pcm->handle);
}