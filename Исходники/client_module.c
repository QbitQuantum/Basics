void* freerds_client_thread(void* arg)
{
	int fps;
	DWORD status;
	DWORD nCount;
	HANDLE events[8];
	HANDLE PackTimer;
	LARGE_INTEGER due;
	rdsBackendConnector* connector = (rdsBackendConnector*) arg;

	fps = connector->fps;
	PackTimer = CreateWaitableTimer(NULL, TRUE, NULL);

	due.QuadPart = 0;
	SetWaitableTimer(PackTimer, &due, 1000 / fps, NULL, NULL, 0);

	nCount = 0;
	events[nCount++] = PackTimer;
	events[nCount++] = connector->StopEvent;
	events[nCount++] = connector->hClientPipe;

	while (1)
	{
		status = WaitForMultipleObjects(nCount, events, FALSE, INFINITE);

		if (WaitForSingleObject(connector->StopEvent, 0) == WAIT_OBJECT_0)
		{
			break;
		}

		if (WaitForSingleObject(connector->hClientPipe, 0) == WAIT_OBJECT_0)
		{
			if (freerds_transport_receive((rdsBackend*) connector) < 0)
				break;
		}

		if (status == WAIT_OBJECT_0)
		{
			freerds_message_server_queue_pack(connector);

			if (connector->fps != fps)
			{
				fps = connector->fps;
				due.QuadPart = 0;
				SetWaitableTimer(PackTimer, &due, 1000 / fps, NULL, NULL, 0);
			}
		}
	}

	CloseHandle(PackTimer);

	return NULL;
}