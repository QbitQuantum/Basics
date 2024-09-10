static int read_stream_open(struct ausrc_st *st)
{
	MMRESULT err;
	WAVEFORMATEX  wfmt;
	int i;

	/* Open an audio INPUT stream. */
	st->wavein = NULL;
	st->pos = 0;
	st->rdy = false;
	st->stop = false;

	for (i = 0; i < READ_BUFFERS; i++) {
		memset(&st->bufs[i].wh, 0, sizeof(WAVEHDR));
		st->bufs[i].mb = mbuf_alloc(2 * st->prm.frame_size);
	}

	wfmt.wFormatTag      = WAVE_FORMAT_PCM;
	wfmt.nChannels       = st->prm.ch;
	wfmt.nSamplesPerSec  = st->prm.srate;
	wfmt.wBitsPerSample  = 16;
	wfmt.nBlockAlign     = (st->prm.ch * wfmt.wBitsPerSample) / 8;
	wfmt.nAvgBytesPerSec = wfmt.nSamplesPerSec * wfmt.nBlockAlign;
	wfmt.cbSize          = 0;
	err = waveInOpen(&st->wavein,
			  WAVE_MAPPER,
			  &wfmt,
			  (DWORD_PTR) waveInCallback,
			  (DWORD_PTR) st,
			  CALLBACK_FUNCTION | WAVE_FORMAT_DIRECT);
	if (err != MMSYSERR_NOERROR) {
		DEBUG_WARNING("waveInOpen: failed %d\n", err);
		return EINVAL;
	}
	/* Prepare enough IN buffers to suite at least 50ms of data */
	for (i = 0; i < READ_BUFFERS; i++)
		add_wave_in(st);

	waveInStart(st->wavein);

	return 0;
}