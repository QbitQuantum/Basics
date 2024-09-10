static int pthread_cond_signal(pthread_cond_t* const condition) {
  int ok = 1;
#ifdef USE_WINDOWS_CONDITION_VARIABLE
  WakeConditionVariable(condition);
#else
  if (WaitForSingleObject(condition->waiting_sem_, 0) == WAIT_OBJECT_0) {
    // a thread is waiting in pthread_cond_wait: allow it to be notified
    ok = SetEvent(condition->signal_event_);
    // wait until the event is consumed so the signaler cannot consume
    // the event via its own pthread_cond_wait.
    ok &= (WaitForSingleObject(condition->received_sem_, INFINITE) !=
           WAIT_OBJECT_0);
  }
#endif
  return !ok;
}