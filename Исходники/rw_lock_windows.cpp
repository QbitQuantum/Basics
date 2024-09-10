Error RWLockWindows::read_try_lock() {

	if (TryAcquireSRWLockShared(&lock) == 0) {
		return ERR_BUSY;
	} else {
		return OK;
	}
}