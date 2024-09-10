HRESULT FrkSound::InitializeSoundClass(HWND windowsHandler)
{
	m_hWindowsHandler = windowsHandler;

	HRESULT result;
	// Thu tao thiet bi DS
	result = DirectSoundCreate8(0, &m_hAudioHandler, 0);
	result = result | m_hAudioHandler->SetCooperativeLevel(m_hWindowsHandler, DSSCL_PRIORITY);

	ZeroMemory(&m_hBufferFormat, sizeof(WAVEFORMATEX));
	ZeroMemory(&m_hBufferDescription, sizeof(DSBUFFERDESC));

	m_hBufferFormat.wFormatTag = AUDIO_FORMAT_TAG;
	m_hBufferFormat.nChannels = AUDIO_NUM_OF_CHANNEL;
	m_hBufferFormat.nSamplesPerSec = AUDIO_SAMPLE_SPEED;
	m_hBufferFormat.wBitsPerSample = AUDIO_BITS_PER_SAMPLE;
	m_hBufferFormat.nBlockAlign = AUDIO_BLOCK_ALIGN(m_hBufferFormat.wBitsPerSample,
		m_hBufferFormat.nChannels);
	m_hBufferFormat.nAvgBytesPerSec = AUDIO_AVERAGE_BPS(m_hBufferFormat.nSamplesPerSec,
		m_hBufferFormat.nBlockAlign);

	m_hBufferDescription.dwFlags = AUDIO_FLAGS;
	m_hBufferDescription.guid3DAlgorithm = AUDIO_GUID;
	m_hBufferDescription.dwSize = sizeof(DSBUFFERDESC);

	return result;
}