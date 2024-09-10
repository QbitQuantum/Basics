static
int set_pause(int flag)
{
  static int paused;
  MMRESULT error;

  if (flag && !paused) {
    error = waveOutPause(wave_handle);
    if (error != MMSYSERR_NOERROR) {
      audio_error = error_text(error);
      return -1;
    }
  }
  else if (!flag && paused) {
    error = waveOutRestart(wave_handle);
    if (error != MMSYSERR_NOERROR) {
      audio_error = error_text(error);
      return -1;
    }
  }

  paused = flag;

  return 0;
}