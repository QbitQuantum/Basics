int mzrt_sema_post(mzrt_sema *s)
{
  ReleaseSemaphore(s->ws, 1, NULL);  
  return 0;
}