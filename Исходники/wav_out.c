static void WAV_WriteAudio(GF_AudioOutput *dr)
{
	LPWAVEHDR hdr;
	HRESULT hr;
	u32 i;
	WAVCTX();

	if (!ctx->hwo) return;

	WaitForSingleObject(ctx->event, INFINITE);

	if (ctx->exit_request) return;

	for (i=0; i<ctx->num_buffers; i++) {
		/*get buffer*/
		hdr = &ctx->wav_hdr[i];

		if (hdr->dwFlags & WHDR_DONE) {
			waveOutUnprepareHeader(ctx->hwo, hdr, sizeof(WAVEHDR));

			hdr->dwBufferLength = ctx->buffer_size;
			/*update delay*/
			ctx->delay = 1000 * i * ctx->buffer_size / ctx->fmt.nAvgBytesPerSec;
			/*fill it*/
			hdr->dwBufferLength = dr->FillBuffer(dr->audio_renderer, hdr->lpData, ctx->buffer_size);
			hdr->dwFlags = 0;
		    hr = waveOutPrepareHeader(ctx->hwo, hdr, sizeof(WAVEHDR));
			/*write it*/
			waveOutWrite(ctx->hwo, hdr, sizeof(WAVEHDR));
		}
	}
}