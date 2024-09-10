static void* encomsp_server_thread(void* arg)
{
	wStream* s;
	DWORD nCount;
	void* buffer;
	HANDLE events[8];
	HANDLE ChannelEvent;
	DWORD BytesReturned;
	ENCOMSP_ORDER_HEADER* header;
	EncomspServerContext* context;
	UINT error = CHANNEL_RC_OK;
	DWORD status;
	context = (EncomspServerContext*) arg;

	buffer = NULL;
	BytesReturned = 0;
	ChannelEvent = NULL;
	s = Stream_New(NULL, 4096);

	if (!s)
	{
		WLog_ERR(TAG, "Stream_New failed!");
		error = CHANNEL_RC_NO_MEMORY;
		goto out;
	}

	if (WTSVirtualChannelQuery(context->priv->ChannelHandle, WTSVirtualEventHandle,
	                           &buffer, &BytesReturned) == TRUE)
	{
		if (BytesReturned == sizeof(HANDLE))
			CopyMemory(&ChannelEvent, buffer, sizeof(HANDLE));

		WTSFreeMemory(buffer);
	}

	nCount = 0;
	events[nCount++] = ChannelEvent;
	events[nCount++] = context->priv->StopEvent;

	while (1)
	{
		status = WaitForMultipleObjects(nCount, events, FALSE, INFINITE);

		if (status == WAIT_FAILED)
		{
			error = GetLastError();
			WLog_ERR(TAG, "WaitForMultipleObjects failed with error %u", error);
			break;
		}

		status = WaitForSingleObject(context->priv->StopEvent, 0);

		if (status == WAIT_FAILED)
		{
			error = GetLastError();
			WLog_ERR(TAG, "WaitForSingleObject failed with error %u", error);
			break;
		}

		if (status == WAIT_OBJECT_0)
		{
			break;
		}

		WTSVirtualChannelRead(context->priv->ChannelHandle, 0, NULL, 0, &BytesReturned);

		if (BytesReturned < 1)
			continue;

		if (!Stream_EnsureRemainingCapacity(s, BytesReturned))
		{
			WLog_ERR(TAG, "Stream_EnsureRemainingCapacity failed!");
			error = CHANNEL_RC_NO_MEMORY;
			break;
		}

		if (!WTSVirtualChannelRead(context->priv->ChannelHandle, 0,
		                           (PCHAR) Stream_Buffer(s), Stream_Capacity(s), &BytesReturned))
		{
			WLog_ERR(TAG, "WTSVirtualChannelRead failed!");
			error = ERROR_INTERNAL_ERROR;
			break;
		}

		if (Stream_GetPosition(s) >= ENCOMSP_ORDER_HEADER_SIZE)
		{
			header = (ENCOMSP_ORDER_HEADER*) Stream_Buffer(s);

			if (header->Length >= Stream_GetPosition(s))
			{
				Stream_SealLength(s);
				Stream_SetPosition(s, 0);

				if ((error = encomsp_server_receive_pdu(context, s)))
				{
					WLog_ERR(TAG, "encomsp_server_receive_pdu failed with error %u!", error);
					break;
				}

				Stream_SetPosition(s, 0);
			}
		}
	}

	Stream_Free(s, TRUE);
out:

	if (error && context->rdpcontext)
		setChannelError(context->rdpcontext, error,
		                "encomsp_server_thread reported an error");

	ExitThread((DWORD)error);
	return NULL;
}