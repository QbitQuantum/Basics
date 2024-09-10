BOOL CVolumeCtrl::Init()
{
	if (!mixerGetNumDevs())
	{
		return FALSE;
	}

	HWAVEIN hwaveIn;
	MMRESULT mmResult;
	WAVEFORMATEX WaveFmt;
	SetDeviceType( &WaveFmt );
	mmResult = waveInOpen(&hwaveIn, m_dwDeviceID, &WaveFmt, 0L, 0L, CALLBACK_NULL);
	if (mmResult != MMSYSERR_NOERROR)
	{
		return FALSE;
	}
	else
	{
		// 得到混响器的标识号
		mmResult = mixerGetID((HMIXEROBJ)hwaveIn, &m_uMixerID, MIXER_OBJECTF_HWAVEIN);
		waveInClose(hwaveIn);
		if (mmResult != MMSYSERR_NOERROR )
		{
			return FALSE;
		}
	}

	// Exposing Window to Mixer
	WNDCLASSEX wcx;
	memset( &wcx, 0, sizeof(WNDCLASSEX) );	
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.lpszClassName = WND_CLASS_NAME;
	wcx.lpfnWndProc = (WNDPROC)MixerWndProc;
	::RegisterClassEx(&wcx);
	m_hWnd = CreateWindow(WND_CLASS_NAME,
		                  WND_NAME, 
						  WS_POPUP | WS_DISABLED,
						  0, 0, 0, 0,
						  NULL, NULL, NULL, NULL );
	if (!m_hWnd)
	{
		return FALSE;
	}
	::ShowWindow(m_hWnd, SW_HIDE);
	::UpdateWindow(m_hWnd);

	//
	// 打开混响器设备
	// 参数:
	//      m_dwMixerHandle--混响器设备的句柄  
	//      m_uMixerID--为混响器的标识号,用于指定要打开的混响器设备
	//	
	mmResult = mixerOpen( (LPHMIXER)&m_dwMixerHandle, m_uMixerID, (DWORD)m_hWnd, 0L, CALLBACK_WINDOW );
	if (mmResult != MMSYSERR_NOERROR || m_uMixerID == -1)
	{
		::DestroyWindow( m_hWnd );
		return FALSE;
	}

	return TRUE;
}