static void qmgr_trigger_event(char *buf, int len,
			               char *unused_service, char **argv)
{
    int     incoming_flag = 0;
    int     deferred_flag = 0;
    int     i;

    /*
     * Sanity check. This service takes no command-line arguments.
     */
    if (argv[0])
	msg_fatal("unexpected command-line argument: %s", argv[0]);

    /*
     * Collapse identical requests that have arrived since we looked last
     * time. There is no client feedback so there is no need to process each
     * request in order. And as long as we don't have conflicting requests we
     * are free to sort them into the most suitable order.
     */
#define QMGR_FLUSH_BEFORE	(QMGR_FLUSH_ONCE | QMGR_FLUSH_DFXP)

    for (i = 0; i < len; i++) {
	if (msg_verbose)
	    msg_info("request: %d (%c)",
		     buf[i], ISALNUM(buf[i]) ? buf[i] : '?');
	switch (buf[i]) {
	case TRIGGER_REQ_WAKEUP:
	case QMGR_REQ_SCAN_INCOMING:
	    incoming_flag |= QMGR_SCAN_START;
	    break;
	case QMGR_REQ_SCAN_DEFERRED:
	    deferred_flag |= QMGR_SCAN_START;
	    break;
	case QMGR_REQ_FLUSH_DEAD:
	    deferred_flag |= QMGR_FLUSH_BEFORE;
	    incoming_flag |= QMGR_FLUSH_BEFORE;
	    break;
	case QMGR_REQ_SCAN_ALL:
	    deferred_flag |= QMGR_SCAN_ALL;
	    incoming_flag |= QMGR_SCAN_ALL;
	    break;
	default:
	    if (msg_verbose)
		msg_info("request ignored");
	    break;
	}
    }

    /*
     * Process each request type at most once. Modifiers take effect upon the
     * next queue run. If no queue run is in progress, and a queue scan is
     * requested, the request takes effect immediately.
     */
    if (incoming_flag != 0)
	qmgr_scan_request(qmgr_scans[QMGR_SCAN_IDX_INCOMING], incoming_flag);
    if (deferred_flag != 0)
	qmgr_scan_request(qmgr_scans[QMGR_SCAN_IDX_DEFERRED], deferred_flag);
}