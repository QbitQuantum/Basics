//wait for the ConnectSucceeded or ConnectFailed call back to get called
HRESULT WcnConnectNotification::WaitForConnectionResult()
{
	HRESULT hr = S_OK;

	DWORD dwIndex = 0;
	hr = CoWaitForMultipleHandles(
									COWAIT_WAITALL, 
									CONNECT_TIME_OUT, 
									1, 
									&connectEndEvent, 
									&dwIndex);
	
	if (hr == S_OK && dwIndex == 0)
	{
		ResetEvent(connectEndEvent);
	}
	else
	{
		wprintf(L"\nDiscovery timeout (after waiting %ums).", CONNECT_TIME_OUT);
	}

	return hr;
}