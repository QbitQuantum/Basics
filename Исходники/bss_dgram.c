static void dgram_adjust_rcv_timeout(BIO *b)
	{
#if defined(SO_RCVTIMEO)
	bio_dgram_data *data = (bio_dgram_data *)b->ptr;
	int sz = sizeof(int);

	/* Is a timer active? */
	if (data->next_timeout.tv_sec > 0 || data->next_timeout.tv_usec > 0)
		{
		struct timeval timenow, timeleft;

		/* Read current socket timeout */
#ifdef OPENSSL_SYS_WINDOWS
		int timeout;
		if (getsockopt(b->num, SOL_SOCKET, SO_RCVTIMEO,
					   (void*)&timeout, &sz) < 0)
			{ perror("getsockopt"); }
		else
			{
			data->socket_timeout.tv_sec = timeout / 1000;
			data->socket_timeout.tv_usec = (timeout % 1000) * 1000;
			}
#else
		if ( getsockopt(b->num, SOL_SOCKET, SO_RCVTIMEO, 
						&(data->socket_timeout), (void *)&sz) < 0)
			{ perror("getsockopt"); }
#endif

		/* Get current time */
		get_current_time(&timenow);

		/* Calculate time left until timer expires */
		memcpy(&timeleft, &(data->next_timeout), sizeof(struct timeval));
		timeleft.tv_sec -= timenow.tv_sec;
		timeleft.tv_usec -= timenow.tv_usec;
		if (timeleft.tv_usec < 0)
			{
			timeleft.tv_sec--;
			timeleft.tv_usec += 1000000;
			}

		if (timeleft.tv_sec < 0)
			{
			timeleft.tv_sec = 0;
			timeleft.tv_usec = 1;
			}

		/* Adjust socket timeout if next handhake message timer
		 * will expire earlier.
		 */
		if ((data->socket_timeout.tv_sec == 0 && data->socket_timeout.tv_usec == 0) ||
			(data->socket_timeout.tv_sec > timeleft.tv_sec) ||
			(data->socket_timeout.tv_sec == timeleft.tv_sec &&
			 data->socket_timeout.tv_usec >= timeleft.tv_usec))
			{
#ifdef OPENSSL_SYS_WINDOWS
			timeout = timeleft.tv_sec * 1000 + timeleft.tv_usec / 1000;
			if (setsockopt(b->num, SOL_SOCKET, SO_RCVTIMEO,
						   (void*)&timeout, sizeof(timeout)) < 0)
				{ perror("setsockopt"); }
#else
			if ( setsockopt(b->num, SOL_SOCKET, SO_RCVTIMEO, &timeleft,
							sizeof(struct timeval)) < 0)
				{ perror("setsockopt"); }
#endif
			}
		}
#endif
	}