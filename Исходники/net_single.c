int
network_process_io(int timeout)
{
    network_handle nh;
    static server_handle sh;
    static Stream *s = 0;
    char buffer[1024];
    int count;
    char *ptr, *end;
    int got_some = 0;

    if (s == 0) {
	int flags;

	s = new_stream(1000);

	if ((flags = fcntl(0, F_GETFL)) < 0
	    || fcntl(0, F_SETFL, flags | NONBLOCK_FLAG) < 0) {
	    log_perror("Setting standard input non-blocking");
	    return 0;
	}
    }
    switch (state) {
    case STATE_CLOSED:
	if (listening) {
	    sh = server_new_connection(slistener, nh, 0);
	    state = STATE_OPEN;
	    got_some = 1;
	} else if (timeout != 0)
	    sleep(timeout);
	break;

    case STATE_OPEN:
	for (;;) {
	    while (!input_suspended
		   && (count = read(0, buffer, sizeof(buffer))) > 0) {
		got_some = 1;
		if (binary) {
		    stream_add_string(s, raw_bytes_to_binary(buffer, count));
		    server_receive_line(sh, reset_stream(s));
		} else
		    for (ptr = buffer, end = buffer + count;
			 ptr < end;
			 ptr++) {
			unsigned char c = *ptr;

			if (isgraph(c) || c == ' ' || c == '\t')
			    stream_add_char(s, c);
			else if (c == '\n')
			    server_receive_line(sh, reset_stream(s));
		    }
	    }

	    if (got_some || timeout == 0)
		goto done;

	    sleep(1);
	    timeout--;
	}
    }

  done:
    return got_some;
}