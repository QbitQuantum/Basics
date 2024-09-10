pthread_t pthread_self(void)
{
  pthread_t t;
	
  _pthread_once_raw(&_pthread_tls_once, pthread_tls_init);
	
  t = (pthread_t)TlsGetValue(_pthread_tls);
	
  /* Main thread? */
  if (!t)
    {
      t = (pthread_t)malloc(sizeof(struct _pthread_v));
		
      /* If cannot initialize main thread, then the only thing we can do is abort */
      if (!t) abort();
	
      t->ret_arg = NULL;
      t->func = NULL;
      t->clean = NULL;
      t->cancelled = 0;
      t->p_state = PTHREAD_DEFAULT_ATTR;
      t->keymax = 0;
      t->keyval = NULL;
      t->h = GetCurrentThread();
		
      /* Save for later */
      TlsSetValue(_pthread_tls, t);
		
      if (setjmp(t->jb))
	{
	  /* Make sure we free ourselves if we are detached */
	  if (!t->h) free(t);
			
	  /* Time to die */
	  _endthreadex(0);
	}
    }
	
  return t;
}