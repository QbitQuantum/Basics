/*
 * Usage: verror(priority, name, format, args...);
 * NB: don't pass more than 8K per call
 */
void verror(int priority, char *name, char *fmt, ...) {
    char buf[8192], tbuf[100], *bufp = buf;
    va_list args;
    time_t t = time(NULL);
    size_t l;
    static time_t last_time = 0;

    /* To improve error reporting */
    if (priority == ERR_FATAL && t - last_time > 10)
	dump_tcl_stack();
    last_time = t;

    if (noisy) bell();
    fflush(stdout);

    va_start(args, fmt);

    /* Use static buffer for small output */
    if ((l = vflen(fmt, args)) > 8192 - sizeof(tbuf)+2) {
	if (NULL == (bufp = (char *)xmalloc(l + sizeof(tbuf)+2))) {
	    verror(ERR_FATAL, "verror", "out of memory");
	    return;
	}
    }

    strftime(tbuf, sizeof(tbuf)-1, "%a %d %b %H:%M:%S %Y", localtime(&t));
    sprintf(bufp, "%s %s: ", tbuf, name);

    if (priority == ERR_FATAL && win_init) {
	fputs(bufp, stderr);
	vfprintf(stderr, fmt, args);
	fputc('\n', stderr);
    }

    l = strlen(bufp);
    vsprintf(&bufp[l], fmt, args);
    log_file(NULL, &bufp[l]);
    strcat(&bufp[l], "\n");
#ifdef _WIN32
    if (priority == ERR_FATAL) {
    /* 7/1/99 johnt - log the messages to the Event Viewer on windows, as we don't always have stderr */
    char *a[] = {bufp};
    if( !eventLogHandle){
	eventLogHandle = RegisterEventSource(NULL,EVENT_SOURCE); /* get default application handle */
    }
    ReportEvent(eventLogHandle,
	priority==ERR_FATAL?EVENTLOG_ERROR_TYPE:EVENTLOG_WARNING_TYPE,
	0,
	0,
	NULL,
	1,
	0,
	a,
	NULL);
    }
#endif
    tout_update_stream(2, bufp, 0, NULL);

    if (bufp != buf) {
	xfree(bufp);
    }

    va_end(args);
}