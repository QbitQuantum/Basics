// Initialisation of the CXAudio2 engine
void CXAudio2::Init(const CXAudio2SetupParameters& params)
{
	// Copy parameters
	numChannels = params.numChannels;
	maxFrequencyRatio = params.maxFrequencyRatio;
	SetCommandBatching(params.commandBatching);
	SetCacheMode(params.cacheMode);
	SetCacheLimit(params.cacheLimit);

	// Initialize COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

#ifdef _DEBUG
	// Request debug XAudio2 engine
	hr = XAudio2Create(&pXAudio2, XAUDIO2_DEBUG_ENGINE,	XAUDIO2_DEFAULT_PROCESSOR);
#else
	// Request standard XAudio2 engine
	hr = XAudio2Create(&pXAudio2, 0,					XAUDIO2_DEFAULT_PROCESSOR);
#endif

	// XAudio2Create failed
	if (FAILED(hr))
		throw CXAudio2Error(hr, "Failed to create XAudio2");

	// Mastering limiter & volume meter effect chain for mastering voice
	XAUDIO2_EFFECT_DESCRIPTOR descriptor[2];
	int count = 0;

	// Create the mastering limiter if enabled
	if (params.limiter_enable) {
		IUnknown* pLimiter;
		hr = CreateFX(__uuidof(FXMasteringLimiter), &pLimiter);

		if (FAILED(hr))
			throw CXAudio2Error(hr, "Failed to create mastering limiter");

		descriptor[0].InitialState = true;
		descriptor[0].OutputChannels = 2;
		descriptor[0].pEffect = pLimiter;

		// Write volume meter to next descriptor
		count++;
	}

	// Create the volume meter for the mastering voice
#ifdef _DEBUG
	hr = XAudio2CreateVolumeMeter(&(master.pVolumeMeter), XAUDIO2FX_DEBUG);
#else
	hr = XAudio2CreateVolumeMeter(&(master.pVolumeMeter), 0);
#endif

	if (FAILED(hr))
		throw CXAudio2Error(hr, "Failed to create XAudio2 volume meter");

	// Set up the effect chain to apply the volume metering to the mastering voice
	descriptor[count].InitialState = true;
	descriptor[count].OutputChannels = 2;
	descriptor[count].pEffect = master.pVolumeMeter;
	master.volumeMeterEffectIndex = count;
	count++;

	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = count;
	chain.pEffectDescriptors = descriptor;

	// Create stereo mastering voice
	hr = pXAudio2->CreateMasteringVoice(&(master.pMaster), 2, XAUDIO2_DEFAULT_SAMPLERATE, 
										0, 0, &chain);

	if (FAILED(hr))
		throw CXAudio2Error(hr, "Failed to create XAudio2 mastering voice");

	// Get the device details
	pXAudio2->GetDeviceDetails(0, &deviceDetails);

	// Set up the channel strip
	channels.reserve(numChannels);

	for (int i = 0; i < numChannels; i++)
		channels.push_back(Channel(this, i));

	// Set the master volume as per parameters; -3.0dB by default to help prevent clipping
	master.SetVolume(params.masterGain);
}