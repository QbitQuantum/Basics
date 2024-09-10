int pthread_cond_broadcast(pthread_cond_t *cond){
  if(TRUE == PulseEvent(*cond))
    return 0;
  else{
    DWORD ret = GetLastError();
    return (ret == 0)? -1 : ret;
  }
}