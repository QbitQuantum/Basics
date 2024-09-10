bool XAudio2_7::Start()
{
	HRESULT hr;

	// callback doesn't seem to run on a specific cpu anyways
	IXAudio2* xaudptr;
	if (FAILED(hr = XAudio2Create(&xaudptr, 0, XAUDIO2_DEFAULT_PROCESSOR)))
	{
		PanicAlertT("XAudio2_7 init failed: %#X", hr);
		Stop();
		return false;
	}
	m_xaudio2 = std::unique_ptr<IXAudio2, Releaser>(xaudptr);

	// XAudio2 master voice
	// XAUDIO2_DEFAULT_CHANNELS instead of 2 for expansion?
	if (FAILED(hr = m_xaudio2->CreateMasteringVoice(&m_mastering_voice, 2, m_mixer->GetSampleRate())))
	{
		PanicAlertT("XAudio2_7 master voice creation failed: %#X", hr);
		Stop();
		return false;
	}

	// Volume
	m_mastering_voice->SetVolume(m_volume);

	m_voice_context = std::unique_ptr<StreamingVoiceContext2_7>
		(new StreamingVoiceContext2_7(m_xaudio2.get(), m_mixer, m_sound_sync_event));

	return true;
}