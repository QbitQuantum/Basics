/* we expect the form: port */
int xioopen_ipdgram_listen(int argc, const char *argv[], struct opt *opts,
			   int xioflags, xiofile_t *fd,
			  unsigned groups, int pf, int ipproto,
			  int protname) {
   const char *portname = argv[1];
   union sockaddr_union us;
   union sockaddr_union themunion;
   union sockaddr_union *them = &themunion;
   int socktype = SOCK_DGRAM;
   struct pollfd readfd;
   bool dofork = false;
   pid_t pid;
   char *rangename;
   char infobuff[256];
   unsigned char buff1[1];
   socklen_t uslen;
   socklen_t themlen;
   int result;

   if (argc != 2) {
      Error2("%s: wrong number of parameters (%d instead of 1)", argv[0], argc-1);
   }

   if (pf == PF_UNSPEC) {
#if WITH_IP4 && WITH_IP6
      pf = xioopts.default_ip=='6'?PF_INET6:PF_INET;
#elif WITH_IP6
      pf = PF_INET6;
#else
      pf = PF_INET;
#endif
   }

   retropt_socket_pf(opts, &pf);

   if (applyopts_single(&fd->stream, opts, PH_INIT) < 0)  return -1;
   applyopts(-1, opts, PH_INIT);

   uslen = socket_init(pf, &us);
   retropt_bind(opts, pf, socktype, IPPROTO_UDP,
		(struct sockaddr *)&us, &uslen, 1,
		fd->stream.para.socket.ip.res_opts[1],
		fd->stream.para.socket.ip.res_opts[0]);

   if (false) {
      ;
#if WITH_IP4
   } else if (pf == PF_INET) {
      us.ip4.sin_port = parseport(portname, ipproto);
#endif
#if WITH_IP6
   } else if (pf == PF_INET6) {
      us.ip6.sin6_port = parseport(portname, ipproto);
#endif
   } else {
      Error1("xioopen_ipdgram_listen(): unknown address family %d", pf);
   }

   retropt_bool(opts, OPT_FORK, &dofork);

   if (dofork) {
      if (!(xioflags & XIO_MAYFORK)) {
	 Error("option fork not allowed here");
	 return STAT_NORETRY;
      }
   }

#if WITH_IP4 /*|| WITH_IP6*/
   if (retropt_string(opts, OPT_RANGE, &rangename) >= 0) {
      if (xioparserange(rangename, pf, &fd->stream.para.socket.range) < 0) {
	 free(rangename);
	 return STAT_NORETRY;
      }
      free(rangename);
      fd->stream.para.socket.dorange = true;
   }
#endif

#if WITH_LIBWRAP
   xio_retropt_tcpwrap(&fd->stream, opts);
#endif /* WITH_LIBWRAP */

   if (retropt_ushort(opts, OPT_SOURCEPORT, &fd->stream.para.socket.ip.sourceport)
       >= 0) {
      fd->stream.para.socket.ip.dosourceport = true;
   }
   retropt_bool(opts, OPT_LOWPORT, &fd->stream.para.socket.ip.lowport);

   if (dofork) {
      xiosetchilddied();	/* set SIGCHLD handler */
   }

   while (true) {	/* we loop with fork or prohibited packets */
      /* now wait for some packet on this datagram socket, get its sender
	 address, connect there, and return */
      int one = 1;
      char infobuff[256];
      union sockaddr_union _sockname;
      union sockaddr_union *la = &_sockname;	/* local address */

      if ((fd->stream.fd = xiosocket(opts, pf, socktype, ipproto, E_ERROR)) < 0) {
	 return STAT_RETRYLATER;
      }
      applyopts(fd->stream.fd, opts, PH_PASTSOCKET);
      if (Setsockopt(fd->stream.fd, opt_so_reuseaddr.major,
		     opt_so_reuseaddr.minor, &one, sizeof(one)) < 0) {
	 Warn6("setsockopt(%d, %d, %d, {%d}, "F_Zd"): %s",
	       fd->stream.fd, opt_so_reuseaddr.major,
	       opt_so_reuseaddr.minor, one, sizeof(one), strerror(errno));
      }
      applyopts_cloexec(fd->stream.fd, opts);
      applyopts(fd->stream.fd, opts, PH_PREBIND);
      applyopts(fd->stream.fd, opts, PH_BIND);
      if (Bind(fd->stream.fd, &us.soa, uslen) < 0) {
	 Error4("bind(%d, {%s}, "F_Zd"): %s", fd->stream.fd,
		sockaddr_info(&us.soa, uslen, infobuff, sizeof(infobuff)),
		uslen, strerror(errno));
	 return STAT_RETRYLATER;
      }
      /* under some circumstances bind() fills sockaddr with interesting info. */
      if (Getsockname(fd->stream.fd, &us.soa, &uslen) < 0) {
	 Error4("getsockname(%d, %p, {%d}): %s",
		fd->stream.fd, &us.soa, uslen, strerror(errno));
      }
      applyopts(fd->stream.fd, opts, PH_PASTBIND);

      Notice1("listening on UDP %s",
	      sockaddr_info(&us.soa, uslen, infobuff, sizeof(infobuff)));
      readfd.fd = fd->stream.fd;
      readfd.events = POLLIN|POLLERR;
      while (xiopoll(&readfd, 1, NULL) < 0) {
	 if (errno != EINTR)  break;
      }

      themlen = socket_init(pf, them);
      do {
	 result = Recvfrom(fd->stream.fd, buff1, 1, MSG_PEEK,
			     &them->soa, &themlen);
      } while (result < 0 && errno == EINTR);
      if (result < 0) {
	 Error5("recvfrom(%d, %p, 1, MSG_PEEK, {%s}, {"F_Zu"}): %s",
		fd->stream.fd, buff1,
		sockaddr_info(&them->soa, themlen, infobuff, sizeof(infobuff)),
		themlen, strerror(errno));
	 return STAT_RETRYLATER;
      }

      Notice1("accepting UDP connection from %s",
	      sockaddr_info(&them->soa, themlen, infobuff, sizeof(infobuff)));

      if (xiocheckpeer(&fd->stream, them, la) < 0) {
	 /* drop packet */
	 char buff[512];
	 Recv(fd->stream.fd, buff, sizeof(buff), 0);	/* drop packet */
	 Close(fd->stream.fd);
	 continue;
      }
      Info1("permitting UDP connection from %s",
	    sockaddr_info(&them->soa, themlen, infobuff, sizeof(infobuff)));

      if (dofork) {
	 pid = xio_fork(false, E_ERROR);
	 if (pid < 0) {
	    return STAT_RETRYLATER;
	 }

	 if (pid == 0) {	/* child */
	    break;
	 }

	 /* server: continue loop with socket()+recvfrom() */
	 /* when we dont close this we get awkward behaviour on Linux 2.4:
	    recvfrom gives 0 bytes with invalid socket address */
	 if (Close(fd->stream.fd) < 0) {
	    Info2("close(%d): %s", fd->stream.fd, strerror(errno));
	 }
	 Sleep(1);	/*! give child a chance to consume the old packet */

	 continue;
      }
      break;
   }

   applyopts(fd->stream.fd, opts, PH_CONNECT);
   if ((result = Connect(fd->stream.fd, &them->soa, themlen)) < 0) {
      Error4("connect(%d, {%s}, "F_Zd"): %s",
	     fd->stream.fd,
	     sockaddr_info(&them->soa, themlen, infobuff, sizeof(infobuff)),
	     themlen, strerror(errno));
      return STAT_RETRYLATER;
   }

   /* set the env vars describing the local and remote sockets */
   if (Getsockname(fd->stream.fd, &us.soa, &uslen) < 0) {
      Warn4("getsockname(%d, %p, {%d}): %s",
	    fd->stream.fd, &us.soa, uslen, strerror(errno));
   }
   xiosetsockaddrenv("SOCK", &us,  uslen,   IPPROTO_UDP);
   xiosetsockaddrenv("PEER", them, themlen, IPPROTO_UDP);

   fd->stream.howtoend = END_SHUTDOWN;
   applyopts_fchown(fd->stream.fd, opts);
   applyopts(fd->stream.fd, opts, PH_LATE);

   if ((result = _xio_openlate(&fd->stream, opts)) < 0)
      return result;

   return 0;
}