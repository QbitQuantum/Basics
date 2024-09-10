/**
 * Function description
 *
 * @return 0 on success, otherwise a Win32 error code
 */
UINT rdpei_server_init(RdpeiServerContext *context)
{
	void *buffer = NULL;
	DWORD bytesReturned;
	RdpeiServerPrivate *priv = context->priv;

	priv->channelHandle = WTSVirtualChannelOpenEx(WTS_CURRENT_SESSION, RDPEI_DVC_CHANNEL_NAME, WTS_CHANNEL_OPTION_DYNAMIC);
	if (!priv->channelHandle)
	{
		WLog_ERR(TAG, "WTSVirtualChannelOpenEx failed!");
		return CHANNEL_RC_INITIALIZATION_ERROR;
	}

	if (!WTSVirtualChannelQuery(priv->channelHandle, WTSVirtualEventHandle, &buffer, &bytesReturned) || (bytesReturned != sizeof(HANDLE)))
	{
		WLog_ERR(TAG, "WTSVirtualChannelQuery failed or invalid invalid returned size(%d)!", bytesReturned);
		if (buffer)
			WTSFreeMemory(buffer);
		goto out_close;
	}
	CopyMemory(&priv->eventHandle, buffer, sizeof(HANDLE));
	WTSFreeMemory(buffer);

	return CHANNEL_RC_OK;

out_close:
	WTSVirtualChannelClose(priv->channelHandle);
	return CHANNEL_RC_INITIALIZATION_ERROR;
}