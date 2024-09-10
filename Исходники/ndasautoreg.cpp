HRESULT
CNdasAutoRegister::Initialize()
{
	if (m_hSemQueue.IsInvalid())
	{
		m_hSemQueue = ::CreateSemaphore(NULL, 0, 255, NULL);
		if (m_hSemQueue.IsInvalid())
		{
			HRESULT hr = AtlHresultFromLastError();
			return hr;
		}
	}
	(void) m_data.LoadFromSystem();
	return S_OK;
}