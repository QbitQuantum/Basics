int
WaitLatchOrSocket(volatile Latch *latch, SOCKET sock, long timeout)
{
	DWORD		rc;
	HANDLE		events[3];
	HANDLE		latchevent;
	HANDLE		sockevent;
	int			numevents;
	int			result = 0;

	latchevent = latch->event;

	events[0] = latchevent;
	events[1] = pgwin32_signal_event;
	numevents = 2;
	if (sock != PGINVALID_SOCKET)
	{
		sockevent = WSACreateEvent();
		WSAEventSelect(sock, sockevent, FD_READ);
		events[numevents++] = sockevent;
	}

	for (;;)
	{
		/*
		 * Reset the event, and check if the latch is set already. If someone
		 * sets the latch between this and the WaitForMultipleObjects() call
		 * below, the setter will set the event and WaitForMultipleObjects()
		 * will return immediately.
		 */
		if (!ResetEvent(latchevent))
			elog(ERROR, "ResetEvent failed: error code %d", (int) GetLastError());
		if (latch->is_set)
		{
			result = 1;
			break;
		}

		rc = WaitForMultipleObjects(numevents, events, FALSE,
								(timeout >= 0) ? (timeout / 1000) : INFINITE);
		if (rc == WAIT_FAILED)
			elog(ERROR, "WaitForMultipleObjects() failed: error code %d", (int) GetLastError());
		else if (rc == WAIT_TIMEOUT)
		{
			result = 0;
			break;
		}
		else if (rc == WAIT_OBJECT_0 + 1)
			pgwin32_dispatch_queued_signals();
		else if (rc == WAIT_OBJECT_0 + 2)
		{
			Assert(sock != PGINVALID_SOCKET);
			result = 2;
			break;
		}
		else if (rc != WAIT_OBJECT_0)
			elog(ERROR, "unexpected return code from WaitForMultipleObjects(): %d", rc);
	}

	/* Clean up the handle we created for the socket */
		if (sock != PGINVALID_SOCKET)
	{
		WSAEventSelect(sock, sockevent, 0);
		WSACloseEvent(sockevent);
	}

	return result;
}