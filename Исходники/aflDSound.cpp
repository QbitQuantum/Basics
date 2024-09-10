bool SoundRecoder::createBuffer(LPGUID guid)
{
	//デバイスの作成
	HMODULE library = LoadLibraryA("dsound.dll");
	if(!library)
		return false;

	HRESULT (WINAPI *DirectSoundCaptureCreate8)(LPCGUID,LPDIRECTSOUNDCAPTURE8*,LPUNKNOWN) =
		(HRESULT (WINAPI *)(LPCGUID,LPDIRECTSOUNDCAPTURE8*,LPUNKNOWN))
		GetProcAddress(library,"DirectSoundCaptureCreate8");

	DirectSoundCaptureCreate8(guid,&m_soundCapture,NULL);

	FreeLibrary(library);

	//デバイスが作成できなかったら終了
	if(!m_soundCapture)
		return false;

	if(m_soundCaptureBuffer)
	{
		m_soundCaptureBuffer->Release();
		m_soundCaptureBuffer = NULL;
	}
	DSCBUFFERDESC dscbd;
	WAVEFORMATEX wfx = 
	{
		WAVE_FORMAT_PCM,
		m_bufferChannel,
		m_bufferRate,
		m_bufferRate*m_bufferChannel*m_bufferBit/8,
		m_bufferChannel*m_bufferBit/8,
		m_bufferBit, 0
	};

	m_bufferSize =  wfx.nAvgBytesPerSec*m_bufferMSec/1000;

	dscbd.dwSize = sizeof(DSCBUFFERDESC);
	dscbd.dwFlags = 0;
	dscbd.dwBufferBytes = m_bufferSize;
	dscbd.dwReserved = 0;
	dscbd.lpwfxFormat = &wfx;
	dscbd.dwFXCount = 0;
	dscbd.lpDSCFXDesc = NULL;
	
	m_latency = m_bufferSize / m_notifyCount;


	LPDIRECTSOUNDCAPTUREBUFFER soundBuffer = NULL;
	m_soundCapture->CreateCaptureBuffer(&dscbd, &soundBuffer, NULL);
	if(!soundBuffer)
		return false;
	soundBuffer->QueryInterface(IID_IDirectSoundCaptureBuffer8,(LPVOID*)&m_soundCaptureBuffer);
	soundBuffer->Release();

	if(!m_soundCaptureBuffer)
		return false;

	INT i;
	for(i=0;i<m_notifyCount;i++)
	{
		m_positionNotify[i].dwOffset = (dscbd.dwBufferBytes /m_notifyCount)*i ;
	}

	LPDIRECTSOUNDNOTIFY8 dsNotify;
	m_soundCaptureBuffer->QueryInterface(IID_IDirectSoundNotify, (LPVOID*)&dsNotify);
	dsNotify->SetNotificationPositions(m_notifyCount, m_positionNotify);
	dsNotify->Release();

	return true;
}