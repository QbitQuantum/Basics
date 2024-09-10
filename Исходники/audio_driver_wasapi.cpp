Error AudioDriverWASAPI::audio_device_init(AudioDeviceWASAPI *p_device, bool p_capture, bool reinit) {

	WAVEFORMATEX *pwfex;
	IMMDeviceEnumerator *enumerator = NULL;
	IMMDevice *device = NULL;

	CoInitialize(NULL);

	HRESULT hr = CoCreateInstance(CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, IID_IMMDeviceEnumerator, (void **)&enumerator);
	ERR_FAIL_COND_V(hr != S_OK, ERR_CANT_OPEN);

	if (p_device->device_name == "Default") {
		hr = enumerator->GetDefaultAudioEndpoint(p_capture ? eCapture : eRender, eConsole, &device);
	} else {
		IMMDeviceCollection *devices = NULL;

		hr = enumerator->EnumAudioEndpoints(p_capture ? eCapture : eRender, DEVICE_STATE_ACTIVE, &devices);
		ERR_FAIL_COND_V(hr != S_OK, ERR_CANT_OPEN);

		LPWSTR strId = NULL;
		bool found = false;

		UINT count = 0;
		hr = devices->GetCount(&count);
		ERR_FAIL_COND_V(hr != S_OK, ERR_CANT_OPEN);

		for (ULONG i = 0; i < count && !found; i++) {
			IMMDevice *device = NULL;

			hr = devices->Item(i, &device);
			ERR_BREAK(hr != S_OK);

			IPropertyStore *props = NULL;
			hr = device->OpenPropertyStore(STGM_READ, &props);
			ERR_BREAK(hr != S_OK);

			PROPVARIANT propvar;
			PropVariantInit(&propvar);

			hr = props->GetValue(PKEY_Device_FriendlyName, &propvar);
			ERR_BREAK(hr != S_OK);

			if (p_device->device_name == String(propvar.pwszVal)) {
				hr = device->GetId(&strId);
				ERR_BREAK(hr != S_OK);

				found = true;
			}

			PropVariantClear(&propvar);
			props->Release();
			device->Release();
		}

		if (found) {
			hr = enumerator->GetDevice(strId, &device);
		}

		if (strId) {
			CoTaskMemFree(strId);
		}

		if (device == NULL) {
			hr = enumerator->GetDefaultAudioEndpoint(p_capture ? eCapture : eRender, eConsole, &device);
		}
	}

	if (reinit) {
		// In case we're trying to re-initialize the device prevent throwing this error on the console,
		// otherwise if there is currently no device available this will spam the console.
		if (hr != S_OK) {
			return ERR_CANT_OPEN;
		}
	} else {
		ERR_FAIL_COND_V(hr != S_OK, ERR_CANT_OPEN);
	}

	hr = enumerator->RegisterEndpointNotificationCallback(&notif_client);
	SAFE_RELEASE(enumerator)

	if (hr != S_OK) {
		ERR_PRINT("WASAPI: RegisterEndpointNotificationCallback error");
	}

	hr = device->Activate(IID_IAudioClient, CLSCTX_ALL, NULL, (void **)&p_device->audio_client);
	SAFE_RELEASE(device)

	if (reinit) {
		if (hr != S_OK) {
			return ERR_CANT_OPEN;
		}
	} else {
		ERR_FAIL_COND_V(hr != S_OK, ERR_CANT_OPEN);
	}

	hr = p_device->audio_client->GetMixFormat(&pwfex);
	ERR_FAIL_COND_V(hr != S_OK, ERR_CANT_OPEN);

	// Since we're using WASAPI Shared Mode we can't control any of these, we just tag along
	p_device->channels = pwfex->nChannels;
	p_device->format_tag = pwfex->wFormatTag;
	p_device->bits_per_sample = pwfex->wBitsPerSample;
	p_device->frame_size = (p_device->bits_per_sample / 8) * p_device->channels;

	if (p_device->format_tag == WAVE_FORMAT_EXTENSIBLE) {
		WAVEFORMATEXTENSIBLE *wfex = (WAVEFORMATEXTENSIBLE *)pwfex;

		if (wfex->SubFormat == KSDATAFORMAT_SUBTYPE_PCM) {
			p_device->format_tag = WAVE_FORMAT_PCM;
		} else if (wfex->SubFormat == KSDATAFORMAT_SUBTYPE_IEEE_FLOAT) {
			p_device->format_tag = WAVE_FORMAT_IEEE_FLOAT;
		} else {
			ERR_PRINT("WASAPI: Format not supported");
			ERR_FAIL_V(ERR_CANT_OPEN);
		}
	} else {
		if (p_device->format_tag != WAVE_FORMAT_PCM && p_device->format_tag != WAVE_FORMAT_IEEE_FLOAT) {
			ERR_PRINT("WASAPI: Format not supported");
			ERR_FAIL_V(ERR_CANT_OPEN);
		}
	}

	DWORD streamflags = 0;
	if (mix_rate != pwfex->nSamplesPerSec) {
		streamflags |= AUDCLNT_STREAMFLAGS_RATEADJUST;
		pwfex->nSamplesPerSec = mix_rate;
		pwfex->nAvgBytesPerSec = pwfex->nSamplesPerSec * pwfex->nChannels * (pwfex->wBitsPerSample / 8);
	}

	hr = p_device->audio_client->Initialize(AUDCLNT_SHAREMODE_SHARED, streamflags, p_capture ? REFTIMES_PER_SEC : 0, 0, pwfex, NULL);
	ERR_FAIL_COND_V(hr != S_OK, ERR_CANT_OPEN);

	if (p_capture) {
		hr = p_device->audio_client->GetService(IID_IAudioCaptureClient, (void **)&p_device->capture_client);
	} else {
		hr = p_device->audio_client->GetService(IID_IAudioRenderClient, (void **)&p_device->render_client);
	}
	ERR_FAIL_COND_V(hr != S_OK, ERR_CANT_OPEN);

	// Free memory
	CoTaskMemFree(pwfex);
	SAFE_RELEASE(device)

	return OK;
}