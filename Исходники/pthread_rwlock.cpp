int pthread_rwlock_unlock(pthread_rwlock_t *l)
{
#ifndef PTHREAD_WIN_XP_SYNC
  void *state = *(void **)l;
	
  if (state == (void *) 1)
    {
      /* Known to be an exclusive lock */
      ReleaseSRWLockExclusive(l);
    }
  else
    {
      /* A shared unlock will work */
      ReleaseSRWLockShared(l);
    }
#else
  WaitForSingleObject(l->mutex,INFINITE);
  if(l->reader_count < 0)	// Known to be an exclusive lock 
    {
      l->reader_count = 0;
      if(l->nb_waiting_writer)	// writter have the priority
	ReleaseSemaphore(l->sema_write,1,NULL);	// Wakeup one writer
      else if(l->nb_waiting_reader)
	ReleaseSemaphore(l->sema_read,l->nb_waiting_reader,NULL); // Wake up all readers
    }
  else if(!--(l->reader_count) && l->nb_waiting_writer)	// maybe wake up one writer
    ReleaseSemaphore(l->sema_write,1,NULL);
  ReleaseMutex(l->mutex);
#endif
  return 0;
}