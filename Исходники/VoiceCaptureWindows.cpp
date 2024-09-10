bool FVoiceCaptureWindows::Init(int32 SampleRate, int32 NumChannels)
{
	if (SampleRate < 8000 || SampleRate > 48000)
	{
		UE_LOG(LogVoice, Warning, TEXT("Voice capture doesn't support %d hz"), SampleRate);
		return false;
	}

	if (NumChannels < 0 || NumChannels > 2)
	{
		UE_LOG(LogVoice, Warning, TEXT("Voice capture only supports 1 or 2 channels"));
		return false;
	}

	// @todo move this to voice module (only init/deinit once ever)
	if (FAILED(DirectSoundCreate8(NULL, &DirectSound, NULL)))
	{
		UE_LOG(LogVoice, Warning, TEXT("Failed to init DirectSound"));
		return false;
	}

	if (FAILED(DirectSoundCaptureEnumerate((LPDSENUMCALLBACK)CaptureDeviceCallback, this)))
	{
		UE_LOG(LogVoice, Warning, TEXT("Failed to enumerate devices"));
		return false;
	}

	// DSDEVID_DefaultCapture WAVEINCAPS 
	if (FAILED(DirectSoundCaptureCreate8(&DSDEVID_DefaultVoiceCapture, &VoiceCaptureDev, NULL)))
	{
		UE_LOG(LogVoice, Warning, TEXT("Failed to create capture device"));
		return false;
	}

	// Device capabilities
	VoiceCaptureDevCaps.dwSize = sizeof(DSCCAPS);
	if (FAILED(VoiceCaptureDev->GetCaps(&VoiceCaptureDevCaps)))
	{
		UE_LOG(LogVoice, Warning, TEXT("Failed to get mic device caps"));
		return false;
	}

	// Wave format setup
	WavFormat.wFormatTag = WAVE_FORMAT_PCM;
	WavFormat.nChannels = NumChannels;
	WavFormat.wBitsPerSample = 16;
	WavFormat.nSamplesPerSec = SampleRate;
	WavFormat.nBlockAlign = (WavFormat.nChannels * WavFormat.wBitsPerSample) / 8;
	WavFormat.nAvgBytesPerSec = WavFormat.nBlockAlign * WavFormat.nSamplesPerSec;
	WavFormat.cbSize = 0;

	// Buffer setup
	VoiceCaptureBufferDesc.dwSize = sizeof(DSCBUFFERDESC);
	VoiceCaptureBufferDesc.dwFlags = 0;
	VoiceCaptureBufferDesc.dwBufferBytes = WavFormat.nAvgBytesPerSec / 2; // .5 sec buffer
	VoiceCaptureBufferDesc.dwReserved = 0;
	VoiceCaptureBufferDesc.lpwfxFormat = &WavFormat;
	VoiceCaptureBufferDesc.dwFXCount = 0;
	VoiceCaptureBufferDesc.lpDSCFXDesc = NULL;

	LPDIRECTSOUNDCAPTUREBUFFER VoiceBuffer = NULL;
	if (FAILED(VoiceCaptureDev->CreateCaptureBuffer(&VoiceCaptureBufferDesc, &VoiceBuffer, NULL)))
	{
		UE_LOG(LogVoice, Warning, TEXT("Failed to create voice capture buffer"));
		return false;
	}

	HRESULT BufferCreateHR = VoiceBuffer->QueryInterface(IID_IDirectSoundCaptureBuffer8, (LPVOID*)&VoiceCaptureBuffer8);
	VoiceBuffer->Release(); 
	VoiceBuffer = NULL;
	if (FAILED(BufferCreateHR))
	{
		UE_LOG(LogVoice, Warning, TEXT("Failed to create voice capture buffer"));
		return false;
	}

	VoiceCaptureBufferCaps8.dwSize = sizeof(DSCBCAPS);
	if (FAILED(VoiceCaptureBuffer8->GetCaps(&VoiceCaptureBufferCaps8)))
	{
		UE_LOG(LogVoice, Warning, TEXT("Failed to get voice buffer caps"));
		return false;
	}

	// TEST ------------------------
	if (0)
	{
		DWORD SizeWritten8 = 0;
		VoiceCaptureBuffer8->GetFormat(NULL, sizeof(WAVEFORMATEX), &SizeWritten8);

		LPWAVEFORMATEX BufferFormat8 = (WAVEFORMATEX*)FMemory::Malloc(SizeWritten8);
		VoiceCaptureBuffer8->GetFormat(BufferFormat8, SizeWritten8, &SizeWritten8);
		FMemory::Free(BufferFormat8);
	}
	// TEST ------------------------

	if (!CreateNotifications(VoiceCaptureBufferCaps8.dwBufferBytes))
	{
		UE_LOG(LogVoice, Warning, TEXT("Failed to create voice buffer notifications"));
		return false;
	}

	VoiceCaptureState = EVoiceCaptureState::NotCapturing;
	return true;
}