bool FVoiceCaptureDeviceWindows::Init()
{
	HRESULT hr = DirectSoundCreate8(NULL, &DirectSound, NULL);
	if (FAILED(hr))
	{
		UE_LOG(LogVoiceCapture, Warning, TEXT("Failed to init DirectSound %d"), hr);
		return false;
	}

	bool bHmdAvailable = IModularFeatures::Get().IsModularFeatureAvailable(IHeadMountedDisplayModule::GetModularFeatureName());
	HmdVoiceCaptureDeviceIndex = bHmdAvailable ? CVarHmdDirectSoundVoiceCaptureDeviceIndex.GetValueOnGameThread() : -1;
	VoiceCaptureDeviceCount = 0;
	VoiceCaptureDeviceGuid = DSDEVID_DefaultVoiceCapture;

	hr = DirectSoundCaptureEnumerate((LPDSENUMCALLBACK)CaptureDeviceCallback, this);
	if (FAILED(hr))
	{
		UE_LOG(LogVoiceCapture, Warning, TEXT("Failed to enumerate capture devices %d"), hr);
		return false;
	}

	bool bDuckingOptOut = false;
	if (GConfig)
	{
		if (!GConfig->GetBool(TEXT("Voice"), TEXT("bDuckingOptOut"), bDuckingOptOut, GEngineIni))
		{
			bDuckingOptOut = false;
		}
	}
	FAudioDuckingWindows::UpdateAudioDucking(bDuckingOptOut);

	bInitialized = true;
	return true;
}