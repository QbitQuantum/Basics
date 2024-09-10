HRESULT CRunBreakPoint::OnDemandBreakpoint(CebScript *pScript, CebThread *pThread, IObjectManagement *pIOM, IStreamInfo *pISI)
{
	ASSERT(NULL != pScript);
	ASSERT(NULL != pThread);
	if (pScript == NULL || pThread == NULL) return E_POINTER;
	ASSERT(NULL != pThread->GetHandle());
	ASSERT(NULL != pScript->GetHandle());
	if (NULL == pScript->GetHandle() || NULL == pThread->GetHandle()) return E_HANDLE;

	HRESULT hr = NOERROR;
	try
	{// evtl. Debuggerfenster erzeugen
		hr = CreateDebugger(WM_CLOSEBREAKPOINTDEBUGGERDIALOG, false, 0, pIOM, pISI);
		if (FAILED(hr)) _com_issue_error(hr);
		// Fertzigen Script und Thread unterschieben
		if (!ebDebugger_SetScript(GetDebuggerWnd(), pScript->GetHandle())) _com_issue_error(E_FAIL);
		if (!ebDebugger_SetThread(GetDebuggerWnd(), pThread->GetHandle())) _com_issue_error(E_FAIL);
		// jetzt Debugger anzeigen 
		hr = m_pScriptDebugger -> RunModal();	
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch(_com_error& e)
	{
		if (m_pScriptDebugger) 
			m_pScriptDebugger -> DestroyWindow(); 
		m_pScriptDebugger = NULL;
		return _COM_ERROR(e);
	}
	return S_OK;
}