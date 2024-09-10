VOID CSoundRecDlg::StartRecording()
{	
	MMRESULT mRes;
	SetStatus("Recording...");

	try
	{
		OpenDevice();
		PrepareBuffers();
		mRes=waveInStart(m_hWaveIn);
		if(mRes!=0)
		{
			StoreError(mRes,FALSE,"File: %s ,Line Number:%d",__FILE__,__LINE__);
			throw m_csErrorText;
		}
		while(m_bRun)
		{
			SleepEx(100,FALSE);
		}
	}
	catch(PCHAR pErrorMsg)
	{
		AfxMessageBox(pErrorMsg);
	}
	CloseDevice();
	CloseHandle(m_hThread);
	m_hThread=NULL;
	SetStatus("Recording stopped...");
}