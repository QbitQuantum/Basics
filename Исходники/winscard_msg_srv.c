INTERNAL int32_t SHMProcessEventsServer(uint32_t *pdwClientID)
{
	fd_set read_fd;
	int selret;
#ifdef DO_TIMEOUT
	struct timeval tv;

	tv.tv_sec = 1;
	tv.tv_usec = 0;
#endif

	FD_ZERO(&read_fd);

	/*
	 * Set up the bit masks for select
	 */
	FD_SET(commonSocket, &read_fd);

	selret = select(commonSocket + 1, &read_fd, (fd_set *) NULL,
		(fd_set *) NULL,
#ifdef DO_TIMEOUT
		&tv
#else
		NULL
#endif
		);

	if (selret < 0)
	{
		if (EINTR == errno)
			return -2;

		Log2(PCSC_LOG_CRITICAL, "Select returns with failure: %s",
			strerror(errno));
		return -1;
	}

	if (selret == 0)
		/* timeout. On *BSD only */
		return 2;

	/*
	 * A common pipe packet has arrived - it could be a new application
	 */
	if (FD_ISSET(commonSocket, &read_fd))
	{
		Log1(PCSC_LOG_DEBUG, "Common channel packet arrival");
		if (SHMProcessCommonChannelRequest(pdwClientID) == -1)
		{
			Log2(PCSC_LOG_ERROR,
				"error in SHMProcessCommonChannelRequest: %d", *pdwClientID);
			return -1;
		}
	}
	else
		return -1;

	Log2(PCSC_LOG_DEBUG,
		"SHMProcessCommonChannelRequest detects: %d", *pdwClientID);

	return 0;
}