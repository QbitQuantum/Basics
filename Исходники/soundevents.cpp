int SoundEvent::InitDirectSound(SoundLib soundlib)
{

//    LPDIRECTSOUND8  m_pDS;
    HRESULT hr;
//    LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;

	TRACESETUP("INITDIRECTSOUND");

	   // Create IDirectSound using the primary sound device
    hr = DirectSoundCreate8( NULL, &m_pDS, NULL );
    if (hr != DS_OK)
	{
	    TRACE ("ERROR DIRECTSOUNDCREATE")
		this->makeInvalid();
		return (false);
	}
		else TRACE("DIRECTSOUND CREATE OK");

    // Set DirectSound coop level
    hr = m_pDS->SetCooperativeLevel( GetActiveWindow() , DSSCL_PRIORITY ) ;
    if (hr != DS_OK)
	    TRACE ("ERROR DIRECTSOUND SET COOP")
	else TRACE("DIRECTSOUND SETCOOP OK");

    // Get the primary buffer
    DSBUFFERDESC dsbd;
    ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
    dsbd.dwSize        = sizeof(DSBUFFERDESC);
    dsbd.dwFlags       = DSBCAPS_PRIMARYBUFFER;
    dsbd.dwBufferBytes = 0;
    dsbd.lpwfxFormat   = NULL;

    hr = m_pDS->CreateSoundBuffer( &dsbd, &pDSBPrimary, NULL );
    if (hr != DS_OK)
	    TRACE ("ERROR DIRECTSOUND CREATE SOUND BUFFER")
	else TRACE("DIRECTSOUND CREATE SOUND BUFFER OK");

    WAVEFORMATEX wfx;
    ZeroMemory( &wfx, sizeof(WAVEFORMATEX) );
    wfx.wFormatTag      = (WORD) WAVE_FORMAT_PCM;
    wfx.nChannels       = (WORD) 2;
    wfx.nSamplesPerSec  = (DWORD) 22050;
    wfx.wBitsPerSample  = (WORD) 16;
    wfx.nBlockAlign     = (WORD) (wfx.wBitsPerSample / 8 * wfx.nChannels);
    wfx.nAvgBytesPerSec = (DWORD) (wfx.nSamplesPerSec * wfx.nBlockAlign);

    hr = pDSBPrimary->SetFormat(&wfx);
    if (hr != DS_OK)
	    TRACE ("ERROR DIRECTSOUND SET FORMAT")
	else TRACE("DIRECTSOUND SET FORMAT OK");

    return(true);
}