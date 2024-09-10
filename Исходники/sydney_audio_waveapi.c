/** sync/timing */
int sa_stream_get_position(sa_stream_t *s, sa_position_t position, int64_t *pos) {
	int status;
  MMTIME  mm;

  ERROR_IF_NO_INIT(s);

  if (position != SA_POSITION_WRITE_HARDWARE) {
    return SA_ERROR_NOT_SUPPORTED;
  }
  // request playback progress in bytes
  mm.wType = TIME_BYTES;		
	status = waveOutGetPosition(s->hWaveOut, &mm, sizeof(MMTIME));
  HANDLE_WAVE_ERROR(status, "reading audio buffer position");
  *pos = (int64_t)mm.u.cb;

	return SA_SUCCESS;
}