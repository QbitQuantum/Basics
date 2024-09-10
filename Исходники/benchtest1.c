int
main (int argc, char *argv[])
{
  int i = 0;
  CRITICAL_SECTION cs;
  old_mutex_t ox;
  pthread_mutexattr_init(&ma);

  printf( "=============================================================================\n");
  printf( "\nLock plus unlock on an unlocked mutex.\n%ld iterations\n\n",
          ITERATIONS);
  printf( "%-45s %15s %15s\n",
	    "Test",
	    "Total(msec)",
	    "average(usec)");
  printf( "-----------------------------------------------------------------------------\n");

  /*
   * Time the loop overhead so we can subtract it from the actual test times.
   */

  TESTSTART
  assert(1 == one);
  assert(1 == one);
  TESTSTOP

  durationMilliSecs = GetDurationMilliSecs(currSysTimeStart, currSysTimeStop) - overHeadMilliSecs;
  overHeadMilliSecs = durationMilliSecs;


  TESTSTART
  assert((dummy_call(&i), 1) == one);
  assert((dummy_call(&i), 1) == one);
  TESTSTOP

  durationMilliSecs = GetDurationMilliSecs(currSysTimeStart, currSysTimeStop) - overHeadMilliSecs;

  printf( "%-45s %15ld %15.3f\n",
	    "Dummy call x 2",
          durationMilliSecs,
          (float) durationMilliSecs * 1E3 / ITERATIONS);


  TESTSTART
  assert((interlocked_inc_with_conditionals(&i), 1) == one);
  assert((interlocked_dec_with_conditionals(&i), 1) == one);
  TESTSTOP

  durationMilliSecs = GetDurationMilliSecs(currSysTimeStart, currSysTimeStop) - overHeadMilliSecs;

  printf( "%-45s %15ld %15.3f\n",
	    "Dummy call -> Interlocked with cond x 2",
          durationMilliSecs,
          (float) durationMilliSecs * 1E3 / ITERATIONS);


  TESTSTART
  assert((InterlockedIncrement((LPLONG)&i), 1) == (LONG)one);
  assert((InterlockedDecrement((LPLONG)&i), 1) == (LONG)one);
  TESTSTOP

  durationMilliSecs = GetDurationMilliSecs(currSysTimeStart, currSysTimeStop) - overHeadMilliSecs;

  printf( "%-45s %15ld %15.3f\n",
	    "InterlockedOp x 2",
          durationMilliSecs,
          (float) durationMilliSecs * 1E3 / ITERATIONS);


  InitializeCriticalSection(&cs);

  TESTSTART
  assert((EnterCriticalSection(&cs), 1) == one);
  assert((LeaveCriticalSection(&cs), 1) == one);
  TESTSTOP

  DeleteCriticalSection(&cs);

  durationMilliSecs = GetDurationMilliSecs(currSysTimeStart, currSysTimeStop) - overHeadMilliSecs;

  printf( "%-45s %15ld %15.3f\n",
	    "Simple Critical Section",
          durationMilliSecs,
          (float) durationMilliSecs * 1E3 / ITERATIONS);


  old_mutex_use = OLD_WIN32CS;
  assert(old_mutex_init(&ox, NULL) == 0);

  TESTSTART
  assert(old_mutex_lock(&ox) == zero);
  assert(old_mutex_unlock(&ox) == zero);
  TESTSTOP

  assert(old_mutex_destroy(&ox) == 0);

  durationMilliSecs = GetDurationMilliSecs(currSysTimeStart, currSysTimeStop) - overHeadMilliSecs;

  printf( "%-45s %15ld %15.3f\n",
	    "Old PT Mutex using a Critical Section (WNT)",
          durationMilliSecs,
          (float) durationMilliSecs * 1E3 / ITERATIONS);


  old_mutex_use = OLD_WIN32MUTEX;
  assert(old_mutex_init(&ox, NULL) == 0);

  TESTSTART
  assert(old_mutex_lock(&ox) == zero);
  assert(old_mutex_unlock(&ox) == zero);
  TESTSTOP

  assert(old_mutex_destroy(&ox) == 0);

  durationMilliSecs = GetDurationMilliSecs(currSysTimeStart, currSysTimeStop) - overHeadMilliSecs;

  printf( "%-45s %15ld %15.3f\n",
	    "Old PT Mutex using a Win32 Mutex (W9x)",
          durationMilliSecs,
          (float) durationMilliSecs * 1E3 / ITERATIONS);

  printf( ".............................................................................\n");

  /*
   * Now we can start the actual tests
   */
#ifdef PTW32_MUTEX_TYPES
  runTest("PTHREAD_MUTEX_DEFAULT (W9x,WNT)", PTHREAD_MUTEX_DEFAULT);

  runTest("PTHREAD_MUTEX_NORMAL (W9x,WNT)", PTHREAD_MUTEX_NORMAL);

  runTest("PTHREAD_MUTEX_ERRORCHECK (W9x,WNT)", PTHREAD_MUTEX_ERRORCHECK);

  runTest("PTHREAD_MUTEX_RECURSIVE (W9x,WNT)", PTHREAD_MUTEX_RECURSIVE);
#else
  runTest("Non-blocking lock", 0);
#endif

  printf( "=============================================================================\n");

  /*
   * End of tests.
   */

  pthread_mutexattr_destroy(&ma);

  one = i; /* Dummy assignment to avoid 'variable unused' warning */
  return 0;
}