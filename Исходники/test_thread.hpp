  void test_exited() {
    Thread* cur = Thread::current(state);
    Thread* thr = Thread::create(state);
    Thread* thr2 = Thread::create(state);

    thr->wakeup(state);
    thr2->wakeup(state);

    state->queue_thread(thr);
    state->activate_thread(thr2);


    TS_ASSERT_EQUALS(thr2, Thread::current(state));
    TS_ASSERT_EQUALS(Qtrue, thr2->alive());

    TS_ASSERT_EQUALS(Qtrue, thr->alive());
    TS_ASSERT_EQUALS(Qfalse, thr->sleep());
    TS_ASSERT_EQUALS(Qtrue, thr->queued());

    thr->exited(state);

    TS_ASSERT_EQUALS(thr2, Thread::current(state));

    TS_ASSERT_EQUALS(Qfalse, thr->alive());
    TS_ASSERT_EQUALS(Qfalse, thr->queued());

    thr2->exited(state);

    TS_ASSERT_EQUALS(cur, Thread::current(state));

    TS_ASSERT_EQUALS(Qfalse, thr->alive());
    TS_ASSERT_EQUALS(Qfalse, thr->queued());
  }