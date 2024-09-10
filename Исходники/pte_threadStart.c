int pte_threadStart (void *vthreadParms)
{
  ThreadParms * threadParms = (ThreadParms *) vthreadParms;
  pthread_t self;
  pte_thread_t * sp;
  void *(*start) (void *);
  void * arg;

#ifdef PTE_CLEANUP_C
#include <setjmp.h>

  int setjmp_rc;
#endif

  void * status = (void *) 0;

  self = threadParms->tid;
  sp = (pte_thread_t *) self.p;
  start = threadParms->start;
  arg = threadParms->arg;
//  free (threadParms);

  pthread_setspecific (pte_selfThreadKey, sp);

  sp->state = PThreadStateRunning;

#ifdef PTE_CLEANUP_C


  setjmp_rc = setjmp (sp->start_mark);


  if (0 == setjmp_rc)
    {

      /*
       * Run the caller's routine;
       */
      sp->exitStatus = status = (*start) (arg);
    }
  else
    {
      switch (setjmp_rc)
        {
        case PTE_EPS_CANCEL:
          status = sp->exitStatus = PTHREAD_CANCELED;
          break;
        case PTE_EPS_EXIT:
          status = sp->exitStatus;
          break;
        default:
          status = sp->exitStatus = PTHREAD_CANCELED;
          break;
        }
    }

#else /* PTE_CLEANUP_C */

#ifdef PTE_CLEANUP_CXX

  pte_oldTerminate = set_terminate (&pte_terminate);

  try
    {
      /*
      * Run the caller's routine in a nested try block so that we
      * can run the user's terminate function, which may call
      * pthread_exit() or be canceled.
      */
      try
        {
          status = sp->exitStatus = (*start) (arg);
        }
      catch (pte_exception &)
        {
          /*
          * Pass these through to the outer block.
          */
          throw;
        }
      catch (...)
        {
          /*
          * We want to run the user's terminate function if supplied.
          * That function may call pthread_exit() or be canceled, which will
          * be handled by the outer try block.
          *
          * pte_terminate() will be called if there is no user
          * supplied function.
          */

          terminate_function
          term_func = set_terminate (0);
          set_terminate (term_func);

          if (term_func != 0)
            {
              term_func ();
            }

          throw;
        }
    }
  catch (pte_exception_cancel &)
    {
      /*
      * Thread was canceled.
      */
      status = sp->exitStatus = PTHREAD_CANCELED;
    }
  catch (pte_exception_exit &)
    {
      /*
      * Thread was exited via pthread_exit().
      */
      status = sp->exitStatus;
    }
  catch (...)
    {
      /*
      * A system unexpected exception has occurred running the user's
      * terminate routine. We get control back within this block - cleanup
      * and release the exception out of thread scope.
      */
      status = sp->exitStatus = PTHREAD_CANCELED;
      (void) pthread_mutex_lock (&sp->cancelLock);
      sp->state = PThreadStateException;
      (void) pthread_mutex_unlock (&sp->cancelLock);
      (void) pte_thread_detach_np();
      (void) set_terminate (pte_oldTerminate);
      throw;

      /*
      * Never reached.
      */
    }

  (void) set_terminate (pte_oldTerminate);

#else

#error ERROR [__FILE__, line __LINE__]: Cleanup type undefined.

#endif /* PTE_CLEANUP_CXX */
#endif /* PTE_CLEANUP_C */

  /*
   * We need to cleanup the pthread now if we have
   * been statically linked, in which case the cleanup
   * in dllMain won't get done. Joinable threads will
   * only be partially cleaned up and must be fully cleaned
   * up by pthread_join() or pthread_detach().
   *
   * Note: if this library has been statically linked,
   * implicitly created pthreads (those created
   * for OS threads which have called pthreads routines)
   * must be cleaned up explicitly by the application
   * (by calling pte_thread_detach_np()).
   */
  (void) pte_thread_detach_and_exit_np ();

  //pte_osThreadExit(status);

  /*
   * Never reached.
   */

  return (unsigned) status;

}				/* pte_threadStart */