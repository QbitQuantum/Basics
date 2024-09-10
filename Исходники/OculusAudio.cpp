	void Initialize() override
	{
		if (FOculusAudioPlugin::NumInstances == 0)
		{
			if (!LoadModule())
			{
				UE_LOG(LogAudio, Error, TEXT("Failed to load OVR Audio dll"));
				return;
			}
		}

		FOculusAudioPlugin::NumInstances++;

		if (!FOculusAudioPlugin::bInitialized)
		{
			// Check the version number
			int32 MajorVersionNumber;
			int32 MinorVersionNumber;
			int32 PatchNumber;

			// Initialize the OVR Audio SDK before making any calls to ovrAudio
			ovrResult Result = ovrAudio_Initialize();
			OVR_AUDIO_CHECK(Result, "Failed to initialize OVR Audio system");

			const char* OvrVersionString = ovrAudio_GetVersion(&MajorVersionNumber, &MinorVersionNumber, &PatchNumber);
			if (MajorVersionNumber != OVR_AUDIO_MAJOR_VERSION || MinorVersionNumber != OVR_AUDIO_MINOR_VERSION)
			{
				UE_LOG(LogAudio, Warning, TEXT("Using mismatched OVR Audio SDK Versiont! %d.%d vs. %d.%d"), OVR_AUDIO_MAJOR_VERSION, OVR_AUDIO_MINOR_VERSION, MajorVersionNumber, MinorVersionNumber);
				return;
			}
			FOculusAudioPlugin::bInitialized = true;
		}
	}