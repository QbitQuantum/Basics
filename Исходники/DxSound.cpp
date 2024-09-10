LPDIRECTSOUND CDXSound::Create( HWND hwnd, DWORD dwLevel )
{
	HRESULT hr;

	m_hWnd = hwnd;
	m_lpDS = NULL;
	
	hr = DirectSoundCreate( NULL, &m_lpDS, NULL );
	if( hr != DS_OK )
		return m_lpDS;

	hr = m_lpDS->SetCooperativeLevel( hwnd, dwLevel );//DSSCL_NORMAL );
	if ( hr != DS_OK ) 
	{
		m_lpDS->Release();
		m_lpDS = NULL;
	}
	else if ( !CreateBuffer() )
	{
		DestroyBuffer();
		m_lpDS->Release();
		m_lpDS = NULL;
	}
	return m_lpDS;
}