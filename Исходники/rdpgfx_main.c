static BOOL rdpgfx_server_open(RdpgfxServerContext* context)
{
	RdpgfxServerPrivate* priv = (RdpgfxServerPrivate*) context->priv;
	void* buffer = NULL;

	if (!priv->isOpened)
	{
		PULONG pSessionId = NULL;
		DWORD BytesReturned = 0;
		priv->SessionId = WTS_CURRENT_SESSION;

		if (WTSQuerySessionInformationA(context->vcm, WTS_CURRENT_SESSION,
		                                WTSSessionId, (LPSTR*) &pSessionId,
		                                &BytesReturned) == FALSE)
		{
			WLog_ERR(TAG, "WTSQuerySessionInformationA failed!");
			return FALSE;
		}

		priv->SessionId = (DWORD) * pSessionId;
		WTSFreeMemory(pSessionId);
		priv->rdpgfx_channel = WTSVirtualChannelOpenEx(priv->SessionId,
		                       RDPGFX_DVC_CHANNEL_NAME,
		                       WTS_CHANNEL_OPTION_DYNAMIC);

		if (!priv->rdpgfx_channel)
		{
			WLog_ERR(TAG, "WTSVirtualChannelOpenEx failed!");
			return FALSE;
		}

		/* Query for channel event handle */
		if (!WTSVirtualChannelQuery(priv->rdpgfx_channel, WTSVirtualEventHandle,
		                            &buffer, &BytesReturned)
		    || (BytesReturned != sizeof(HANDLE)))
		{
			WLog_ERR(TAG,  "WTSVirtualChannelQuery failed "
			         "or invalid returned size(%d)",
			         BytesReturned);

			if (buffer)
				WTSFreeMemory(buffer);

			goto out_close;
		}

		CopyMemory(&priv->channelEvent, buffer, sizeof(HANDLE));
		WTSFreeMemory(buffer);

		if (!(priv->zgfx = zgfx_context_new(TRUE)))
		{
			WLog_ERR(TAG, "Create zgfx context failed!");
			goto out_close;
		}

		if (priv->ownThread)
		{
			if (!(priv->stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
			{
				WLog_ERR(TAG, "CreateEvent failed!");
				goto out_zgfx;
			}

			if (!(priv->thread = CreateThread(NULL, 0,
			                                  (LPTHREAD_START_ROUTINE)
			                                  rdpgfx_server_thread_func,
			                                  (void*) context, 0, NULL)))
			{
				WLog_ERR(TAG, "CreateThread failed!");
				goto out_stopEvent;
			}
		}

		priv->isOpened = TRUE;
		priv->isReady = FALSE;
		return TRUE;
	}

	WLog_ERR(TAG, "RDPGFX channel is already opened!");
	return FALSE;
out_stopEvent:
	CloseHandle(priv->stopEvent);
	priv->stopEvent = NULL;
out_zgfx:
	zgfx_context_free(priv->zgfx);
	priv->zgfx = NULL;
out_close:
	WTSVirtualChannelClose(priv->rdpgfx_channel);
	priv->rdpgfx_channel = NULL;
	priv->channelEvent = NULL;
	return FALSE;
}