static void* tf_debug_channel_thread_func(void* arg)
{
	void* fd;
	STREAM* s;
	void* buffer;
	uint32 bytes_returned = 0;
	testPeerContext* context = (testPeerContext*) arg;
	freerdp_thread* thread = context->debug_channel_thread;

	if (WTSVirtualChannelQuery(context->debug_channel, WTSVirtualFileHandle, &buffer, &bytes_returned) == true)
	{
		fd = *((void**)buffer);
		WTSFreeMemory(buffer);
		thread->signals[thread->num_signals++] = wait_obj_new_with_fd(fd);
	}

	s = stream_new(4096);

	WTSVirtualChannelWrite(context->debug_channel, (uint8*) "test1", 5, NULL);

	while (1)
	{
		freerdp_thread_wait(thread);
		if (freerdp_thread_is_stopped(thread))
			break;

		stream_set_pos(s, 0);
		if (WTSVirtualChannelRead(context->debug_channel, 0, stream_get_head(s),
			stream_get_size(s), &bytes_returned) == false)
		{
			if (bytes_returned == 0)
				break;
			stream_check_size(s, bytes_returned);
			if (WTSVirtualChannelRead(context->debug_channel, 0, stream_get_head(s),
				stream_get_size(s), &bytes_returned) == false)
			{
				/* should not happen */
				break;
			}
		}
		stream_set_pos(s, bytes_returned);

		printf("got %d bytes\n", bytes_returned);
	}

	stream_free(s);
	freerdp_thread_quit(thread);

	return 0;
}