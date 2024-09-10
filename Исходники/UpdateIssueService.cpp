STDMETHODIMP CUpdateIssueService::OnShutdown()
{
	RETURN_IF_FAILED(AtlUnadvise(m_pThreadService, __uuidof(IThreadServiceEventSink), m_dwAdvice));
	m_pSettings.Release();
	m_pThreadService.Release();
	m_pTimerService.Release();
	return S_OK;
}