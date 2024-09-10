HRESULT
CNdasCommandServer::Initialize()
{
	m_hProcSemaphore = ::CreateSemaphore(NULL, 0, MaxPipeInstances, NULL);
	if (m_hProcSemaphore.IsInvalid())
	{
		HRESULT hr = AtlHresultFromLastError();
		return hr;
	}
	return S_OK;
}