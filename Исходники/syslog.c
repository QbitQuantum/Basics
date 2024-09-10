void
vsyslogp_r(int pri, struct syslog_data *data, const char *msgid,
	const char *sdfmt, const char *msgfmt, va_list ap)
{
	static const char BRCOSP[] = "]: ";
	static const char CRLF[] = "\r\n";
	size_t cnt, prlen, tries;
	char ch, *p, *t;
	struct timeval tv;
	struct tm tmnow;
	time_t now;
	int fd, saved_errno;
#define TBUF_LEN	2048
#define FMT_LEN		1024
#define MAXTRIES	10
	char tbuf[TBUF_LEN], fmt_cpy[FMT_LEN], fmt_cat[FMT_LEN] = "";
	size_t tbuf_left, fmt_left, msgsdlen;
	char *fmt = fmt_cat;
	int signal_safe = pri & LOG_SIGNAL_SAFE;
	struct iovec iov[7];	/* prog + [ + pid + ]: + fmt + crlf */
	int opened, iovcnt;

	pri &= ~LOG_SIGNAL_SAFE;

#define INTERNALLOG	LOG_ERR|LOG_CONS|LOG_PERROR|LOG_PID
	/* Check for invalid bits. */
	if (pri & ~(LOG_PRIMASK|LOG_FACMASK)) {
		syslog_r(INTERNALLOG | signal_safe, data,
		    "syslog_r: unknown facility/priority: %x", pri);
		pri &= LOG_PRIMASK|LOG_FACMASK;
	}

	/* Check priority against setlogmask values. */
	if (!(LOG_MASK(LOG_PRI(pri)) & data->log_mask))
		return;

	saved_errno = errno;

	/* Set default facility if none specified. */
	if ((pri & LOG_FACMASK) == 0)
		pri |= data->log_fac;

	/* Build the message. */
	p = tbuf;
	tbuf_left = TBUF_LEN;

#define DEC()							\
	do {							\
		if (prlen >= tbuf_left)				\
			prlen = tbuf_left - 1;			\
		p += prlen;					\
		tbuf_left -= prlen;				\
	} while (/*CONSTCOND*/0)

	prlen = snprintf_ss(p, tbuf_left, "<%d>1 ", pri);
	DEC();

	if (!signal_safe && (gettimeofday(&tv, NULL) != -1)) {
		/* strftime() implies tzset(), localtime_r() doesn't. */
		tzset();
		now = (time_t) tv.tv_sec;
		localtime_r(&now, &tmnow);

		prlen = strftime(p, tbuf_left, "%FT%T", &tmnow);
		DEC();
		prlen = snprintf(p, tbuf_left, ".%06ld", (long)tv.tv_usec);
		DEC();
		prlen = strftime(p, tbuf_left-1, "%z", &tmnow);
		/* strftime gives eg. "+0200", but we need "+02:00" */
		if (prlen == 5) {
			p[prlen+1] = p[prlen];
			p[prlen]   = p[prlen-1];
			p[prlen-1] = p[prlen-2];
			p[prlen-2] = ':';
			prlen += 1;
		}
	} else {
		prlen = snprintf_ss(p, tbuf_left, "-");

		/* if gmtime_r() was signal-safe we could output the UTC-time:
		gmtime_r(&now, &tmnow);
		prlen = strftime(p, tbuf_left, "%FT%TZ", &tmnow);
		*/
	}
	DEC();
	prlen = snprintf_ss(p, tbuf_left, " %s ", hostname);
	DEC();

	if (data->log_tag == NULL)
		data->log_tag = getprogname();

	prlen = snprintf_ss(p, tbuf_left, "%s ",
	    data->log_tag ? data->log_tag : "-");
	if (data->log_stat & (LOG_PERROR|LOG_CONS)) {
		iovcnt = 0;
		iov[iovcnt].iov_base = p;
		iov[iovcnt].iov_len = prlen - 1;
		iovcnt++;
	}
	DEC();

	if (data->log_stat & LOG_PID) {
		prlen = snprintf_ss(p, tbuf_left, "%d ", getpid());
		if (data->log_stat & (LOG_PERROR|LOG_CONS)) {
			iov[iovcnt].iov_base = __UNCONST("[");
			iov[iovcnt].iov_len = 1;
			iovcnt++;
			iov[iovcnt].iov_base = p;
			iov[iovcnt].iov_len = prlen - 1;
			iovcnt++;
			iov[iovcnt].iov_base = __UNCONST(BRCOSP);
			iov[iovcnt].iov_len = 3;
			iovcnt++;
		}
	} else {
		prlen = snprintf_ss(p, tbuf_left, "- ");
		if (data->log_stat & (LOG_PERROR|LOG_CONS)) {
			iov[iovcnt].iov_base = __UNCONST(BRCOSP + 1);
			iov[iovcnt].iov_len = 2;
			iovcnt++;
		}
	}
	DEC();

	/*
	 * concat the format strings, then use one vsnprintf()
	 */
	if (msgid != NULL && *msgid != '\0') {
		strlcat(fmt_cat, msgid, FMT_LEN);
		strlcat(fmt_cat, " ", FMT_LEN);
	} else
		strlcat(fmt_cat, "- ", FMT_LEN);

	if (sdfmt != NULL && *sdfmt != '\0') {
		strlcat(fmt_cat, sdfmt, FMT_LEN);
	} else
		strlcat(fmt_cat, "-", FMT_LEN);

	if (data->log_stat & (LOG_PERROR|LOG_CONS))
		msgsdlen = strlen(fmt_cat) + 1;
	else
		msgsdlen = 0;	/* XXX: GCC */

	if (msgfmt != NULL && *msgfmt != '\0') {
		strlcat(fmt_cat, " ", FMT_LEN);
		strlcat(fmt_cat, msgfmt, FMT_LEN);
	}

	/*
	 * We wouldn't need this mess if printf handled %m, or if
	 * strerror() had been invented before syslog().
	 */
	for (t = fmt_cpy, fmt_left = FMT_LEN; (ch = *fmt) != '\0'; ++fmt) {
		if (ch == '%' && fmt[1] == 'm') {
			char ebuf[128];
			++fmt;
			if (signal_safe ||
			    strerror_r(saved_errno, ebuf, sizeof(ebuf)))
				prlen = snprintf_ss(t, fmt_left, "Error %d",
				    saved_errno);
			else
				prlen = snprintf_ss(t, fmt_left, "%s", ebuf);
			if (prlen >= fmt_left)
				prlen = fmt_left - 1;
			t += prlen;
			fmt_left -= prlen;
		} else if (ch == '%' && fmt[1] == '%' && fmt_left > 2) {
			*t++ = '%';
			*t++ = '%';
			fmt++;
			fmt_left -= 2;
		} else {
			if (fmt_left > 1) {
				*t++ = ch;
				fmt_left--;
			}
		}
	}
	*t = '\0';

	if (signal_safe)
		prlen = vsnprintf_ss(p, tbuf_left, fmt_cpy, ap);
	else
		prlen = vsnprintf(p, tbuf_left, fmt_cpy, ap);

	if (data->log_stat & (LOG_PERROR|LOG_CONS)) {
		iov[iovcnt].iov_base = p + msgsdlen;
		iov[iovcnt].iov_len = prlen - msgsdlen;
		iovcnt++;
	}

	DEC();
	cnt = p - tbuf;

	/* Output to stderr if requested. */
	if (data->log_stat & LOG_PERROR) {
		iov[iovcnt].iov_base = __UNCONST(CRLF + 1);
		iov[iovcnt].iov_len = 1;
		(void)writev(STDERR_FILENO, iov, iovcnt + 1);
	}

	/* Get connected, output the message to the local logger. */
#ifndef __minix
	if (data == &sdata)
		mutex_lock(&syslog_mutex);
#endif
	opened = !data->opened;
	if (opened)
		openlog_unlocked_r(data->log_tag, data->log_stat, 0, data);
	connectlog_r(data);

	/*
	 * If the send() failed, there are two likely scenarios:
	 *  1) syslogd was restarted
	 *  2) /dev/log is out of socket buffer space
	 * We attempt to reconnect to /dev/log to take care of
	 * case #1 and keep send()ing data to cover case #2
	 * to give syslogd a chance to empty its socket buffer.
	 */
	for (tries = 0; tries < MAXTRIES; tries++) {
		if (send(data->log_file, tbuf, cnt, 0) != -1)
			break;
		if (errno != ENOBUFS) {
			disconnectlog_r(data);
			connectlog_r(data);
		} else
			(void)usleep(1);
	}

	/*
	 * Output the message to the console; try not to block
	 * as a blocking console should not stop other processes.
	 * Make sure the error reported is the one from the syslogd failure.
	 */
	if (tries == MAXTRIES && (data->log_stat & LOG_CONS) &&
	    (fd = open(_PATH_CONSOLE, O_WRONLY|O_NONBLOCK, 0)) >= 0) {
		iov[iovcnt].iov_base = __UNCONST(CRLF);
		iov[iovcnt].iov_len = 2;
		(void)writev(fd, iov, iovcnt + 1);
		(void)close(fd);
	}

#ifndef __minix
	if (data == &sdata)
		mutex_unlock(&syslog_mutex);
#endif

	if (data != &sdata && opened) {
		/* preserve log tag */
		const char *ident = data->log_tag;
		closelog_r(data);
		data->log_tag = ident;
	}
}