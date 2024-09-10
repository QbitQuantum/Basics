static int do_daemon_work(const char *channel, const char *sync_shutdown_file,
		   unsigned long timeout, unsigned long min_delta,
		   int *restartp)
{
    int r = 0;
    time_t session_start;
    time_t single_start;
    int    delta;
    struct stat sbuf;
    sync_log_reader_t *slr;

    *restartp = RESTART_NONE;
    slr = sync_log_reader_create_with_channel(channel);

    session_start = time(NULL);

    while (1) {
	single_start = time(NULL);

	signals_poll();

	/* Check for shutdown file */
	if (sync_shutdown_file && !stat(sync_shutdown_file, &sbuf)) {
	    unlink(sync_shutdown_file);
	    break;
	}

	/* See if its time to RESTART */
	if ((timeout > 0) &&
	    ((single_start - session_start) > (time_t) timeout)) {
	    *restartp = RESTART_NORMAL;
	    break;
	}

	r = sync_log_reader_begin(slr);
	if (r) {
	    /* including specifically r == IMAP_AGAIN */
	    if (min_delta > 0) {
		sleep(min_delta);
	    } else {
		usleep(100000);    /* 1/10th second */
	    }
	    continue;
	}

	/* Process the work log */
	if ((r=do_sync(slr))) {
	    syslog(LOG_ERR,
		   "Processing sync log file %s failed: %s",
		   sync_log_reader_get_file_name(slr), error_message(r));
	    break;
	}

	r = sync_log_reader_end(slr);
	if (r) break;

	delta = time(NULL) - single_start;

	if (((unsigned) delta < min_delta) && ((min_delta-delta) > 0))
	    sleep(min_delta-delta);
    }
    sync_log_reader_free(slr);

    if (*restartp == RESTART_NORMAL) {
	r = do_restart();
	if (r) {
	    syslog(LOG_ERR, "sync_client RESTART failed: %s",
		   error_message(r));
	} else {
	    syslog(LOG_INFO, "sync_client RESTART succeeded");
	}
	r = 0;
    }

    return(r);
}