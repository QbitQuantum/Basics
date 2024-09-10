  void test_find_and_activate_sleeping_does_not() {
    Thread* cur = Thread::current(state);
    Thread* thread = Thread::create(state);
    Thread* thread2 = Thread::create(state);
    
    thread->wakeup(state);
    thread2->wakeup(state);

    state->queue_thread(thread);
    state->queue_thread(thread2);
    thread->sleep(state, Qtrue);

    bool ret = state->find_and_activate_thread();
    TS_ASSERT_EQUALS(true, ret);

    TS_ASSERT_EQUALS(Qfalse, thread->queued());

    TS_ASSERT_EQUALS(thread2, Thread::current(state));

    TS_ASSERT_EQUALS(Qtrue, cur->queued());
  }