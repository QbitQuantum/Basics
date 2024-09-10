HRESULT
CNdasEventMonitor::Initialize()
{
	HRESULT hr;

	// Initialize routine is reentrant
	if (m_HeartbeatMonitorTimer.IsInvalid()) 
	{
		// Auto-reset waitable timer
		m_HeartbeatMonitorTimer = ::CreateWaitableTimer(NULL, FALSE, NULL);
		if (m_HeartbeatMonitorTimer.IsInvalid()) 
		{
			hr = AtlHresultFromLastError();			
			XTLTRACE2(NDASSVC_EVENTMON, TRACE_LEVEL_ERROR,
				"Timer creation failed, hr=0x%X\n", 
				hr);
			return hr;
		}
	}
	if (m_NdasLogicalUnitSetChanged.IsInvalid()) 
	{
		m_NdasLogicalUnitSetChanged = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		if (m_NdasLogicalUnitSetChanged.IsInvalid()) 
		{
			hr = AtlHresultFromLastError();
			XTLTRACE2(NDASSVC_EVENTMON, TRACE_LEVEL_ERROR,
				"Logical device set change event creation failed, hr=0x%X\n",
				hr);
			return hr;
		}
	}
	if (!m_NdasDeviceDataLock.Initialize())
	{
		hr = AtlHresultFromLastError();
		XTLTRACE2(NDASSVC_EVENTMON, TRACE_LEVEL_ERROR,
			"Device ReaderWriterLock initialization failed, hr=0x%X\n",
			hr);
		return hr;
	}
	if (!m_NdasLogicalUnitDataLock.Initialize())
	{
		hr = AtlHresultFromLastError();			
		XTLTRACE2(NDASSVC_EVENTMON, TRACE_LEVEL_ERROR,
			"LogDevice ReaderWriterLock initialization failed, hr=0x%X\n",
			hr);
		return hr;
	}

	return S_OK;
}