static int
check_wave_format(Xcap_wasapi_param *wparam) {
	WAVEFORMATEX *pwfx = wparam->pwfx;
	WAVEFORMATEXTENSIBLE *ext = (WAVEFORMATEXTENSIBLE*) wparam->pwfx;
	//
	if(pwfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
		if(ext->SubFormat == KSDATAFORMAT_SUBTYPE_IEEE_FLOAT) {
			wparam->isFloat = 1;
		} else if(ext->SubFormat != KSDATAFORMAT_SUBTYPE_PCM) {
			OLECHAR *guidstr;
			char *in, *out, guid2[256];
			StringFromCLSID(ext->SubFormat, &guidstr);
			// because GUID is UTF-16LE?
			for(in = (char*) guidstr, out = guid2; *in; in += 2) {
				*out++ = *in;
			}
			*out = '\0';
			//
			ga_error("WAVEFORMATEXTENSIBLE: non-PCM is not supported (Format GUID=%s)\n", guid2);
			CoTaskMemFree(guidstr);
			return -1;
		}
	} else if(pwfx->wFormatTag != WAVE_FORMAT_PCM) {
		ga_error("WAVEFORMATEX: non-PCM is not supported\n");
		return -1;
	}
	if(pwfx->nChannels != 2) {
		ga_error("WAVEFORMATEX: channels = %d (!=2)\n",
			pwfx->nChannels);
		return -1;
	}
	ga_error("WAVEFORMATEX: samplerate=%d, bitspersample=%d\n",
		pwfx->nSamplesPerSec, pwfx->wBitsPerSample);
	//
	if(wparam->samplerate != pwfx->nSamplesPerSec) {
		ga_error("WAVEFORMATEX: audio sample rate mismatch (%d != %d)\n",
			wparam->samplerate,
			pwfx->nSamplesPerSec);
		return -1;
	}
	//
	if(wparam->isFloat) {
		if(wparam->bits_per_sample != 16) {
			ga_error("WAVEFORMATEX: [float] audio bits per sample mismatch (%d != 16)\n",
				wparam->bits_per_sample);
		}
	} else if(wparam->bits_per_sample != pwfx->wBitsPerSample) {
		ga_error("WAVEFORMATEX: audio bits per sample mismatch (%d != %d)\n",
			wparam->bits_per_sample,
			pwfx->wBitsPerSample);
		return -1;
	}
	return 0;
}