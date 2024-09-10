void *onas_fan_th(void *arg)
{
	struct thrarg *tharg = (struct thrarg *) arg;
	sigset_t sigset;
        struct sigaction act;
	const struct optstruct *pt;
	short int scan;
	int sizelimit = 0, extinfo;
	STATBUF sb;
        uint64_t fan_mask = FAN_EVENT_ON_CHILD | FAN_CLOSE;
        fd_set rfds;
	char buf[4096];
	ssize_t bread;
	struct fanotify_event_metadata *fmd;
	char fname[1024];
	int ret, len;
	char err[128];

	pthread_attr_t ddd_attr;
	struct ddd_thrarg *ddd_tharg = NULL;

	ddd_pid = 0;

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
    act.sa_handler = onas_fan_exit;
    sigfillset(&(act.sa_mask));
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGSEGV, &act, NULL);

    /* Initialize fanotify */
    onas_fan_fd = fanotify_init(FAN_CLASS_CONTENT | FAN_UNLIMITED_QUEUE | FAN_UNLIMITED_MARKS, O_LARGEFILE | O_RDONLY);
    if(onas_fan_fd < 0) {
	logg("!ScanOnAccess: fanotify_init failed: %s\n", cli_strerror(errno, err, sizeof(err)));
	if(errno == EPERM)
	    logg("ScanOnAccess: clamd must be started by root\n");
	return NULL;
    }

    if (!tharg) {
	logg("!Unable to start on-access scanner. Bad thread args.\n");
	return NULL;
    }


    if (optget(tharg->opts, "OnAccessPrevention")->enabled && !optget(tharg->opts, "OnAccessMountPath")->enabled) {
	    logg("ScanOnAccess: preventing access attempts on malicious files.\n");
	    fan_mask |= FAN_ACCESS_PERM | FAN_OPEN_PERM;
    } else {
	    logg("ScanOnAccess: notifying only for access attempts.\n");
	    fan_mask |= FAN_ACCESS | FAN_OPEN;
    }

    if ((pt = optget(tharg->opts, "OnAccessMountPath"))->enabled) {
	    while(pt) {
		    if(fanotify_mark(onas_fan_fd, FAN_MARK_ADD | FAN_MARK_MOUNT, fan_mask, onas_fan_fd, pt->strarg) != 0) {
			    logg("!ScanOnAccess: Can't include mountpoint '%s'\n", pt->strarg);
			    return NULL;
		    } else
			    logg("ScanOnAccess: Protecting '%s' and rest of mount.\n", pt->strarg);
		    pt = (struct optstruct *) pt->nextarg;
	    }

    } else if (!optget(tharg->opts, "OnAccessDisableDDD")->enabled) {
	    do {
		    if(pthread_attr_init(&ddd_attr)) break;
		    pthread_attr_setdetachstate(&ddd_attr, PTHREAD_CREATE_JOINABLE);

		    if(!(ddd_tharg = (struct ddd_thrarg *) malloc(sizeof(struct ddd_thrarg)))) break;

		    ddd_tharg->fan_fd = onas_fan_fd;
		    ddd_tharg->fan_mask = fan_mask;
		    ddd_tharg->opts = tharg->opts;
		    ddd_tharg->engine = tharg->engine;
		    ddd_tharg->options = tharg->options;

		    if(!pthread_create(&ddd_pid, &ddd_attr, onas_ddd_th, ddd_tharg)) break;

		    free(ddd_tharg);
		    ddd_tharg=NULL;
	    } while(0);
	    if (!ddd_tharg) logg("!Unable to start dynamic directory determination.\n");

    } else {
	    if((pt = optget(tharg->opts, "OnAccessIncludePath"))->enabled) {
		    while(pt) {
			    if(fanotify_mark(onas_fan_fd, FAN_MARK_ADD, fan_mask, onas_fan_fd, pt->strarg) != 0) {
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
    }

    /* Load other options. */
    sizelimit = optget(tharg->opts, "OnAccessMaxFileSize")->numarg;
    if(sizelimit)
	logg("ScanOnAccess: Max file size limited to %d bytes\n", sizelimit);
    else
	logg("ScanOnAccess: File size limit disabled\n");

    extinfo = optget(tharg->opts, "ExtendedDetectionInfo")->enabled;

    FD_ZERO(&rfds);
    FD_SET(onas_fan_fd, &rfds);
    do {
	if (reload) sleep(1);
        ret = select(onas_fan_fd + 1, &rfds, NULL, NULL, NULL);
    } while((ret == -1 && errno == EINTR) || reload);


    time_t start = time(NULL) - 30;
    while(((bread = read(onas_fan_fd, buf, sizeof(buf))) > 0) || errno == EOVERFLOW) {

	if (errno == EOVERFLOW) {
		if (time(NULL) - start >= 30) {
			logg("!ScanOnAccess: Internal error (failed to read data) ... %s\n", strerror(errno));
			logg("!ScanOnAccess: File too large for fanotify ... recovering and continuing scans...\n");
			start = time(NULL);
		}

		errno = 0;
		continue;
	}

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

		if(onas_fan_checkowner(fmd->pid, tharg->opts)) {
		    scan = 0;
		    logg("*ScanOnAccess: %s skipped (excluded UID)\n", fname);
		}

		if(sizelimit) {
		    if(FSTAT(fmd->fd, &sb) != 0 || sb.st_size > sizelimit) {
			scan = 0;
			/* logg("*ScanOnAccess: %s skipped (size > %d)\n", fname, sizelimit); */
		    }
		}

		if(onas_fan_scanfile(onas_fan_fd, fname, fmd, scan, extinfo, tharg) == -1) {
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
	    if (reload) sleep(1);
	    ret = select(onas_fan_fd + 1, &rfds, NULL, NULL, NULL);
	} while((ret == -1 && errno == EINTR) || reload);
    }

    if(bread < 0)
	logg("!ScanOnAccess: Internal error (failed to read data) ... %s\n", strerror(errno));

    return NULL;
}