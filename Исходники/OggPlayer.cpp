bool OggPlayer::InitDirectSound( HWND hWnd )
{
	HRESULT hr;
	
	if (FAILED(hr = DirectSoundCreate8(NULL, &pDS, NULL)))
        return bInitialized = false;

	pDS->Initialize(NULL);
	pDS->SetCooperativeLevel( hWnd, DSSCL_PRIORITY );

    bReleaseDS = true;

    return bInitialized = true;
}