BOOL WTSVirtualChannelManagerCheckFileDescriptor(HANDLE hServer)
{
	wMessage message;
	BOOL status = TRUE;
	rdpPeerChannel* channel;
	UINT32 dynvc_caps;
	WTSVirtualChannelManager* vcm = (WTSVirtualChannelManager*) hServer;

	if ((vcm->drdynvc_state == DRDYNVC_STATE_NONE) && vcm->client->activated)
	{
		/* Initialize drdynvc channel once and only once. */
		vcm->drdynvc_state = DRDYNVC_STATE_INITIALIZED;
		channel = (rdpPeerChannel*) WTSVirtualChannelOpen((HANDLE) vcm,
		          WTS_CURRENT_SESSION, "drdynvc");

		if (channel)
		{
			ULONG written;
			vcm->drdynvc_channel = channel;
			dynvc_caps = 0x00010050; /* DYNVC_CAPS_VERSION1 (4 bytes) */

			if (!WTSVirtualChannelWrite(channel, (PCHAR) &dynvc_caps, sizeof(dynvc_caps),
			                            &written))
				return FALSE;
		}
	}

	while (MessageQueue_Peek(vcm->queue, &message, TRUE))
	{
		BYTE* buffer;
		UINT32 length;
		UINT16 channelId;
		channelId = (UINT16)(UINT_PTR) message.context;
		buffer = (BYTE*) message.wParam;
		length = (UINT32)(UINT_PTR) message.lParam;

		if (vcm->client->SendChannelData(vcm->client, channelId, buffer,
		                                 length) == FALSE)
		{
			status = FALSE;
		}

		free(buffer);

		if (!status)
			break;
	}

	return status;
}