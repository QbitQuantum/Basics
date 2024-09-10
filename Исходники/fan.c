void *fan_th(void *arg)
{
	struct thrarg *tharg = (struct thrarg *) arg;
	sigset_t sigset;
        struct sigaction act;
	const struct optstruct *pt;
	short int scan;
	int sizelimit = 0, extinfo;
	STATBUF sb;
        uint64_t fan_mask = FAN_ACCESS | FAN_EVENT_ON_CHILD;
	int fan_fd;
        fd_set rfds;
	char buf[4096];
	ssize_t bread;
	struct fanotify_event_metadata *fmd;
	char fname[1024];
	int ret, len;
	char err[128];

    /* ignore all signals except SIGUSR1 */
    sigfillset(&sigset);
    sigdelset(&sigset, SIGUSR1);
    /* The behavior of a process is undefined after it ignores a 
     * SIGFPE, SIGILL, SIGSEGV, or SIGBUS signal */
    sigdelset(&sigset, SIGFPE);
    sigdelset(&sigset, SIGILL);
    sigdelset(&sigset, SIGSEGV);
#ifdef SIGBUS    
    sigdelset(&sigset, SIGBUS);
#endif
    pthread_sigmask(SIG_SETMASK, &sigset, NULL);
    memset(&act, 0, sizeof(struct sigaction));
    act.sa_handler = fan_exit;
    sigfillset(&(act.sa_mask));
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGSEGV, &act, NULL);

    fan_fd = fanotify_init(0, O_RDONLY);
    if(fan_fd < 0) {
	logg("!ScanOnAccess: fanotify_init failed: %s\n", cli_strerror(errno, err, sizeof(err)));
	if(errno == EPERM)
	    logg("ScanOnAccess: clamd must be started by root\n");
	return NULL;
    }

    if((pt = optget(tharg->opts, "OnAccessIncludePath"))->enabled) {
	while(pt) {
	    if(fanotify_mark(fan_fd, FAN_MARK_ADD, fan_mask, fan_fd, pt->strarg) != 0) {
		logg("!ScanOnAccess: Can't include path '%s'\n", pt->strarg);
		return NULL;
	    } else
		logg("ScanOnAccess: Protecting directory '%s'\n", pt->strarg);
	    pt = (struct optstruct *) pt->nextarg;
	}
    } else {
	logg("!ScanOnAccess: Please specify at least one path with OnAccessIncludePath\n");
	return NULL;
    }

    if((pt = optget(tharg->opts, "OnAccessExcludePath"))->enabled) {
	while(pt) {
            if(fanotify_mark(fan_fd, FAN_MARK_REMOVE, fan_mask, fan_fd, pt->strarg) != 0) {
		logg("!ScanOnAccess: Can't exclude path %s\n", pt->strarg);
		return NULL;
	    } else
		logg("ScanOnAccess: Excluded path %s\n", pt->strarg);
	    pt = (struct optstruct *) pt->nextarg;
	}
    }

    sizelimit = optget(tharg->opts, "OnAccessMaxFileSize")->numarg;
    if(sizelimit)
	logg("ScanOnAccess: Max file size limited to %d bytes\n", sizelimit);
    else
	logg("ScanOnAccess: File size limit disabled\n");

    extinfo = optget(tharg->opts, "ExtendedDetectionInfo")->enabled;

    FD_ZERO(&rfds);
    FD_SET(fan_fd, &rfds);
    do {
        ret = select(fan_fd + 1, &rfds, NULL, NULL, NULL);
    } while(ret == -1 && errno == EINTR);

    while((bread = read(fan_fd, buf, sizeof(buf))) > 0) {
	fmd = (struct fanotify_event_metadata *) buf;
	while(FAN_EVENT_OK(fmd, bread)) {
	    scan = 1;
	    if(fmd->fd >= 0) {
		sprintf(fname, "/proc/self/fd/%d", fmd->fd);
		len = readlink(fname, fname, sizeof(fname) - 1);
		if(len == -1) {
		    close(fmd->fd);
		    logg("!ScanOnAccess: Internal error (readlink() failed)\n");
		    return NULL;
		}
		fname[len] = 0;

		if(fan_checkowner(fmd->pid, tharg->opts)) {
		    scan = 0;
		    logg("*ScanOnAccess: %s skipped (excluded UID)\n", fname);
		}

		if(sizelimit) {
		    if(FSTAT(fmd->fd, &sb) != 0 || sb.st_size > sizelimit) {
			scan = 0;
			/* logg("*ScanOnAccess: %s skipped (size > %d)\n", fname, sizelimit); */
		    }
		}

		if(fan_scanfile(fan_fd, fname, fmd, scan, extinfo, tharg) == -1) {
		    close(fmd->fd);
		    return NULL;
		}

		if(close(fmd->fd) == -1) {
		    printf("!ScanOnAccess: Internal error (close(%d) failed)\n", fmd->fd);
		    close(fmd->fd);
		    return NULL;
		}
	    }
	    fmd = FAN_EVENT_NEXT(fmd, bread);
	}
	do {
	    ret = select(fan_fd + 1, &rfds, NULL, NULL, NULL);
	} while(ret == -1 && errno == EINTR);
    }

    if(bread < 0)
	logg("!ScanOnAccess: Internal error (failed to read data)\n");

    return NULL;
}