/* ============ Media Producer Interface ================= */
int tdav_producer_dsound_prepare(tmedia_producer_t* self, const tmedia_codec_t* codec)
{
	HRESULT hr;

	WAVEFORMATEX wfx = {0};
	DSCBUFFERDESC dsbd = {0};

	tdav_producer_dsound_t* dsound = (tdav_producer_dsound_t*)self;

	if(!dsound || !codec){
		TSK_DEBUG_ERROR("Invalid parameter");
		return -1;
	}

	if(dsound->device || dsound->captureBuffer){
		TSK_DEBUG_ERROR("Producer already prepared");
		return -2;
	}

	TDAV_PRODUCER_AUDIO(dsound)->channels = codec->plugin->audio.channels;
	TDAV_PRODUCER_AUDIO(dsound)->rate = codec->plugin->rate;

	/* Create capture device */
	if((hr = DirectSoundCaptureCreate(NULL, &dsound->device, NULL) != DS_OK)){
		tdav_win32_print_error("DirectSoundCaptureCreate", hr);
		return -3;
	}

	/* Creates the capture buffer */
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = TDAV_PRODUCER_AUDIO(dsound)->channels;
	wfx.nSamplesPerSec = TDAV_PRODUCER_AUDIO(dsound)->rate;
	wfx.wBitsPerSample = TDAV_PRODUCER_AUDIO(dsound)->bits_per_sample;
	wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample/8);
	wfx.nAvgBytesPerSec = (wfx.nSamplesPerSec * wfx.nBlockAlign);

	/* Average bytes (count) for each notification */
	dsound->bytes_per_notif = ((wfx.nAvgBytesPerSec * TDAV_PRODUCER_AUDIO(dsound)->ptime)/1000);

	dsbd.dwSize = sizeof(DSCBUFFERDESC);
	dsbd.dwBufferBytes = (TDAV_DSOUNS_PRODUCER_NOTIF_POS_COUNT * dsound->bytes_per_notif);
	dsbd.lpwfxFormat = &wfx;

	if((hr = IDirectSoundCapture_CreateCaptureBuffer(dsound->device, &dsbd, &dsound->captureBuffer, NULL)) != DS_OK){
		tdav_win32_print_error("IDirectSoundCapture_CreateCaptureBuffer", hr);
		return -4;
	}	

	return 0;
}