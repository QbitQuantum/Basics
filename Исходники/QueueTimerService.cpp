STDMETHODIMP QueueTimerService::SetTimerClient(ITimerClient *pClient)
{
	TimerData *data = clients.get(pClient);

	double time;
	pClient->get_TimerInterval(&time);

	if (time == 0.0 && data != 0)
		RemoveTimerClient(pClient);
	else
	{
		if (!data)
		{
			data = new TimerData(hWnd, NULL, pClient);
			clients.put(pClient, data);
		}
		else
			::DeleteTimerQueueTimer(hQueue, data->hTimer, NULL);

		AtlTrace("Setting timer to %ld\n", (long)(time * 1000));
		::CreateTimerQueueTimer(&data->hTimer, hQueue, QTS_Handler, (PVOID)data, (long)(time * 1000), (long)(time * 10000), WT_EXECUTEINTIMERTHREAD);
	}

	return S_OK;
}