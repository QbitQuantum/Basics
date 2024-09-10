void spin_lock_rtm(int *lock)
{
	int i;
	unsigned status;
	unsigned retry = RETRY_OTHER;

	for (i = 0; i < retry; i++) {
		if ((status = _xbegin()) == _XBEGIN_STARTED) {
			if (lock_is_free(lock))
				return;
			_xabort(0xff);
		}
		trace_abort(status);
		if ((status & _XABORT_EXPLICIT) && _XABORT_CODE(status) == 0xff) {
			while (!lock_is_free(lock))
				pause();
		} else if (!(status & _XABORT_RETRY) && !(status & _XABORT_CAPACITY))
			break;

		if (status & _XABORT_CONFLICT) {
			retry = RETRY_CON;
			while (!lock_is_free(lock))
				pause();
			/* Could do various kinds of backoff here. */
		} else if (status & _XABORT_CAPACITY) {
			retry = RETRY_CAP;
		} else {
			retry = RETRY_OTHER;
		}
	}
	/* Could do adaptation here */

	while (__sync_sub_and_fetch(lock, 1) < 0) {
		do
			pause();
		while (!lock_is_free(lock));
		/* Could do respeculation here */
	}
}