static int tss2_get_socket (FILE **ret_read_fh, FILE **ret_write_fh)
{
	/*
	 * Returns connected file objects or establishes the connection
	 * if it's not already present
	 */
	struct addrinfo ai_hints;
	struct addrinfo *ai_head;
	struct addrinfo *ai_ptr;
	int sd = -1;
	int status;

	/* Check if we already got opened connections */
	if ((global_read_fh != NULL) && (global_write_fh != NULL))
	{
		/* If so, use them */
		if (ret_read_fh != NULL)
			*ret_read_fh = global_read_fh;
		if (ret_write_fh != NULL)
			*ret_write_fh = global_write_fh;
		return (0);
	}

	/* Get all addrs for this hostname */
	memset (&ai_hints, 0, sizeof (ai_hints));
#ifdef AI_ADDRCONFIG
	ai_hints.ai_flags |= AI_ADDRCONFIG;
#endif
	ai_hints.ai_family = AF_UNSPEC;
	ai_hints.ai_socktype = SOCK_STREAM;

	status = getaddrinfo ((config_host != NULL) ? config_host : DEFAULT_HOST,
			(config_port != NULL) ? config_port : DEFAULT_PORT,
			&ai_hints,
			&ai_head);
	if (status != 0)
	{
		ERROR ("teamspeak2 plugin: getaddrinfo failed: %s",
				gai_strerror (status));
		return (-1);
	}

	/* Try all given hosts until we can connect to one */
	for (ai_ptr = ai_head; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
	{
		/* Create socket */
		sd = socket (ai_ptr->ai_family, ai_ptr->ai_socktype,
				ai_ptr->ai_protocol);
		if (sd < 0)
		{
			char errbuf[1024];
			WARNING ("teamspeak2 plugin: socket failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			continue;
		}

		/* Try to connect */
		status = connect (sd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
		if (status != 0)
		{
			char errbuf[1024];
			WARNING ("teamspeak2 plugin: connect failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			close (sd);
			continue;
		}

		/*
		 * Success, we can break. Don't need more than one connection
		 */
		break;
	} /* for (ai_ptr) */

	freeaddrinfo (ai_head);

	/* Check if we really got connected */
	if (sd < 0)
		return (-1);

	/* Create file objects from sockets */
	global_read_fh = fdopen (sd, "r");
	if (global_read_fh == NULL)
	{
		char errbuf[1024];
		ERROR ("teamspeak2 plugin: fdopen failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		close (sd);
		return (-1);
	}

	global_write_fh = fdopen (sd, "w");
	if (global_write_fh == NULL)
	{
		char errbuf[1024];
		ERROR ("teamspeak2 plugin: fdopen failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		tss2_close_socket ();
		return (-1);
	}

	{ /* Check that the server correctly identifies itself. */
		char buffer[4096];
		char *buffer_ptr;

		buffer_ptr = fgets (buffer, sizeof (buffer), global_read_fh);
		buffer[sizeof (buffer) - 1] = 0;

		if (memcmp ("[TS]\r\n", buffer, 6) != 0)
		{
			ERROR ("teamspeak2 plugin: Unexpected response when connecting "
					"to server. Expected ``[TS]'', got ``%s''.",
					buffer);
			tss2_close_socket ();
			return (-1);
		}
		DEBUG ("teamspeak2 plugin: Server send correct banner, connected!");
	}

	/* Copy the new filehandles to the given pointers */
	if (ret_read_fh != NULL)
		*ret_read_fh = global_read_fh;
	if (ret_write_fh != NULL)
		*ret_write_fh = global_write_fh;
	return (0);
} /* int tss2_get_socket */