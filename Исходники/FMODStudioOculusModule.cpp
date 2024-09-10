void FFMODStudioOculusModule::OnInitialize()
{
	UE_LOG(LogFMODOculus, Verbose, TEXT("OnInitialize"));

#if FMOD_OSP_SUPPORTED
	const UFMODOculusSettings& Settings = *GetDefault<UFMODOculusSettings>();
	if (!Settings.bOculusEnabled)
	{
		UE_LOG(LogFMODOculus, Verbose, TEXT("bOculusEnabled is false - skipping init"));
		return;
	}

	FMOD::Studio::System* StudioSystem = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);
	if (!StudioSystem)
	{
		UE_LOG(LogFMODOculus, Log, TEXT("StudioSystem is null - skipping init"));
		return;
	}

	if (!IFMODStudioModule::Get().LoadPlugin(TEXT("ovrfmod")))
	{
		UE_LOG(LogFMODOculus, Log, TEXT("ovrfmod failed to load - skipping init"));

		return;
	}

	UE_LOG(LogFMODOculus, Log, TEXT("Initialising OSP"));

	FMOD::System* LowLevelSystem = nullptr;
	verifyfmod(StudioSystem->getLowLevelSystem(&LowLevelSystem));
	if (LowLevelSystem)
	{
		int SampleRate = 0;
		unsigned int BufferSize = 0;
		verifyfmod(LowLevelSystem->getSoftwareFormat(&SampleRate, nullptr, nullptr));
		verifyfmod(LowLevelSystem->getDSPBufferSize(&BufferSize, nullptr));
		int returncode = OSP_FMOD_Initialize(SampleRate, BufferSize);
		if (returncode == 0)
		{
			bRunning = true;
			// Unreal units are per cm, but our plugin converts everything to metres when calling into Studio
			OSP_FMOD_SetGlobalScale(1.0f);
			UFMODOculusBlueprintStatics::SetEarlyReflectionsEnabled(Settings.bEarlyReflectionsEnabled);
			UFMODOculusBlueprintStatics::SetLateReverberationEnabled(Settings.bLateReverberationEnabled);
			UFMODOculusBlueprintStatics::SetRoomParameters(Settings.RoomParameters);
			UE_LOG(LogFMODOculus, Log, TEXT("OSP_FMOD_Initialize returned success - running with Oculus plugin enabled"));
		}
		else
		{
			UE_LOG(LogFMODOculus, Error, TEXT("OSP_FMOD_Initialize returned error %s"), returncode);
		}
	}
#else
	UE_LOG(LogFMODOculus, Log, TEXT("FMOD_OSP_SUPPORTED is not enabled"));
#endif
}