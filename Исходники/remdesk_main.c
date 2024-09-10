static void* remdesk_server_thread(void* arg)
{
	wStream* s;
	DWORD status;
	DWORD nCount;
	void* buffer;
	UINT32* pHeader;
	UINT32 PduLength;
	HANDLE events[8];
	HANDLE ChannelEvent;
	DWORD BytesReturned;
	RemdeskServerContext* context;

	context = (RemdeskServerContext*) arg;

	buffer = NULL;
	BytesReturned = 0;
	ChannelEvent = NULL;

	s = Stream_New(NULL, 4096);

	if (WTSVirtualChannelQuery(context->priv->ChannelHandle, WTSVirtualEventHandle, &buffer, &BytesReturned) == TRUE)
	{
		if (BytesReturned == sizeof(HANDLE))
			CopyMemory(&ChannelEvent, buffer, sizeof(HANDLE));

		WTSFreeMemory(buffer);
	}

	nCount = 0;
	events[nCount++] = ChannelEvent;
	events[nCount++] = context->priv->StopEvent;

	remdesk_send_ctl_version_info_pdu(context);

	while (1)
	{
		status = WaitForMultipleObjects(nCount, events, FALSE, INFINITE);

		if (WaitForSingleObject(context->priv->StopEvent, 0) == WAIT_OBJECT_0)
		{
			break;
		}

		if (WTSVirtualChannelRead(context->priv->ChannelHandle, 0,
				(PCHAR) Stream_Buffer(s), Stream_Capacity(s), &BytesReturned))
		{
			if (BytesReturned)
				Stream_Seek(s, BytesReturned);
		}
		else
		{
			Stream_EnsureRemainingCapacity(s, BytesReturned);
		}

		if (Stream_GetPosition(s) >= 8)
		{
			pHeader = (UINT32*) Stream_Buffer(s);
			PduLength = pHeader[0] + pHeader[1] + 8;

			if (PduLength >= Stream_GetPosition(s))
			{
				Stream_SealLength(s);
				Stream_SetPosition(s, 0);
				remdesk_server_receive_pdu(context, s);
				Stream_SetPosition(s, 0);
			}
		}
	}

	Stream_Free(s, TRUE);

	return NULL;
}