static int xioopen_unix_listen(int argc, const char *argv[], struct opt *opts, int xioflags, xiofile_t *xxfd, unsigned groups, int abstract, int dummy2, int dummy3) {
   /* we expect the form: filename */
   const char *name;
   xiosingle_t *xfd = &xxfd->stream;
   int pf = PF_UNIX;
   int socktype = SOCK_STREAM;
   int protocol = 0;
   struct sockaddr_un us;
   socklen_t uslen;
   bool tight = true;
   struct opt *opts0 = NULL;
   pid_t pid = Getpid();
   bool opt_unlink_early = false;
   bool opt_unlink_close = true;
   int result;

   if (argc != 2) {
      Error2("%s: wrong number of parameters (%d instead of 1)",
	     argv[0], argc-1);
      return STAT_NORETRY;
   }

   name = argv[1];
   retropt_socket_pf(opts, &pf);
   retropt_bool(opts, OPT_UNIX_TIGHTSOCKLEN, &tight);
   uslen = xiosetunix(pf, &us, name, abstract, tight);

   xfd->howtoend = END_SHUTDOWN;

   if (!(ABSTRACT && abstract)) {
      /* only for non abstract because abstract do not work in file system */
      retropt_bool(opts, OPT_UNLINK_EARLY, &opt_unlink_early);
      retropt_bool(opts, OPT_UNLINK_CLOSE, &opt_unlink_close);
   }

   if (applyopts_single(xfd, opts, PH_INIT) < 0) return STAT_NORETRY;
   applyopts(-1, opts, PH_INIT);
   applyopts(-1, opts, PH_EARLY);

   if (!(ABSTRACT && abstract)) {
      if (opt_unlink_early) {
	 if (Unlink(name) < 0) {
	    if (errno == ENOENT) {
	       Warn2("unlink(\"%s\"): %s", name, strerror(errno));
	    } else {
	       Error2("unlink(\"%s\"): %s", name, strerror(errno));
	    }
	 }
      }

      /* trying to set user-early, perm-early etc. here is useless because
	 file system entry is available only past bind() call. */
      applyopts_named(name, opts, PH_EARLY);	/* umask! */
   }

   opts0 = copyopts(opts, GROUP_ALL);

   if ((result =
	xioopen_listen(xfd, xioflags,
		       (struct sockaddr *)&us, uslen,
		       opts, opts0, pf, socktype, protocol))
       != 0)
      return result;

   /* we set this option as late as now because we should not remove an
      existing entry when bind() failed */
   if (!(ABSTRACT && abstract)) {
      if (opt_unlink_close) {
	 if (pid == Getpid()) {
	    if ((xfd->unlink_close = strdup(name)) == NULL) {
	       Error1("strdup(\"%s\"): out of memory", name);
	    }
	    xfd->opt_unlink_close = true;
	 }
      }
   }
   return 0;
}