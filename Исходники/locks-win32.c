bool TRI_TryReadLockReadWriteLock (TRI_read_write_lock_t* lock) {
  return (TryAcquireSRWLockShared(&lock->_lock) != 0);
}