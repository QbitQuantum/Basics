static inline void socket_thread_windows_internal(struct rtmp_stream *stream)
{
	bool can_write = false;

	int delay_time;
	size_t latency_packet_size;
	uint64_t last_send_time = 0;

	HANDLE send_backlog_event;
	OVERLAPPED send_backlog_overlapped;

	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);

	WSAEventSelect(stream->rtmp.m_sb.sb_socket,
			stream->socket_available_event,
			FD_READ|FD_WRITE|FD_CLOSE);

	send_backlog_event = CreateEvent(NULL, true, false, NULL);

	if (stream->low_latency_mode) {
		delay_time = 1000 / LATENCY_FACTOR;
		latency_packet_size = stream->write_buf_size / (LATENCY_FACTOR - 2);
	} else {
		latency_packet_size = stream->write_buf_size;
		delay_time = 0;
	}

	if (!stream->disable_send_window_optimization) {
		memset(&send_backlog_overlapped, 0,
				sizeof(send_backlog_overlapped));
		send_backlog_overlapped.hEvent = send_backlog_event;
		idealsendbacklognotify(stream->rtmp.m_sb.sb_socket,
				&send_backlog_overlapped, NULL);
	} else {
		blog(LOG_INFO, "socket_thread_windows: Send window "
				"optimization disabled by user.");
	}

	HANDLE objs[3];

	objs[0] = stream->socket_available_event;
	objs[1] = stream->buffer_has_data_event;
	objs[2] = send_backlog_event;

	for (;;) {
		if (os_event_try(stream->send_thread_signaled_exit) != EAGAIN) {
			pthread_mutex_lock(&stream->write_buf_mutex);
			if (stream->write_buf_len == 0) {
				//blog(LOG_DEBUG, "Exiting on empty buffer");
				pthread_mutex_unlock(&stream->write_buf_mutex);
				os_event_reset(stream->send_thread_signaled_exit);
				break;
			}

			pthread_mutex_unlock(&stream->write_buf_mutex);
		}

		int status = WaitForMultipleObjects(3, objs, false, INFINITE);
		if (status == WAIT_ABANDONED || status == WAIT_FAILED) {
			blog(LOG_ERROR, "socket_thread_windows: Aborting due "
					"to WaitForMultipleObjects failure");
			fatal_sock_shutdown(stream);
			return;
		}

		if (status == WAIT_OBJECT_0) {
			/* Socket event */
			if (!socket_event(stream, &can_write, last_send_time))
				return;

		} else if (status == WAIT_OBJECT_0 + 2) {
			/* Ideal send backlog event */
			ideal_send_backlog_event(stream, &can_write);

			ResetEvent(send_backlog_event);
			idealsendbacklognotify(stream->rtmp.m_sb.sb_socket,
					&send_backlog_overlapped, NULL);
			continue;
		}

		if (can_write) {
			for (;;) {
				enum data_ret ret = write_data(
						stream,
						&can_write,
						&last_send_time,
						latency_packet_size,
						delay_time);

				switch (ret) {
				case RET_BREAK:
					goto exit_write_loop;
				case RET_FATAL:
					return;
				case RET_CONTINUE:;
				}
			}
		}
		exit_write_loop:;
	}

	if (stream->rtmp.m_sb.sb_socket != INVALID_SOCKET)
		WSAEventSelect(stream->rtmp.m_sb.sb_socket,
			stream->socket_available_event, 0);

	blog(LOG_INFO, "socket_thread_windows: Normal exit");
}