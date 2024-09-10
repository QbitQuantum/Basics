bool	CWAbsMutex::AMutexInit(thread_mutex mutext)
{
  InitializeCriticalSection((LPCRITICAL_SECTION)mutext);
  return (true);
}