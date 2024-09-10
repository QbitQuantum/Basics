XAudio2Thread::XAudio2Thread()
	: m_xaudio2_instance(nullptr)
	, m_master_voice(nullptr)
	, m_source_voice(nullptr)
{
	HRESULT hr = S_OK;

	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		LOG_ERROR(GENERAL, "XAudio2Thread : CoInitializeEx() failed(0x%08x)", (u32)hr);
		Emu.Pause();
		return;
	}

	hr = XAudio2Create(&m_xaudio2_instance, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr))
	{
		LOG_ERROR(GENERAL, "XAudio2Thread : XAudio2Create() failed(0x%08x)", (u32)hr);
		Emu.Pause();
		return;
	}

	hr = m_xaudio2_instance->CreateMasteringVoice(&m_master_voice);
	if (FAILED(hr))
	{
		LOG_ERROR(GENERAL, "XAudio2Thread : CreateMasteringVoice() failed(0x%08x)", (u32)hr);
		m_xaudio2_instance->Release();
		Emu.Pause();
	}
}