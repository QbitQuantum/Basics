static void* rdpdr_server_thread(void* arg)
{
	wStream* s;
	DWORD status;
	DWORD nCount;
	void* buffer;
	int position;
	HANDLE events[8];
	RDPDR_HEADER header;
	HANDLE ChannelEvent;
	DWORD BytesReturned;
	RdpdrServerContext* context;
	context = (RdpdrServerContext*) arg;
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
	rdpdr_server_send_announce_request(context);

	while (1)
	{
		BytesReturned = 0;
		status = WaitForMultipleObjects(nCount, events, FALSE, INFINITE);

		if (WaitForSingleObject(context->priv->StopEvent, 0) == WAIT_OBJECT_0)
		{
			break;
		}

		WTSVirtualChannelRead(context->priv->ChannelHandle, 0, NULL, 0, &BytesReturned);

		if (BytesReturned < 1)
			continue;

		Stream_EnsureRemainingCapacity(s, BytesReturned);

		if (!WTSVirtualChannelRead(context->priv->ChannelHandle, 0,
								   (PCHAR) Stream_Buffer(s), Stream_Capacity(s), &BytesReturned))
		{
			break;
		}

		if (Stream_GetPosition(s) >= RDPDR_HEADER_LENGTH)
		{
			position = Stream_GetPosition(s);
			Stream_SetPosition(s, 0);
			Stream_Read_UINT16(s, header.Component); /* Component (2 bytes) */
			Stream_Read_UINT16(s, header.PacketId); /* PacketId (2 bytes) */
			Stream_SetPosition(s, position);
			Stream_SealLength(s);
			Stream_SetPosition(s, RDPDR_HEADER_LENGTH);
			rdpdr_server_receive_pdu(context, s, &header);
			Stream_SetPosition(s, 0);
		}
	}

	Stream_Free(s, TRUE);
	return NULL;
}