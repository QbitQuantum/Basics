bool CUPnPImplMiniLib::CheckAndRefresh()
{
	// on a CheckAndRefresh we don't do any new time consuming discovery tries, we expect to find the same router like the first time
	// and of course we also don't delete old ports (this was done on Discovery) but only check that our current mappings still exist
	// and refresh them if not
	if (m_bAbortDiscovery || !m_bSucceededOnce|| !IsReady() || m_pURLs == NULL || m_pIGDData == NULL 
		|| m_pURLs->controlURL == NULL || m_nTCPPort == 0)
	{
		DebugLog(_T("Not refreshing UPnP ports because they don't seem to be forwarded in the first place"));
		return false;
	}
	else
		DebugLog(_T("Checking and refreshing UPnP ports"));

	m_bCheckAndRefresh = true;
	CStartDiscoveryThread* pStartDiscoveryThread = (CStartDiscoveryThread*) AfxBeginThread(RUNTIME_CLASS(CStartDiscoveryThread), THREAD_PRIORITY_NORMAL,0, CREATE_SUSPENDED);
	m_hThreadHandle = pStartDiscoveryThread->m_hThread;
	pStartDiscoveryThread->SetValues(this);
	pStartDiscoveryThread->ResumeThread();
	return true;
}