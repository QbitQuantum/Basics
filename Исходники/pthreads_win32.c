static
VOID CALLBACK pthreads_win32_unnotice(void* parameter, BOOLEAN timerOrWait)
{
  pthread_t pth = parameter;
  pthread_t self = tls_impersonate(pth);

  tls_call_destructors();
  CloseHandle(pth->handle);
  /*
  if (pth->fiber && pth->own_fiber) {
    DeleteFiber(pth->fiber);
    } */
  UnregisterWait(pth->wait_handle);

  tls_impersonate(self);
  pthread_mutex_destroy(&pth->fiber_lock);
  pthread_mutex_destroy(&pth->lock);
  free(pth);
}