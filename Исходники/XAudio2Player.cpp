XAudio2Player::XAudio2Player(IXAudio2* pxa, int &status)
{
	
	currentBufferNumber = 0;
	
	pXAudio2 = pxa;
	
	HRESULT hr;
	if( FAILED(hr = XAudio2Create( &pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR ) ) )
		status = SA_XAUDIO2_ERROR;
	IXAudio2MasteringVoice* pMasterVoice = NULL;
	if ( FAILED(hr = pXAudio2->CreateMasteringVoice( &pMasterVoice ) ) )
		status = SA_XAUDIO2_ERROR;

	wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 2;
    wf.nSamplesPerSec = 44100;
    wf.nAvgBytesPerSec = 44100 * 4;
    wf.nBlockAlign = 4;
    wf.wBitsPerSample = 16;
    wf.cbSize = 0;

	if( FAILED(hr = pXAudio2->CreateSourceVoice( &pSourceVoice, &wf, 0, 1.0f, &voiceContext ) ) ) 
		status = SA_XAUDIO2_ERROR;
	if ( FAILED(hr = pSourceVoice->Start( 0, 0 ) ) )
		status = SA_XAUDIO2_ERROR;
	
	doUpdate = true;

	t = std::thread(&XAudio2Player::Play, this);
	
}