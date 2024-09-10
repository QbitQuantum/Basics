int zThread::getPriority() const
{
#if defined(_WIN32) || defined(_WIN64)
 zMutexLock m1(&m_zThread);
 if(pid > 0) return GetThreadPriority(hThread);
 return 0;
#else
#if defined(__GNUG__) || defined(__linux__) || defined(__CYGWIN__)
#ifndef __CYGWIN__
 zMutexLock m1(&m_zThread);
 if(pid > 0) return getpriority(PRIO_PROCESS,pid);
 return 0;
#else
return 1;
#endif
#endif
#endif
}