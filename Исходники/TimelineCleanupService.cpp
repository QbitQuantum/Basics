STDMETHODIMP CTimelineCleanupService::OnShutdown()
{
	RETURN_IF_FAILED(m_pTimerServiceCleanup->StopTimer());
	RETURN_IF_FAILED(AtlUnadvise(m_pTimerServiceCleanup, __uuidof(ITimerServiceEventSink), m_dwAdviceTimerServiceCleanup));
	m_pTimerServiceCleanup.Release();
	return S_OK;
}