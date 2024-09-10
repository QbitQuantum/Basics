/* if this next one returns zero, no ping reply.
   if it returns > 0, ping reply.
   */
static
int
internal_do_pingin(struct NetKeepAlive *nka) {
	int ret = 0;
#ifndef WIN32
	unsigned char buffer[2048];
	fd_set fs;
	struct timeval tv_sel;
	
	memset(buffer, 0, sizeof(buffer));

	FD_ZERO(&fs);
	FD_SET(nka->keepalive_fd, &fs);
	memset(&tv_sel, 0, sizeof(tv_sel));	// set to zero - imitate polling

	ret = select(nka->keepalive_fd + 1, &fs, NULL, NULL, &tv_sel);	
	if (ret > 0)
		ret = recv(nka->keepalive_fd, buffer, sizeof(buffer), 0);
#else
	// Check if windows signaled our event
	// meaning the ping reply came in
	//
	if ((hEvent != NULL) && (WaitForSingleObject(hEvent, 0) == WAIT_OBJECT_0)) 
  {
		if (nka->family == AF_INET6)
    {
			ret = Icmp6ParseReplies(ReplyBuffer, sizeof(ReplyBuffer));
    }
#ifdef V4V6_SUPPORT
		else if (nka->family == AF_INET)
    {
			ret = IcmpParseReplies(ReplyBuffer, sizeof(ReplyBuffer));
    }
#endif

		CloseHandle(hEvent);
		hEvent = NULL;
	}
#endif

	//if (ret > 0) 
	//	Display(LOG_LEVEL_3, ELNotice, "internal_do_pingin", HEX_STR_ICMP_ECHO_REPLY, ret);
	return ret;
}