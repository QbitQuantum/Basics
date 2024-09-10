static void* drdynvc_server_thread(void* arg)
{
#if 0
	wStream* s;
	DWORD status;
	DWORD nCount;
	void* buffer;
	HANDLE events[8];
	HANDLE ChannelEvent;
	DWORD BytesReturned;
	DrdynvcServerContext* context;
	UINT error = ERROR_INTERNAL_ERROR;

	context = (DrdynvcServerContext*) arg;

	buffer = NULL;
	BytesReturned = 0;
	ChannelEvent = NULL;

	s = Stream_New(NULL, 4096);
	if (!s)
	{
		WLog_ERR(TAG, "Stream_New failed!");
		ExitThread((DWORD) CHANNEL_RC_NO_MEMORY);
		return NULL;
	}

	if (WTSVirtualChannelQuery(context->priv->ChannelHandle, WTSVirtualEventHandle, &buffer, &BytesReturned) == TRUE)
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

		if (WaitForSingleObject(context->priv->StopEvent, 0) == WAIT_OBJECT_0)
		{
			error = CHANNEL_RC_OK;
			break;
		}

		if (!WTSVirtualChannelRead(context->priv->ChannelHandle, 0, NULL, 0, &BytesReturned))
		{
			WLog_ERR(TAG, "WTSVirtualChannelRead failed!");
			break;
		}
		if (BytesReturned < 1)
			continue;
		if (!Stream_EnsureRemainingCapacity(s, BytesReturned))
		{
			WLog_ERR(TAG, "Stream_EnsureRemainingCapacity failed!");
			break;
		}

		if (!WTSVirtualChannelRead(context->priv->ChannelHandle, 0,
			(PCHAR) Stream_Buffer(s), Stream_Capacity(s), &BytesReturned))
		{
			WLog_ERR(TAG, "WTSVirtualChannelRead failed!");
			break;
		}
	}

	Stream_Free(s, TRUE);
	ExitThread((DWORD) error);
#endif
	// WTF ... this code only reads data into the stream until there is no more memory
	ExitThread(0);
	return NULL;
}