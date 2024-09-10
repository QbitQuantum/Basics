int AudioWaveOut::push_pcm_data(char* pbuf, int nlen)
{
	if (pbuf == NULL || nlen <= 0)
		return -1;
	if (!m_bInit && !bCanInPCM)
	{
		if (FailedCount++ >= 500)
		{
			FailedCount = 0;
			Log::writeMessage(LOG_RTSPSERV, 1, "waveout devicename %s 没有初始化成功 return!", WcharToAnsi(m_DeviceName.c_str()).c_str());
		}
		return -2;
	}
	MMRESULT mr = MMSYSERR_NOERROR;
	PWAVEPERIO hdr = m_wavequeue.front();
	if( hdr->hdr.dwFlags & WHDR_DONE || hdr->hdr.dwFlags == 0 )
	{
		mr = waveOutUnprepareHeader(m_outdev, &hdr->hdr, sizeof(WAVEHDR));
		if (mr != MMSYSERR_NOERROR)
			Log::writeMessage(LOG_RTSPSERV, 1, "waveOutUnprepareHeader ERROR devicename %s ", WcharToAnsi(m_DeviceName.c_str()).c_str());
	}
	else
	{
		Log::writeMessage(LOG_RTSPSERV, 1, "overrun reset devicename %s ", WcharToAnsi(m_DeviceName.c_str()).c_str());
		waveOutReset(m_outdev);
	}

	hdr->hdr.dwFlags = 0;
	hdr->hdr.dwUser = 0;
	if( nlen > MAX_SUPPORT_PCMPKG_LEN )
	{
		Log::writeMessage(LOG_RTSPSERV, 1, "PCM package len > MAX_SUPPORT_PCMPKG_LEN not play devicename %s ", WcharToAnsi(m_DeviceName.c_str()));
		return -5;
	}
	int dlen = nlen;
	if( m_bConver32t16 )
	{
		if( awresample( pbuf, nlen, (char*)hdr->buf, &dlen ) != 0 )
			Log::writeMessage(LOG_RTSPSERV, 1, "AudioWaveOut resample fail  devicename %s ", WcharToAnsi(m_DeviceName.c_str()));
	}
	else
		memcpy(hdr->buf, pbuf, nlen );
	hdr->hdr.lpData = (LPSTR)hdr->buf;
	hdr->hdr.dwBufferLength = dlen;

	mr = waveOutPrepareHeader(m_outdev, &hdr->hdr, sizeof(WAVEHDR));
	if (mr != MMSYSERR_NOERROR){
		if (FailedCount++ >= 100)
		{
			FailedCount = 0;
			Log::writeMessage(LOG_RTSPSERV, 1, "waveOutPrepareHeader fail devicename %s ", WcharToAnsi(m_DeviceName.c_str()).c_str());
			Uninitialize();
			Initialize(const_cast<TCHAR*>(m_DeviceName.c_str()), iChannels, iSamplerate, iSampleperbits);
		}
		return -3;
	}
	mr = waveOutWrite(m_outdev, &hdr->hdr, sizeof(WAVEHDR));
	if (mr != MMSYSERR_NOERROR){
		if (FailedCount++ >= 100)
		{
			FailedCount = 0;
			Log::writeMessage(LOG_RTSPSERV, 1, "waveOutWrite fail devicename %s ", WcharToAnsi(m_DeviceName.c_str()).c_str());
			Uninitialize();
			Initialize(const_cast<TCHAR*>(m_DeviceName.c_str()), iChannels, iSamplerate, iSampleperbits);
		}
		return -4;
	}
	m_wavequeue.pop();
	m_wavequeue.push(hdr);
	return 0;
}