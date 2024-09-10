  std::exception_ptr TaskScheduler::thread_loop(size_t threadIndex)
  {
    /* allocate thread structure */
    std::unique_ptr<Thread> mthread(new Thread(threadIndex,this)); // too large for stack allocation
    Thread& thread = *mthread;
    threadLocal[threadIndex].store(&thread);
    Thread* oldThread = swapThread(&thread);

    /* main thread loop */
    while (anyTasksRunning)
    {
      steal_loop(thread,
                 [&] () { return anyTasksRunning > 0; },
                 [&] () {
                   anyTasksRunning++;
                   while (thread.tasks.execute_local_internal(thread,nullptr));
                   anyTasksRunning--;
                 });
    }
    threadLocal[threadIndex].store(nullptr);
    swapThread(oldThread);

    /* remember exception to throw */
    std::exception_ptr except = nullptr;
    if (cancellingException != nullptr) except = cancellingException;

    /* wait for all threads to terminate */
    threadCounter--;
#if defined(__WIN32__)
	size_t loopIndex = 1;
#endif
#define LOOP_YIELD_THRESHOLD (4096)
	while (threadCounter > 0) {
#if defined(__WIN32__)
          if ((loopIndex % LOOP_YIELD_THRESHOLD) == 0)
            yield();
          else
            _mm_pause();
	  loopIndex++;
#else
          yield();
#endif
	}
    return except;
  }