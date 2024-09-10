int main(int argc, char *argv[])
{
    extern char *optarg;
    int opt;
    char *alt_config = NULL, *port = "119";
    const char *peer = NULL, *server = "localhost", *wildmat = "*";
    char *authname = NULL, *password = NULL;
    int psock = -1, ssock = -1;
    struct protstream *pin, *pout, *sin, *sout;
    char buf[BUFFERSIZE];
    char sfile[1024] = "";
    int fd = -1, i, n, offered, rejected, accepted, failed;
    time_t stamp;
    char **resp = NULL;
    int newnews = 1;
    char *datefmt = "%y%m%d %H%M%S";

    if (geteuid() == 0) fatal("must run as the Cyrus user", EC_USAGE);

    while ((opt = getopt(argc, argv, "C:s:w:f:a:p:ny")) != EOF) {
	switch (opt) {
	case 'C': /* alt config file */
	    alt_config = optarg;
	    break;

	case 's': /* server */
	    server = xstrdup(optarg);
	    if ((port = strchr(server, ':')))
		*port++ = '\0';
	    else
		port = "119";
	    break;

	case 'w': /* wildmat */
	    wildmat = optarg;
	    break;

	case 'f': /* timestamp file */
	    snprintf(sfile, sizeof(sfile), optarg);
	    break;

	case 'a': /* authname */
	    authname = optarg;
	    break;

	case 'p': /* password */
	    password = optarg;
	    break;

	case 'n': /* no newnews */
	    newnews = 0;
	    break;

	case 'y': /* newsserver is y2k compliant */
	    datefmt = "%Y%m%d %H%M%S";
	    break;

	default:
	    usage();
	    /* NOTREACHED */
	}
    }
    if (argc - optind < 1) {
	usage();
	/* NOTREACHED */
    }

    peer = argv[optind++];

    cyrus_init(alt_config, "fetchnews", 0);

    /* connect to the peer */
    /* xxx configurable port number? */
    if ((psock = init_net(peer, "119", &pin, &pout)) < 0) {
	fprintf(stderr, "connection to %s failed\n", peer);
	cyrus_done();
	exit(-1);
    }

    /* read the initial greeting */
    if (!prot_fgets(buf, sizeof(buf), pin) || strncmp("20", buf, 2)) {
	syslog(LOG_ERR, "peer not available");
	goto quit;
    }

    if (authname) {
	/* authenticate to peer */
	/* XXX this should be modified to support SASL and STARTTLS */

	prot_printf(pout, "AUTHINFO USER %s\r\n", authname);
	if (!prot_fgets(buf, sizeof(buf), pin)) {
	    syslog(LOG_ERR, "AUTHINFO USER terminated abnormally");
	    goto quit;
	}
	else if (!strncmp("381", buf, 3)) {
	    /* password required */
	    if (!password)
		password = getpass("Please enter the password: "******"failed to get password\n");
		goto quit;
	    }

	    prot_printf(pout, "AUTHINFO PASS %s\r\n", password);
	    if (!prot_fgets(buf, sizeof(buf), pin)) {
		syslog(LOG_ERR, "AUTHINFO PASS terminated abnormally");
		goto quit;
	    }
	}

	if (strncmp("281", buf, 3)) {
	    /* auth failed */
	    goto quit;
	}
    }

    /* change to reader mode - not always necessary, so ignore result */
    prot_printf(pout, "MODE READER\r\n");
    prot_fgets(buf, sizeof(buf), pin);

    if (newnews) {
	struct tm ctime, *ptime;

	/* fetch the server's current time */
	prot_printf(pout, "DATE\r\n");

	if (!prot_fgets(buf, sizeof(buf), pin) || strncmp("111 ", buf, 4)) {
	    syslog(LOG_ERR, "error fetching DATE");
	    goto quit;
	}

	/* parse and normalize the server time */
	memset(&ctime, 0, sizeof(struct tm));
	sscanf(buf+4, "%4d%02d%02d%02d%02d%02d",
	       &ctime.tm_year, &ctime.tm_mon, &ctime.tm_mday,
	       &ctime.tm_hour, &ctime.tm_min, &ctime.tm_sec);
	ctime.tm_year -= 1900;
	ctime.tm_mon--;
	ctime.tm_isdst = -1;

	/* read the previous timestamp */
	if (!sfile[0]) {
	    char oldfile[1024];

	    snprintf(sfile, sizeof(sfile), "%s/fetchnews.stamp", config_dir);

	    /* upgrade from the old stamp filename to the new */
	    snprintf(oldfile, sizeof(oldfile), "%s/newsstamp", config_dir);
	    rename(oldfile, sfile);
	}

	if ((fd = open(sfile, O_RDWR | O_CREAT, 0644)) == -1) {
	    syslog(LOG_ERR, "can not open %s", sfile);
	    goto quit;
	}
	if (lock_nonblocking(fd) == -1) {
	    syslog(LOG_ERR, "can not lock %s: %m", sfile);
	    goto quit;
	}

	if (read(fd, &stamp, sizeof(stamp)) < sizeof(stamp)) {
	    /* XXX do something better here */
	    stamp = 0;
	}

	/* ask for new articles */
	if (stamp) stamp -= 180; /* adjust back 3 minutes */
	ptime = gmtime(&stamp);
	ptime->tm_isdst = -1;
	strftime(buf, sizeof(buf), datefmt, ptime);
	prot_printf(pout, "NEWNEWS %s %s GMT\r\n", wildmat, buf);
	
	if (!prot_fgets(buf, sizeof(buf), pin) || strncmp("230", buf, 3)) {
	    syslog(LOG_ERR, "peer doesn't support NEWNEWS");
	    newnews = 0;
	}

	/* prepare server's current time as new timestamp */
	stamp = mktime(&ctime);
	/* adjust for local timezone

	   XXX  We need to do this because we use gmtime() above.
	   We can't change this, otherwise we'd be incompatible
	   with an old localtime timestamp.
	*/
	stamp += gmtoff_of(&ctime, stamp);
    }

    if (!newnews) {
	prot_printf(pout, "LIST ACTIVE %s\r\n", wildmat);
	
	if (!prot_fgets(buf, sizeof(buf), pin) || strncmp("215", buf, 3)) {
	    syslog(LOG_ERR, "peer doesn't support LIST ACTIVE");
	    goto quit;
	}
    }

    /* process the NEWNEWS/LIST ACTIVE list */
    n = 0;
    while (prot_fgets(buf, sizeof(buf), pin)) {
	if (buf[0] == '.') break;

	if (!(n % RESP_GROW)) { /* time to alloc more */
	    resp = (char **)
		xrealloc(resp, (n + RESP_GROW) * sizeof(char *));
	}
	resp[n++] = xstrdup(buf);
    }
    if (buf[0] != '.') {
	syslog(LOG_ERR, "%s terminated abnormally",
	       newnews ? "NEWNEWS" : "LIST ACTIVE");
	goto quit;
    }

    if (!n) {
	/* nothing matches our wildmat */
	goto quit;
    }

    /* connect to the server */
    if ((ssock = init_net(server, port, &sin, &sout)) < 0) {
	fprintf(stderr, "connection to %s failed\n", server);
	goto quit;
    }

    /* read the initial greeting */
    if (!prot_fgets(buf, sizeof(buf), sin) || strncmp("20", buf, 2)) {
	syslog(LOG_ERR, "server not available");
	goto quit;
    }

    /* fetch and store articles */
    offered = rejected = accepted = failed = 0;
    if (newnews) {
	/* response is a list of msgids */
	for (i = 0; i < n; i++) {
	    /* find the end of the msgid */
	    *(strrchr(resp[i], '>') + 1) = '\0';

	    offered++;
	    if (fetch(resp[i], 1, pin, pout, sin, sout,
		      &rejected, &accepted, &failed)) {
		goto quit;
	    }
	}

	/* write the current timestamp */
	lseek(fd, 0, SEEK_SET);
	if (write(fd, &stamp, sizeof(stamp)) < sizeof(stamp))
	    syslog(LOG_ERR, "error writing %s", sfile);
	lock_unlock(fd);
	close(fd);
    }
    else {
	char group[BUFFERSIZE], msgid[BUFFERSIZE], lastbuf[50];
	const char *data;
	unsigned long low, high, last, cur;
	int start;
	int datalen;
	struct txn *tid = NULL;

	newsrc_init(NULL, 0);

	/*
	 * response is a list of groups.
	 * select each group, and STAT each article we haven't seen yet.
	 */
	for (i = 0; i < n; i++) {
	    /* parse the LIST ACTIVE response */
	    sscanf(resp[i], "%s %lu %lu", group, &high, &low);

	    last = 0;
	    if (!DB->fetchlock(newsrc_db, group, strlen(group),
			       &data, &datalen, &tid)) {
		last = strtoul(data, NULL, 10);
	    }
	    if (high <= last) continue;

	    /* select the group */
	    prot_printf(pout, "GROUP %s\r\n", group);
	    if (!prot_fgets(buf, sizeof(buf), pin)) {
		syslog(LOG_ERR, "GROUP terminated abnormally");
		continue;
	    }
	    else if (strncmp("211", buf, 3)) break;

	    for (start = 1, cur = low > last ? low : ++last;; cur++) {
		if (start) {
		    /* STAT the first article we haven't seen */
		    prot_printf(pout, "STAT %lu\r\n", cur);
		} else {
		    /* continue with the NEXT article */
		    prot_printf(pout, "NEXT\r\n");
		}

		if (!prot_fgets(buf, sizeof(buf), pin)) {
		    syslog(LOG_ERR, "STAT/NEXT terminated abnormally");
		    cur--;
		    break;
		}
		if (!strncmp("223", buf, 3)) {
		    /* parse the STAT/NEXT response */
		    sscanf(buf, "223 %lu %s", &cur, msgid);

		    /* find the end of the msgid */
		    *(strrchr(msgid, '>') + 1) = '\0';

		    if (fetch(msgid, 0, pin, pout, sin, sout,
			      &rejected, &accepted, &failed)) {
			cur--;
			break;
		    }
		    offered++;
		    start = 0;
		}

		/* have we reached the highwater mark? */
		if (cur >= high) break;
	    }

	    snprintf(lastbuf, sizeof(lastbuf), "%lu", cur);
	    DB->store(newsrc_db, group, strlen(group),
		      lastbuf, strlen(lastbuf)+1, &tid);
	}

	if (tid) DB->commit(newsrc_db, tid);
	newsrc_done();
    }

    syslog(LOG_NOTICE,
	   "fetchnews: %s offered %d; %s rejected %d, accepted %d, failed %d",
	   peer, offered, server, rejected, accepted, failed);

  quit:
    if (psock >= 0) {
	prot_printf(pout, "QUIT\r\n");
	prot_flush(pout);

	/* Flush the incoming buffer */
	prot_NONBLOCK(pin);
	prot_fill(pin);

	/* close/free socket & prot layer */
	close(psock);
    
	prot_free(pin);
	prot_free(pout);
    }

    if (ssock >= 0) {
	prot_printf(sout, "QUIT\r\n");
	prot_flush(sout);

	/* Flush the incoming buffer */
	prot_NONBLOCK(sin);
	prot_fill(sin);

	/* close/free socket & prot layer */
	close(psock);
    
	prot_free(sin);
	prot_free(sout);
    }

    cyrus_done();
    
    return 0;
}