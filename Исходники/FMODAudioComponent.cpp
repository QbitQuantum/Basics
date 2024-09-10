void UFMODAudioComponent::Play()
{
	Stop();

	if (!FMODUtils::IsWorldAudible(GetWorld()))
	{
		return;
	}

	UE_LOG(LogFMOD, Verbose, TEXT("UFMODAudioComponent %p Play"), this);
	
	// Only play events in PIE/game, not when placing them in the editor
	FMOD::Studio::EventDescription* EventDesc = IFMODStudioModule::Get().GetEventDescription(Event.Get());
	if (EventDesc != nullptr)
	{
		FMOD_RESULT result = EventDesc->createInstance(&StudioInstance);
		if (StudioInstance != nullptr)
		{
			FMOD_STUDIO_USER_PROPERTY UserProp = {0};
			if (EventDesc->getUserProperty("Ambient", &UserProp) == FMOD_OK)
			{
				if (UserProp.type == FMOD_STUDIO_USER_PROPERTY_TYPE_FLOAT) // All numbers are stored as float
				{
					bApplyAmbientVolumes = (UserProp.floatValue != 0.0f);
				}
			}
			OnUpdateTransform(true);
			// Set initial parameters
			for (auto Kvp : StoredParameters)
			{
				FMOD_RESULT Result = StudioInstance->setParameterValue(TCHAR_TO_UTF8(*Kvp.Key.ToString()), Kvp.Value);
				if (Result != FMOD_OK)
				{
					UE_LOG(LogFMOD, Warning, TEXT("Failed to set initial parameter %s"), *Kvp.Key.ToString());
				}
			}

			if (bEnableTimelineCallbacks)
			{
				verifyfmod(StudioInstance->setUserData(this));
				verifyfmod(StudioInstance->setCallback(UFMODAudioComponent_EventCallback));
			}
			verifyfmod(StudioInstance->start());
			UE_LOG(LogFMOD, Verbose, TEXT("Playing component %p"), this);
			bIsActive = true;
			SetComponentTickEnabled(true);
		}
	}
}