STDMETHODIMP CTimelineLoadingService::OnShutdown()
{
	if (m_pThreadServiceShowMoreService)
	{
		RETURN_IF_FAILED(AtlUnadvise(m_pThreadServiceShowMoreService, __uuidof(IThreadServiceEventSink), m_dwAdviceThreadServiceShowMoreService));
	}
	RETURN_IF_FAILED(AtlUnadvise(m_pThreadServiceUpdateService, __uuidof(IThreadServiceEventSink), m_dwAdviceThreadServiceUpdateService));
	RETURN_IF_FAILED(IInitializeWithControlImpl::OnShutdown());

	m_pThreadServiceUpdateService.Release();
	m_pTimelineControl.Release();
	m_pThreadServiceShowMoreService.Release();;
	m_pServiceProvider.Release();

	return S_OK;
}