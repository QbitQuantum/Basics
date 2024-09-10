/*
 * ptw32_throw
 *
 * All canceled and explicitly exited POSIX threads go through
 * here. This routine knows how to exit both POSIX initiated threads and
 * 'implicit' POSIX threads for each of the possible language modes (C,
 * C++, and SEH).
 */
void
ptw32_throw (DWORD exception)
{
  /*
   * Don't use pthread_self() to avoid creating an implicit POSIX thread handle
   * unnecessarily.
   */
  ptw32_thread_t * sp = (ptw32_thread_t *) pthread_getspecific (ptw32_selfThreadKey);

#ifdef __CLEANUP_SEH
  DWORD exceptionInformation[3];
#endif

  if (exception != PTW32_EPS_CANCEL && exception != PTW32_EPS_EXIT)
    {
      /* Should never enter here */
      exit (1);
    }

  if (NULL == sp || sp->implicit)
    {
      /*
       * We're inside a non-POSIX initialised Win32 thread
       * so there is no point to jump or throw back to. Just do an
       * explicit thread exit here after cleaning up POSIX
       * residue (i.e. cleanup handlers, POSIX thread handle etc).
       */
      void* exitCode = 0;

      switch (exception)
	{
	case PTW32_EPS_CANCEL:
	  exitCode = PTHREAD_CANCELED;
	  break;
	case PTW32_EPS_EXIT:
	  exitCode = sp->exitStatus;
	  break;
	}

#if defined(PTW32_STATIC_LIB)

      pthread_win32_thread_detach_np ();

#endif

#if ! defined (__MINGW32__) || defined (__MSVCRT__) || defined (__DMC__)
      _endthreadex ((unsigned)exitCode);
#else
      _endthread ();
#endif

    }

#ifdef __CLEANUP_SEH


  exceptionInformation[0] = (DWORD) (exception);
  exceptionInformation[1] = (DWORD) (0);
  exceptionInformation[2] = (DWORD) (0);

  RaiseException (EXCEPTION_PTW32_SERVICES, 0, 3, exceptionInformation);

#else /* __CLEANUP_SEH */

#ifdef __CLEANUP_C

  ptw32_pop_cleanup_all (1);
  longjmp (sp->start_mark, exception);

#else /* __CLEANUP_C */

#ifdef __CLEANUP_CXX

  switch (exception)
    {
    case PTW32_EPS_CANCEL:
      throw ptw32_exception_cancel ();
      break;
    case PTW32_EPS_EXIT:
      throw ptw32_exception_exit ();
      break;
    }

#else

#error ERROR [__FILE__, line __LINE__]: Cleanup type undefined.

#endif /* __CLEANUP_CXX */

#endif /* __CLEANUP_C */

#endif /* __CLEANUP_SEH */

  /* Never reached */
}