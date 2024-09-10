	virtual DWORD OnStop()
	{
		if (hTimer != NULL)
		{
			DeleteTimerQueueTimer(NULL, hTimer, NULL);
			hTimer = NULL;
		}
		if (m_hOneInstance != NULL)
		{
			CloseHandle(m_hOneInstance);
			m_hOneInstance = NULL;
		}
		ReportStatusToSCM(SERVICE_STOP_PENDING);
		if (m_pPlugMgr != NULL)
		{
			m_pPlugMgr->Stop();
		}
		if (m_pLogger)
		{
			m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("I8VDisk Service already stoped."));
			m_pLogger->SetAddDateBefore(false);
			m_pLogger->WriteLog(i8desk::LM_INFO, TEXT("==============================================================\r\n\r\n"));
		}
		ReportStatusToSCM(SERVICE_STOPPED);

		return ERROR_SUCCESS;
	}