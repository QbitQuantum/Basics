int
main()
{
  pthread_t t;
  pthread_attr_t attr;
  void * result = NULL;
  struct sched_param param;

  assert((maxPrio = sched_get_priority_max(SCHED_OTHER)) != -1);
  assert((minPrio = sched_get_priority_min(SCHED_OTHER)) != -1);

  assert(pthread_create(&t, NULL, getValidPriorities, NULL) == 0);
  assert(pthread_join(t, &result) == 0);

  assert(pthread_attr_init(&attr) == 0);
  assert(pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED) == 0);

  /* Set the thread's priority to a known initial value. */
  SetThreadPriority(pthread_getw32threadhandle_np(pthread_self()),
                    PTW32TEST_THREAD_INIT_PRIO);

  printf("Using pthread_getschedparam\n");
  printf("%10s %10s %10s\n", "Set value", "Get value", "Win priority");

  for (param.sched_priority = minPrio;
       param.sched_priority <= maxPrio;
       param.sched_priority++)
    {
      int prio;

      assert(pthread_attr_setschedparam(&attr, &param) == 0);
      assert(pthread_create(&t, &attr, func, (void *) &attr) == 0);

      assert((prio = GetThreadPriority(pthread_getw32threadhandle_np(t)))
             == validPriorities[param.sched_priority+(PTW32TEST_MAXPRIORITIES/2)]);

      assert(pthread_join(t, &result) == 0);

      assert(param.sched_priority == (int)(size_t) result);
      printf("%10d %10d %10d\n", param.sched_priority, (int)(size_t) result, prio);
    }

  return 0;
}