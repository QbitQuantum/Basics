static int winMutexTry(sqlite3_mutex *p){
  int rc = SQLITE_BUSY;
  assert( p->id==SQLITE_MUTEX_RECURSIVE || winMutexNotheld(p) );
  /*
  ** The sqlite3_mutex_try() routine is very rarely used, and when it
  ** is used it is merely an optimization.  So it is OK for it to always
  ** fail.  
  **
  ** The TryEnterCriticalSection() interface is only available on WinNT.
  ** And some windows compilers complain if you try to use it without
  ** first doing some #defines that prevent SQLite from building on Win98.
  ** For that reason, we will omit this optimization for now.  See
  ** ticket #2685.
  */
#if 0
  if( mutexIsNT() && TryEnterCriticalSection(&p->mutex) ){
    p->owner = GetCurrentThreadId();
    p->nRef++;
    rc = SQLITE_OK;
  }
#endif
  return rc;
}