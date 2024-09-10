BOOL CMixOut::OpenMixer()
{
	m_iDevNum = mixerGetNumDevs();
	if (m_iDevNum == 0)
	{
		TRACE("There (is) are no device mixer.\n");
		return FALSE;
	}

	WAVEFORMATEX wfx;
	memset( &wfx, 0, sizeof(WAVEFORMATEX) );
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = 8000;
	wfx.nAvgBytesPerSec = 1 * 8000 * 16 / 8;
	wfx.nBlockAlign = 16 * 1 / 8;
	wfx.wBitsPerSample = 16;
	wfx.cbSize = 0;

	HWAVEOUT hwaveOut;
	m_mmr = waveOutOpen( &hwaveOut, WAVE_MAPPER, &wfx, 0L, 0L, CALLBACK_NULL );
	if ( m_mmr != MMSYSERR_NOERROR )
	{
		return false;
	}
	else
	{
		m_mmr = mixerGetID( (HMIXEROBJ)hwaveOut, &m_uiMixerId, MIXER_OBJECTF_HWAVEOUT );
		waveOutClose( hwaveOut );
		if (m_mmr != MMSYSERR_NOERROR )
		{
			return false;
		}
	}

	WNDCLASSEX wcx;
	memset( &wcx, 0, sizeof(WNDCLASSEX) );	
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.lpszClassName = WND_CLASS_NAME;
	wcx.lpfnWndProc = (WNDPROC)MixerWndProc;
	::RegisterClassEx(&wcx);
	m_hWnd = CreateWindow(	WND_CLASS_NAME,
							WND_NAME,
							WS_POPUP | WS_DISABLED,
							0, 0, 0, 0,
							NULL, NULL, NULL, NULL );
	if ( !m_hWnd )
	{
	
		return false;
	}
	::ShowWindow(m_hWnd, SW_HIDE);
	m_mmr = mixerOpen( (LPHMIXER)&m_hMixer, m_uiMixerId, (DWORD)m_hWnd, 0L, CALLBACK_WINDOW );
	if (m_mmr != MMSYSERR_NOERROR )
	{
		::DestroyWindow( m_hWnd );
		return false;
	}
	return true;
}