int
mono_sem_timedwait (MonoSemType *sem, guint32 timeout_ms, gboolean alertable)
{
	gboolean res;

	while ((res = WaitForSingleObjectEx (*sem, timeout_ms, alertable)) == WAIT_IO_COMPLETION) {
		if (alertable) {
			errno = EINTR;
			return -1;
		}
	}
	switch (res) {
	case WAIT_OBJECT_0:
		return 0;    
	// WAIT_TIMEOUT and WAIT_FAILED
	default:
		return -1;
	}
}