HRESULT CBSoundAVI::InitializeBuffer(PAVISTREAM Stream)
{
	if(!Stream) return E_FAIL;

	SetStreaming(true);
	m_Type = SOUND_SFX;
	m_Looping = false;

	m_AudioStream = Stream;

	LONG FormatSize;
	if(AVIStreamReadFormat(m_AudioStream, 0, NULL, &FormatSize)!=0) return E_FAIL;

	LPWAVEFORMAT Format = (LPWAVEFORMAT)new BYTE[FormatSize];
	if(AVIStreamReadFormat(m_AudioStream, 0, Format, &FormatSize)!=0){
		delete [] (BYTE*)Format;
		return E_FAIL;
	}
	
	m_TotalDataLength = AVIStreamLength(m_AudioStream) * Format->nBlockAlign;


	HRESULT ret;

	memcpy(&m_Format, Format, sizeof(PCMWAVEFORMAT));
	m_Format.wf.wFormatTag = WAVE_FORMAT_PCM;
	
	// create buffer
	ret = CreateSoundBuffer(m_TotalDataLength, (PCMWAVEFORMAT*)Format);

	
	delete [] (BYTE*)Format;

	return ret;
}