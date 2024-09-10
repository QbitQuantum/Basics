static int read_stream_open(struct ausrc_st *st, const struct ausrc_prm *prm,
			    unsigned int dev)
{
	WAVEFORMATEX wfmt;
	MMRESULT res;
	uint32_t sampc;
	int i, err = 0;

	/* Open an audio INPUT stream. */
	st->wavein = NULL;
	st->bufs_idx = 0;

	sampc = prm->srate * prm->ch * prm->ptime / 1000;

	for (i = 0; i < READ_BUFFERS; i++) {
		memset(&st->bufs[i].wh, 0, sizeof(WAVEHDR));
		st->bufs[i].mb = mbuf_alloc(2 * sampc);
		if (!st->bufs[i].mb)
			return ENOMEM;
	}

	wfmt.wFormatTag      = WAVE_FORMAT_PCM;
	wfmt.nChannels       = prm->ch;
	wfmt.nSamplesPerSec  = prm->srate;
	wfmt.wBitsPerSample  = 16;
	wfmt.nBlockAlign     = (prm->ch * wfmt.wBitsPerSample) / 8;
	wfmt.nAvgBytesPerSec = wfmt.nSamplesPerSec * wfmt.nBlockAlign;
	wfmt.cbSize          = 0;

	res = waveInOpen(&st->wavein, dev, &wfmt,
			  (DWORD_PTR) waveInCallback,
			  (DWORD_PTR) st,
			  CALLBACK_FUNCTION | WAVE_FORMAT_DIRECT);
	if (res != MMSYSERR_NOERROR) {
		warning("sinwave: waveInOpen: failed %d\n", err);
		return EINVAL;
	}

	/* Prepare enough IN buffers to suite at least 50ms of data */
	for (i = 0; i < READ_BUFFERS; i++)
		err |= add_wave_in(st);

	waveInStart(st->wavein);

	return err;
}