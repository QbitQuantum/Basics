bool InternalThread::createThread()
{
    thread_printf("%s[%d]  welcome to createThread(%s)\n", __FILE__, __LINE__, idstr);
  if (isRunning()) {
     fprintf(stderr, "%s[%d]:  WARNING:  cannot create thread '%s'which is already running\n", 
             __FILE__, __LINE__, idstr);
     return true;
  }
  
  startupLock = new eventLock();
  startupLock->_Lock(__FILE__, __LINE__);

#if defined(os_windows)
  handler_thread = _beginthread(eventHandlerWrapper, 0, (void *) this);
  if (-1L == handler_thread) {
    bperr("%s[%d]:  _beginthread(...) failed\n", __FILE__, __LINE__);
    return false;
  }
#else  // Unixes

  int err = 0;
  pthread_attr_t handler_thread_attr;

  err = pthread_attr_init(&handler_thread_attr);
  if (err) {
    bperr("%s[%d]:  could not init async handler thread attributes: %s, %d\n",
          __FILE__, __LINE__, strerror(err), err);
    return false;
  }

  err = pthread_attr_setdetachstate(&handler_thread_attr, PTHREAD_CREATE_DETACHED);
  if (err) {
    bperr("%s[%d]:  could not set async handler thread attrixibcutes: %s, %d\n",
          __FILE__, __LINE__, strerror(err), err);
    return false;
  }

  try {
  err = pthread_create(&handler_thread, &handler_thread_attr,
                       &eventHandlerWrapper, (void *) this);
  if (err) {
    bperr("%s[%d]:  could not start async handler thread: %s, %d\n",
          __FILE__, __LINE__, strerror(err), err);
    fprintf(stderr,"%s[%d]:  could not start async handler thread: %s, %d\n",
          __FILE__, __LINE__, strerror(err), err);
    return false;
  }
  } catch(...) {
    assert(0);
  }

  err = pthread_attr_destroy(&handler_thread_attr);
  if (err) {
    bperr("%s[%d]:  could not destroy async handler attr: %s, %d\n",
          __FILE__, __LINE__, strerror(err), err);
    return false;
  }
#endif

  while (!_isRunning && (init_ok)) {
      thread_printf("%s[%d]:  createThread (%s) waiting for thread main to start\n", __FILE__, __LINE__, idstr);
      startupLock->_WaitForSignal(__FILE__, __LINE__);
      thread_printf("%s[%d]:  createThread (%s) got signal\n", __FILE__, __LINE__, idstr);
  }
  startupLock->_Unlock(__FILE__, __LINE__);

  thread_printf("%s[%d]: createThread returning %d\n", FILE__, __LINE__, init_ok);

  if (!init_ok) {
    return false;
  }
  return true;

}