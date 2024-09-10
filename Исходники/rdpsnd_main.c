static int rdpsnd_server_start(RdpsndServerContext* context)
{
	void *buffer = NULL;
	DWORD bytesReturned;
	RdpsndServerPrivate *priv = context->priv;

	priv->ChannelHandle = WTSVirtualChannelOpen(context->vcm, WTS_CURRENT_SESSION, "rdpsnd");
	if (!priv->ChannelHandle)
		return -1;

	if (!WTSVirtualChannelQuery(priv->ChannelHandle, WTSVirtualEventHandle, &buffer, &bytesReturned) || (bytesReturned != sizeof(HANDLE)))
	{
		WLog_ERR(TAG,  "%s: error during WTSVirtualChannelQuery(WTSVirtualEventHandle) or invalid returned size(%d)\n",
				 __FUNCTION__, bytesReturned);

		if (buffer)
			WTSFreeMemory(buffer);
		goto out_close;
	}
	CopyMemory(&priv->channelEvent, buffer, sizeof(HANDLE));
	WTSFreeMemory(buffer);

	priv->rdpsnd_pdu = Stream_New(NULL, 4096);
	if (!priv->rdpsnd_pdu)
		goto out_close;


	if (priv->ownThread)
	{
		context->priv->StopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (!context->priv->StopEvent)
			goto out_pdu;

		context->priv->Thread = CreateThread(NULL, 0,
				(LPTHREAD_START_ROUTINE) rdpsnd_server_thread, (void*) context, 0, NULL);
		if (!context->priv->Thread)
			goto out_stopEvent;
	}

	return 0;

out_stopEvent:
	CloseHandle(context->priv->StopEvent);
	context->priv->StopEvent = NULL;
out_pdu:
	Stream_Free(context->priv->rdpsnd_pdu, TRUE);
	context->priv->rdpsnd_pdu = NULL;
out_close:
	WTSVirtualChannelClose(context->priv->ChannelHandle);
	context->priv->ChannelHandle = NULL;
	return -1;
}