int
pthread_cancel (pthread_t thread)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function requests cancellation of 'thread'.
      *
      * PARAMETERS
      *      thread
      *              reference to an instance of pthread_t
      *
      *
      * DESCRIPTION
      *      This function requests cancellation of 'thread'.
      *      NOTE: cancellation is asynchronous; use pthread_join to
      *                wait for termination of 'thread' if necessary.
      *
      * RESULTS
      *              0               successfully requested cancellation,
      *              ESRCH           no thread found corresponding to 'thread',
      *              ENOMEM          implicit self thread create failed.
      * ------------------------------------------------------
      */
{
  int result;
  int cancel_self;
  pthread_t self;

  /* This is the proper way to test thread validity. */
  result = pthread_kill(thread, 0);
  if (0 != result)
    {
      return result;
    }

  if ((self = pthread_self()) == NULL)
    {
      return ENOMEM;
    };

  /*
   * FIXME!!
   *
   * Can a thread cancel itself?
   *
   * The standard doesn't
   * specify an error to be returned if the target
   * thread is itself.
   *
   * If it may, then we need to ensure that a thread can't
   * deadlock itself trying to cancel itself asyncronously
   * (pthread_cancel is required to be an async-cancel
   * safe function).
   */
  cancel_self = pthread_equal(thread, self);

  /*
   * Lock for async-cancel safety.
   */
  (void) pthread_mutex_lock(&thread->cancelLock);

  if (thread->cancelType == PTHREAD_CANCEL_ASYNCHRONOUS
      && thread->cancelState == PTHREAD_CANCEL_ENABLE
      && thread->state < PThreadStateCanceling )
    {
      if (cancel_self)
        {
          thread->state = PThreadStateCanceling;
          thread->cancelState = PTHREAD_CANCEL_DISABLE;

          (void) pthread_mutex_unlock(&thread->cancelLock);
          ptw32_throw(PTW32_EPS_CANCEL);

          /* Never reached */
        }
      else
        {
          HANDLE threadH = thread->threadH;

          SuspendThread(threadH);

          if (WaitForSingleObject(threadH, 0) == WAIT_TIMEOUT )
            {
              CONTEXT context;

              thread->state = PThreadStateCanceling;
              thread->cancelState = PTHREAD_CANCEL_DISABLE;
              context.ContextFlags = CONTEXT_CONTROL;
              GetThreadContext(threadH, &context);
              PTW32_PROGCTR(context) = (DWORD) ptw32_cancel_self;
              SetThreadContext(threadH, &context);
              (void) pthread_mutex_unlock(&thread->cancelLock);
              ResumeThread(threadH);
            }
        }
    }
  else
    {
      /*
       * Set for deferred cancellation.
       */
      if ( thread->state >= PThreadStateCanceling
           || !SetEvent (thread->cancelEvent))
        {
          result = ESRCH;
        }

      (void) pthread_mutex_unlock(&thread->cancelLock);
    }

  return (result);
}