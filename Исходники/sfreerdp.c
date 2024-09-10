static void* tf_debug_channel_thread_func(void* arg)
{
	void* fd;
	wStream* s;
	void* buffer;
	DWORD BytesReturned = 0;
	testPeerContext* context = (testPeerContext*) arg;

	if (WTSVirtualChannelQuery(context->debug_channel, WTSVirtualFileHandle, &buffer, &BytesReturned) == TRUE)
	{
		fd = *((void**) buffer);
		WTSFreeMemory(buffer);

		context->event = CreateWaitObjectEvent(NULL, TRUE, FALSE, fd);
	}

	s = Stream_New(NULL, 4096);

	WTSVirtualChannelWrite(context->debug_channel, (PCHAR) "test1", 5, NULL);

	while (1)
	{
		WaitForSingleObject(context->event, INFINITE);

		if (WaitForSingleObject(context->stopEvent, 0) == WAIT_OBJECT_0)
			break;

		Stream_SetPosition(s, 0);

		if (WTSVirtualChannelRead(context->debug_channel, 0, (PCHAR) Stream_Buffer(s),
			Stream_Capacity(s), &BytesReturned) == FALSE)
		{
			if (BytesReturned == 0)
				break;

			Stream_EnsureRemainingCapacity(s, BytesReturned);

			if (WTSVirtualChannelRead(context->debug_channel, 0, (PCHAR) Stream_Buffer(s),
				Stream_Capacity(s), &BytesReturned) == FALSE)
			{
				/* should not happen */
				break;
			}
		}

		Stream_SetPosition(s, BytesReturned);

		printf("got %lu bytes\n", BytesReturned);
	}

	Stream_Free(s, TRUE);

	return 0;
}