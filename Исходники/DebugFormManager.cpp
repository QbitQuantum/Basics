STDMETHODIMP CDebugFormManager::OnShutdown()
{
	RETURN_IF_FAILED(AtlUnadvise(m_pViewDebugEngineService, IID_IViewDebugEngineServiceEvents, m_dwCookie));
	m_pServiceProvider = NULL;

	return S_OK;
}