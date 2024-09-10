void
ptw32_callUserDestroyRoutines (pthread_t thread)
     /*
      * -------------------------------------------------------------------
      * DOCPRIVATE
      *
      * This the routine runs through all thread keys and calls
      * the destroy routines on the user's data for the current thread.
      * It simulates the behaviour of POSIX Threads.
      *
      * PARAMETERS
      *              thread
      *                      an instance of pthread_t
      *
      * RETURNS
      *              N/A
      * -------------------------------------------------------------------
      */
{
  ThreadKeyAssoc **
    nextP;
  ThreadKeyAssoc *
    assoc;

  if (thread != NULL)
    {
      /*
       * Run through all Thread<-->Key associations
       * for the current thread.
       * If the pthread_key_t still exits (ie the assoc->key
       * is not NULL) then call the user's TSD destroy routine.
       * Notes:
       *      If assoc->key is NULL, then the user previously called
       *      PThreadKeyDestroy. The association is now only referenced
       *      by the current thread and must be released; otherwise
       *      the assoc will be destroyed when the key is destroyed.
       */
      nextP = (ThreadKeyAssoc **) & (thread->keys);
      assoc = *nextP;

      while (assoc != NULL)
	{

	  if (pthread_mutex_lock (&(assoc->lock)) == 0)
	    {
	      pthread_key_t
		k;
	      if ((k = assoc->key) != NULL)
		{
		  /*
		   * Key still active; pthread_key_delete
		   * will block on this same mutex before
		   * it can release actual key; therefore,
		   * key is valid and we can call the destroy
		   * routine;
		   */
		  void *
		    value = NULL;

		  value = pthread_getspecific (k);
		  if (value != NULL && k->destructor != NULL)
		    {

#ifdef __cplusplus

		      try
		      {
			/*
			 * Run the caller's cleanup routine.
			 */
			(*(k->destructor)) (value);
		      }
		      catch (...)
		      {
			/*
			 * A system unexpected exception has occurred
			 * running the user's destructor.
			 * We get control back within this block in case
			 * the application has set up it's own terminate
			 * handler. Since we are leaving the thread we
			 * should not get any internal pthreads
			 * exceptions.
			 */
			terminate ();
		      }

#else /* __cplusplus */

		      /*
		       * Run the caller's cleanup routine.
		       */
		      (*(k->destructor)) (value);

#endif /* __cplusplus */
		    }
		}

	      /*
	       * mark assoc->thread as NULL to indicate the
	       * thread no longer references this association
	       */
	      assoc->thread = NULL;

	      /*
	       * Remove association from the pthread_t chain
	       */
	      *nextP = assoc->nextKey;

	      pthread_mutex_unlock (&(assoc->lock));

	      ptw32_tkAssocDestroy (assoc);

	      assoc = *nextP;
	    }
	}
    }

}				/* ptw32_callUserDestroyRoutines */