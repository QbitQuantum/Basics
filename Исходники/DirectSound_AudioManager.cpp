	DirectSound_AudioManager::DirectSound_AudioManager(void* backendId, bool threaded, float updateTime, chstr deviceName) :
		AudioManager(backendId, threaded, updateTime, deviceName)
	{
		this->name = XAL_AS_DIRECTSOUND;
		hlog::write(xal::logTag, "Initializing DirectSound.");
		HRESULT result = DirectSoundCreate(NULL, &this->dsDevice, NULL);
		if (FAILED(result))
		{
			this->dsDevice = NULL;
			hlog::error(xal::logTag, "Could not create device!");
			return;
		}
		result = this->dsDevice->SetCooperativeLevel((HWND)backendId, DSSCL_NORMAL);
		if (FAILED(result))
		{
			this->dsDevice->Release();
			this->dsDevice = NULL;
			hlog::error(xal::logTag, "Could not set cooperative level!");
			return;
		}
		this->dsCaps = new _DSCAPS();
		memset(this->dsCaps, 0, sizeof(_DSCAPS));
		this->dsCaps->dwSize = sizeof(_DSCAPS);
		result = this->dsDevice->GetCaps(this->dsCaps);
		if (result != DS_OK)
		{
			this->dsCaps->dwMaxSecondarySampleRate = 100000; // just in case. 100k is guaranteed to be always supported on all DS hardware
			hlog::error(xal::logTag, "Failed fetching DirectSound device caps");
		}
		else
		{
			hlog::writef(xal::logTag, "DirectSound device caps: { maxSampleRate = %u }", this->dsCaps->dwMaxSecondarySampleRate);
		}
		this->enabled = true;
	}