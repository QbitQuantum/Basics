int
clip_TCPCONNECT(ClipMachine *mp)
{
	C_FILE *cf = NULL;
	struct sockaddr_in sin;
	long port = 0, timeout = 60000; /* maybe we should add _set_ for default timeout */
	int arg = 0, sock = -1, ret = -1, i;
	int *err = _clip_fetch_item(mp, HASH_ferror);
	struct timeval tv;
	char *addr  = _clip_parc(mp,1), *sport;

	*err=0;

	if (_clip_parinfo(mp,0) < 2 || _clip_parinfo(mp,1) != CHARACTER_t)
	{
		*err = EINVAL;
		goto err;
	}

	if (_clip_parinfo(mp,2) == NUMERIC_t)
		port = htons(_clip_parnl(mp,2));
	else if ((sport = _clip_parc(mp,2)) != NULL)
	{
		struct servent *sp;
		if ((sp = getservbyname( (const char *) sport, "tcp")) != NULL)
			port = sp->s_port;
		else
		{
			for (i = 0; sport[i] >= '0' && sport[i] <= '9'; i++);
			if (sport[i] == '\0')
				port = htons(atol(sport));
		}

	}

	if (port == 0)
	{
		*err = EINVAL;
		goto err;
	}

	if (_clip_parinfo(mp,3) == NUMERIC_t)
		timeout = _clip_parnl(mp,3);

	tv.tv_sec = timeout / 1000;
	tv.tv_usec = (timeout % 1000) * 1000;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		goto err;

/*
#if !defined(linux) && !defined(SOLARIS_26_X86)
	setsockopt( sock, SOL_SOCKET, SO_SNDTIMEO, (void *)&tv,  sizeof(tv) );
	setsockopt( sock, SOL_SOCKET, SO_RCVTIMEO, (void *)&tv,  sizeof(tv) );
#endif
*/
	if ((arg = fcntl(sock, F_GETFL, 0)) == -1)
		goto err;
	fcntl(sock, F_SETFL, arg | O_NONBLOCK);

	sin.sin_family = AF_INET;
	sin.sin_port = port;
	tcp_host_addr(addr, &sin.sin_addr);

	if (sin.sin_addr.s_addr == INADDR_NONE)
	{
		*err = EFAULT;
		goto err;
	}

	if (connect( sock, (struct sockaddr *) &sin, sizeof(sin)) == -1 )
	{
		fd_set set;

#ifndef OS_MINGW
		if (errno != EINPROGRESS)
			goto err;
#endif

		FD_ZERO(&set);
		FD_SET(sock, &set);

		do  i = _clip_select( sock+1, NULL, &set, NULL, &tv );
		while (i == -1 && errno == EINTR);

		if (i == -1)
			goto err;
		else if (i == 0)
		{
#ifdef OS_MINGW
			*err = EAGAIN;
#else
			*err = ETIMEDOUT;
#endif
		}

		arg = 0;
		i = sizeof(arg);
		if (getsockopt(sock, SOL_SOCKET, SO_ERROR, (void *) &arg, (socklen_t *)(&i)) == -1)
			goto err;
		if (arg != 0)
		{
			*err = arg;
			goto err;
		}
	}

#ifndef OS_MINGW
	if ((arg = fcntl(sock, F_GETFL, 0)) == -1)
		goto err;
	fcntl(sock, F_SETFL, arg | O_NONBLOCK);
#endif

	cf = calloc(1, sizeof(C_FILE));
	cf->fileno = sock;
	cf->f = NULL;
	cf->type = FT_SOCKET;
	cf->pid = -1;
	cf->timeout = timeout;
	cf->stat = 0; /* see FS_* flags */
	ret = _clip_store_c_item(mp, cf, _C_ITEM_TYPE_FILE, destroy_c_file);

	err:
	if (ret == -1)
	{
		if (*err !=0 )
			*err = errno;
		if (sock != -1)
			close(sock);
	}
	_clip_retni(mp, ret);

	return 0;
}