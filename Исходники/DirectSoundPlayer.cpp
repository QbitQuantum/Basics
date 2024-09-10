bool CDirectSoundPlayer::Stop()
{
    HRESULT hr;
	if(m_InitOK && m_AudioEnabled)
	{
		if(m_TimerID!=NULL) timeKillEvent(m_TimerID);
		hr=m_BufferSecondary->Stop();
		if(hr!=DS_OK)
		{
			CString message ("CDirectSoundPlayer::Stop - Error: \n");
			message += DXAppErrorToString (hr);
			gError->Warning(message);
		}

		hr=m_BufferSecondary->SetCurrentPosition(0);
		if(hr!=DS_OK)
		{
			CString message ("CDirectSoundPlayer::Stop - Error: \n");
			message += DXAppErrorToString (hr);
			gError->Warning(message);
		}
//		dbg.Close();
	}
	m_AudioEnabled=FALSE;
	return m_AudioEnabled;
}