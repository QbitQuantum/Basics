HRESULT
CNdasDeviceHeartbeatListener::Initialize()
{
	if (!m_datalock.Initialize())
	{
		return AtlHresultFromLastError();
	}
	return S_OK;
}