void CALLBACK CAudioCapture::waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, 
										DWORD dwParam1, DWORD dwParam2)
{
	CAudioCapture* pObj = (CAudioCapture*)dwInstance;
	DWORD dwBytesWritten = 0;

	if(hwi != NULL)
	{
	    if(uMsg == WIM_DATA)
		{
//			RETAILMSG(1, (L"WAV: WaveIn Data.. time %u \n", GetTickCount()));
			if(pObj->m_bUseBufferA == TRUE)
			{
				if (pObj->m_waveHdrA.dwBytesRecorded > 0)
				{
					WriteFile(pObj->m_hFile, pObj->m_waveHdrA.lpData, pObj->m_waveHdrA.dwBytesRecorded, &dwBytesWritten, NULL);
					pObj->m_waveHdrA.dwBytesRecorded = 0;
					waveInAddBuffer(pObj->m_hWaveIn, &pObj->m_waveHdrA, sizeof(WAVEHDR));
				}
				pObj->m_bUseBufferA = FALSE;
			}
			else 
			{
				if (pObj->m_waveHdrB.dwBytesRecorded > 0)
				{
					WriteFile(pObj->m_hFile, pObj->m_waveHdrB.lpData, pObj->m_waveHdrB.dwBytesRecorded, &dwBytesWritten, NULL);
					pObj->m_waveHdrB.dwBytesRecorded = 0;
					waveInAddBuffer(pObj->m_hWaveIn, &pObj->m_waveHdrB, sizeof(WAVEHDR));
				}
				pObj->m_bUseBufferA = TRUE;
			}
			pObj->m_ulCapturedBytes += dwBytesWritten;
			if (pObj->m_ulCapturedBytes >= pObj->m_iMaxFileSizeBytes)
				pObj->Stop();
		}
		else if(uMsg == WIM_OPEN)
		{
			OutputDebugStringW(L"WAV: WaveIn device open..\n");
		}
		else if(uMsg == WIM_CLOSE)
		{
			OutputDebugStringW(L"WAV: WaveIn device closed..\n");
		}
	}
}