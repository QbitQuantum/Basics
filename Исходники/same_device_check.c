bool	same_device_check (mstr tname, char *buf)
{
	int			fstat_res, gsn_stat;
	struct stat		outbuf1, outbuf2;
	GTM_SOCKLEN_TYPE	socknamelen1;
	GTM_SOCKLEN_TYPE	socknamelen2;
	GTM_SOCKLEN_TYPE	psocknamelen1;
	GTM_SOCKLEN_TYPE	psocknamelen2;
	struct sockaddr_storage	sockname1;
	struct sockaddr_storage	sockname2;
	struct sockaddr_storage	psockname1;
	struct sockaddr_storage	psockname2;
	char			port_buffer1[NI_MAXSERV];
	char			port_buffer2[NI_MAXSERV];
	char			pport_buffer1[NI_MAXSERV];
	char			pport_buffer2[NI_MAXSERV];
	char			host_buffer1[NI_MAXHOST];
	char			host_buffer2[NI_MAXHOST];
	char			phost_buffer1[NI_MAXHOST];
	char			phost_buffer2[NI_MAXHOST];
	int			errcode, tmplen, save_errno;
	const char		*errptr;

	FSTAT_FILE(0, &outbuf1, fstat_res);
	if (-1 == fstat_res)
	{
		save_errno = errno;
		rts_error_csa(CSA_ARG(NULL) VARLSTCNT(8) ERR_SYSCALL, 5, RTS_ERROR_LITERAL("fstat"), CALLFROM, save_errno);
	}
	FSTAT_FILE(1, &outbuf2, fstat_res);
	if (-1 == fstat_res)
	{
		save_errno = errno;
		rts_error_csa(CSA_ARG(NULL) VARLSTCNT(8) ERR_SYSCALL, 5, RTS_ERROR_LITERAL("fstat"), CALLFROM, save_errno);
	}

	if ((S_IFMT & outbuf1.st_mode) != (S_IFMT & outbuf2.st_mode))
		return FALSE;


	if (S_ISSOCK(outbuf1.st_mode))
	{
		/* if here then both 0,1 are sockets */
		socknamelen1 = SIZEOF(sockname1);
		if (-1 == (gsn_stat = getsockname(0, (struct sockaddr *)&sockname1, (GTM_SOCKLEN_TYPE *)&socknamelen1)))
		{
			save_errno = errno;
			if (IS_SOCKNAME_UNIXERROR(save_errno))
			{
				/* problem with getsockname for AF_UNIX socket so just assign family for the switch below */
				(((sockaddr_ptr)&sockname1)->sa_family)	= AF_UNIX;
			} else
			{
				/* process error */
				errptr = (char *)STRERROR(save_errno);
				tmplen = STRLEN(errptr);
				rts_error_csa(CSA_ARG(NULL) VARLSTCNT(5) ERR_GETSOCKNAMERR, 3, save_errno, tmplen, errptr);
			}
		}

		socknamelen2 = SIZEOF(sockname2);
		if (-1 == (gsn_stat = getsockname(1, (struct sockaddr *)&sockname2, (GTM_SOCKLEN_TYPE *)&socknamelen2)))
		{
			save_errno = errno;
			if (IS_SOCKNAME_UNIXERROR(save_errno))
			{
				/* problem with getsockname for AF_UNIX socket so just assign family for the switch below */
				(((sockaddr_ptr)&sockname2)->sa_family)	= AF_UNIX;
			} else
			{
				/* process error */
				errptr = (char *)STRERROR(save_errno);
				tmplen = STRLEN(errptr);
				rts_error_csa(CSA_ARG(NULL) VARLSTCNT(5) ERR_GETSOCKNAMERR, 3, save_errno, tmplen, errptr);
			}
		}
		/* if both sockets not the same family then not the same device */
		if ((((sockaddr_ptr)&sockname1)->sa_family) != (((sockaddr_ptr)&sockname2)->sa_family))
			return FALSE;

		switch(((sockaddr_ptr)&sockname1)->sa_family)
		{
		case AF_INET:
		case AF_INET6:
			GETNAMEINFO((struct sockaddr *)&sockname1, socknamelen1, host_buffer1, NI_MAXHOST,
				    port_buffer1, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV, errcode);
			if (0 != errcode)
			{
				RTS_ERROR_ADDRINFO(NULL, ERR_GETNAMEINFO, errcode);
				return FALSE;
			}

			GETNAMEINFO((struct sockaddr *)&sockname2, socknamelen2, host_buffer2, NI_MAXHOST,
				    port_buffer2, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV, errcode);
			if (0 != errcode)
			{
				RTS_ERROR_ADDRINFO(NULL, ERR_GETNAMEINFO, errcode);
				return FALSE;
			}

			/* hosts and ports must be the same */
			if (STRCMP(host_buffer1, host_buffer2) || STRCMP(port_buffer1, port_buffer2))
				return FALSE;

			psocknamelen1 = SIZEOF(psockname1);
			if (-1 == (gsn_stat = getpeername(0, (struct sockaddr *)&psockname1,
							   (GTM_SOCKLEN_TYPE *)&psocknamelen1)))
			{
				save_errno = errno;
				errptr = (char *)STRERROR(save_errno);
				tmplen = STRLEN(errptr);
				rts_error_csa(CSA_ARG(NULL) VARLSTCNT(5) ERR_GETSOCKNAMERR, 3, save_errno, tmplen, errptr);
			}


			psocknamelen2 = SIZEOF(psockname2);
			if (-1 == (gsn_stat = getpeername(1, (struct sockaddr *)&psockname2,
							   (GTM_SOCKLEN_TYPE *)&psocknamelen2)))
			{
				save_errno = errno;
				errptr = (char *)STRERROR(save_errno);
				tmplen = STRLEN(errptr);
				rts_error_csa(CSA_ARG(NULL) VARLSTCNT(5) ERR_GETSOCKNAMERR, 3, save_errno, tmplen, errptr);
			}

			GETNAMEINFO((struct sockaddr *)&psockname1, psocknamelen1, phost_buffer1, NI_MAXHOST,
				    pport_buffer1, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV, errcode);
			if (0 != errcode)
			{
				RTS_ERROR_ADDRINFO(NULL, ERR_GETNAMEINFO, errcode);
				return FALSE;
			}

			GETNAMEINFO((struct sockaddr *)&psockname2, psocknamelen2, phost_buffer2, NI_MAXHOST,
				pport_buffer2, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV, errcode);
			if (0 != errcode)
			{
				RTS_ERROR_ADDRINFO(NULL, ERR_GETNAMEINFO, errcode);
				return FALSE;
			}

			/* hosts and ports for the peer sockets must also be the same */
			if (STRCMP(phost_buffer1, phost_buffer2) || STRCMP(pport_buffer1, pport_buffer2))
				return FALSE;
			break;
		case AF_UNIX:
		default:
			/* if inodes are different or st_dev different then not the same device */
			if ((outbuf1.st_ino != outbuf2.st_ino) || (outbuf1.st_dev != outbuf2.st_dev))
				return FALSE;
			break;
			}
		return TRUE;
	} else if (S_ISCHR(outbuf1.st_mode))
	{
		/* if here then both 0,1 are character devices */
		/* if inodes are different or st_dev different then not the same device */
		if ((outbuf1.st_ino != outbuf2.st_ino) || (outbuf1.st_dev != outbuf2.st_dev))
			return FALSE;
		else
			return TRUE;
	} else
	{
		/* unexpected type so assert */
		assert(FALSE);
		return FALSE;
	}
}