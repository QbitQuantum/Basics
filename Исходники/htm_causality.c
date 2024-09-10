void *child(void *dummy)
{
	int status;
retry:
	if ((status = _xbegin()) == _XBEGIN_STARTED) {
		count = 0;
		_xend();
	} else if ((status & _XABORT_RETRY) != 0) {
		assert(0 && "please run with -X -A -S to suppress retries");
		goto retry;
	} else {
		assert((status & _XABORT_CONFLICT) != 0 && "unexpected abort mode");
		// it would be a causality violation for this to be visible to
		// the parent's xadd, which has to happen first for us to abort
		__sync_fetch_and_add(&count, 1);
	}
	return NULL;
}