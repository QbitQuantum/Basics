/*
 * This may be called from DllMain, and hence operates under unusual
 * constraints.
 */
static GC_thread GC_new_thread(void) {
  int i;
  /* It appears to be unsafe to acquire a lock here, since this	*/
  /* code is apparently not preeemptible on some systems.	*/
  /* (This is based on complaints, not on Microsoft's official	*/
  /* documentation, which says this should perform "only simple	*/
  /* initialization tasks".)					*/
  /* Hence we make do with nonblocking synchronization.		*/

  /* The following should be a noop according to the win32	*/
  /* documentation.  There is empirical evidence that it	*/
  /* isn't.		- HB					*/
# if defined(MPROTECT_VDB)
   if (GC_incremental) SetUnhandledExceptionFilter(GC_write_fault_handler);
# endif
                /* cast away volatile qualifier */
  for (i = 0; InterlockedExchange((IE_t)&thread_table[i].in_use,1) != 0; i++) {
    /* Compare-and-swap would make this cleaner, but that's not 	*/
    /* supported before Windows 98 and NT 4.0.  In Windows 2000,	*/
    /* InterlockedExchange is supposed to be replaced by		*/
    /* InterlockedExchangePointer, but that's not really what I		*/
    /* want here.							*/
    if (i == MAX_THREADS - 1)
      ABORT("too many threads");
  }
  /* Update GC_max_thread_index if necessary.  The following is safe,	*/
  /* and unlike CompareExchange-based solutions seems to work on all	*/
  /* Windows95 and later platforms.					*/
  /* Unfortunately, GC_max_thread_index may be temporarily out of 	*/
  /* bounds, so readers have to compensate.				*/
  while (i > GC_max_thread_index) {
    InterlockedIncrement((IE_t)&GC_max_thread_index);
  }
  if (GC_max_thread_index >= MAX_THREADS) {
    /* We overshot due to simultaneous increments.	*/
    /* Setting it to MAX_THREADS-1 is always safe.	*/
    GC_max_thread_index = MAX_THREADS - 1;
  }
  
# ifdef CYGWIN32
    thread_table[i].pthread_id = pthread_self();
# endif
  if (!DuplicateHandle(GetCurrentProcess(),
	               GetCurrentThread(),
		       GetCurrentProcess(),
		       (HANDLE*)&thread_table[i].handle,
		       0,
		       0,
		       DUPLICATE_SAME_ACCESS)) {
	DWORD last_error = GetLastError();
	GC_printf1("Last error code: %lx\n", last_error);
	ABORT("DuplicateHandle failed");
  }
  thread_table[i].stack_base = GC_get_stack_base();
  /* Up until this point, GC_push_all_stacks considers this thread	*/
  /* invalid.								*/
  if (thread_table[i].stack_base == NULL) 
    ABORT("Failed to find stack base in GC_new_thread");
  /* Up until this point, this entry is viewed as reserved but invalid	*/
  /* by GC_delete_thread.						*/
  thread_table[i].id = GetCurrentThreadId();
  /* If this thread is being created while we are trying to stop	*/
  /* the world, wait here.  Hopefully this can't happen on any	*/
  /* systems that don't allow us to block here.			*/
  while (GC_please_stop) Sleep(20);
  return thread_table + i;
}