bool SoundBuffersMG::Initialize(const HWND hWnd)
	{
	
	hr = DirectSoundCreate8(NULL, &pDSound, NULL);
	if( FAILED(hr) )
		return false;

	hr = pDSound->SetCooperativeLevel( hWnd, DSSCL_NORMAL);
	if( FAILED(hr) )
		return false;

	return true;
	}