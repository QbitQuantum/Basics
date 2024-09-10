static void* rdpsnd_server_thread_func(void* arg)
{
	void* fd;
	STREAM* s;
	void* buffer;
	BYTE msgType;
	UINT16 BodySize;
	UINT32 bytes_returned = 0;
	rdpsnd_server* rdpsnd = (rdpsnd_server*) arg;
	freerdp_thread* thread = rdpsnd->rdpsnd_channel_thread;

	if (WTSVirtualChannelQuery(rdpsnd->rdpsnd_channel, WTSVirtualFileHandle, &buffer, &bytes_returned) == TRUE)
	{
		fd = *((void**)buffer);
		WTSFreeMemory(buffer);
		thread->signals[thread->num_signals++] = wait_obj_new_with_fd(fd);
	}

	s = stream_new(4096);

	rdpsnd_server_send_formats(rdpsnd, s);

	while (1)
	{
		freerdp_thread_wait(thread);
		
		if (freerdp_thread_is_stopped(thread))
			break;

		stream_set_pos(s, 0);

		if (WTSVirtualChannelRead(rdpsnd->rdpsnd_channel, 0, stream_get_head(s),
			stream_get_size(s), &bytes_returned) == FALSE)
		{
			if (bytes_returned == 0)
				break;
			
			stream_check_size(s, (int) bytes_returned);

			if (WTSVirtualChannelRead(rdpsnd->rdpsnd_channel, 0, stream_get_head(s),
				stream_get_size(s), &bytes_returned) == FALSE)
				break;
		}

		stream_read_BYTE(s, msgType);
		stream_seek_BYTE(s); /* bPad */
		stream_read_UINT16(s, BodySize);

		if (BodySize + 4 > (int) bytes_returned)
			continue;

		switch (msgType)
		{
			case SNDC_FORMATS:
				if (rdpsnd_server_recv_formats(rdpsnd, s))
				{
					IFCALL(rdpsnd->context.Activated, &rdpsnd->context);
				}
				break;
			default:
				break;
		}
	}

	stream_free(s);
	freerdp_thread_quit(thread);

	return 0;
}