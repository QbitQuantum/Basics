void txn()
{
	int status;
	if ((status = _xbegin()) == _XBEGIN_STARTED) {
		count++;
		// TODO - 
		// omitting xend should not cause a "deadlock" in which the
		// second thread "blocks" forever at xbegin,
		// but rather should force the 1st txn to abort.
		// double bonus TODO: how should we behave if the "last" thread
		// exits w/o xending, without any contender to abort it?
		// _xend();
	} else {
		mutex_lock(&lock);
		count++;
		mutex_unlock(&lock);
	}
}