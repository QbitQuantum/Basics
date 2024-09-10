bool XAudio2SourceVoice::Init()
{
	if (!XAudio2CheckedCall(XAudio2Device::XAudio2->CreateSourceVoice(&m_Source, (WAVEFORMATEX*)m_wfx, 0, 2.0f, &m_Callback)))
	{
		ConsolePrintf(TEXT("Failed to create XAudio2 source voice."));
		return false;
	}

	UINT32 NumEffects = 0;

	// Create the reverb effect
	IUnknown* ReverbXAPO = nullptr;
	bool bReverbEnabled = (m_EffectFlags & ILLUSYNTH_FX_REVERB) ? true : false;
	if (!XAudio2CheckedCall(CreateFX(__uuidof(FXReverb), &ReverbXAPO)))
	{
		ConsolePrintf(TEXT("XAudio2: Failed to create reverb XAPO."));
		return false;
	}

	// Create the EQ effect
	IUnknown* EQ_XAPO = nullptr;
	bool bEQEnabled = (m_EffectFlags & ILLUSYNTH_FX_EQ) ? true : false;
	if (!XAudio2CheckedCall(CreateFX(__uuidof(FXEQ), &EQ_XAPO)))
	{
		ConsolePrintf(TEXT("XAudio2: Failed to create EQ XAPO."));
		return false;
	}

	// NOTE: The order of these effects must match the order in the
	// header file
	XAUDIO2_EFFECT_DESCRIPTOR EffectDescriptors[] = {
		{ ReverbXAPO, bReverbEnabled, 1 },
		{ EQ_XAPO, bEQEnabled, 1 }
	};

	XAUDIO2_EFFECT_CHAIN EffectChain;
	EffectChain.EffectCount = sizeof(EffectDescriptors) / sizeof(XAUDIO2_EFFECT_DESCRIPTOR);
	EffectChain.pEffectDescriptors = EffectDescriptors;

	if (!XAudio2CheckedCall(m_Source->SetEffectChain(&EffectChain)))
	{
		ConsolePrintf(TEXT("XAudio2: Failed to set effect chain on source voice."));
		return false;
	}

	m_bInitialized = true;

	ReverbXAPO->Release();
	EQ_XAPO->Release();

	return true;
}