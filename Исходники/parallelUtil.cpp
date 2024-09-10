bool multiMutex::trylock(unsigned long key, size_t& nLock)
{
  bool status(true);
  namedLock *pLock(NULL);

  if (pthread_mutex_lock(&controlMutex_))
    throw std::runtime_error("multiMutex::lock: pthread_mutex_lock error return");

  for (size_t n=0; n < N_locks_; ++n){
	  namedLock& cLock(vLock_[n]);

	  // Either find an already assigned named lock, or
	  //   return the first available named lock.
	  if (key == cLock.key_){
		  // there already is a matching lock:
		  pLock = &cLock;
		  nLock = n;
		  break;
	  }	 
	  else	 
	  if ((NULL == pLock) && (static_cast<unsigned long>(NULL) == cLock.key_)){
      // first available lock:
		  pLock = &cLock;
		  nLock = n;
	  }
  }

  if (NULL == pLock)
    throw std::runtime_error("multiMutex::lock: no new lock available");
  // This case should probably be a throw -- it will segfault next...
  // Either there are fewer locks than threads, or a thread took a lock
  //   for another key and didn't give it back.

  if (static_cast<unsigned long>(NULL) == pLock->key_)
	  pLock->key_ = key; // name the lock.

  // note: this also will work with recursive mutexes:		 
  ++pLock->refCount_;

  if (pthread_mutex_unlock(&controlMutex_))
    throw std::runtime_error("multiMutex::lock: pthread_mutex_unlock error return");

  // attempt to lock the mutex:
  int N_STAT(0);
  if ((N_STAT = pthread_mutex_trylock(&pLock->mutex_))){
    if (N_STAT == EBUSY)
      status = false; // mutex is locked
    else
      throw std::runtime_error("multiMutex::trylock: pthread_mutex_trylock error return");
  }
  else{
    pLock->tid_ = pthread_self();
    assert(pLock->tid_ != 0);
  }

  return status;
}