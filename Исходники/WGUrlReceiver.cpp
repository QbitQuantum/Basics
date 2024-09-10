void CWGUrlReceiver::StartJobThread(LPTHREAD_START_ROUTINE pfn)
{
	UIThread *thr = (UIThread*) RUNTIME_CLASS (UIThread)->CreateObject ();
	_ic_DownloadInfo* dlinfo = new _ic_DownloadInfo;
	*dlinfo = m_dlInfo;

	if (pfn == _threadAddPage  ||
			(!dlinfo->bForceSilent && !_App.Monitor_Silent ()))
	{
		CComObject <CFdmUiWindow> *pUiWindow = NULL;		
		CComObject <CFdmUiWindow>::CreateInstance (&pUiWindow);
		dlinfo->pUiWindow = pUiWindow;
		if (pUiWindow)
			pUiWindow->AddRef ();
		vmsAUTOLOCKSECTION (m_csLastUiWindow);
		m_spLastUiWindow = pUiWindow;
	}
	else
	{
		dlinfo->pUiWindow = NULL;
	}

	thr->set_Thread (pfn, dlinfo);
	thr->CreateThread ();

	if (m_hJobt)
		CloseHandle (m_hJobt);

	DuplicateHandle (GetCurrentProcess (), thr->m_hThread, GetCurrentProcess (),
		&m_hJobt, 0, TRUE, DUPLICATE_SAME_ACCESS);
}