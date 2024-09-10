int64_t
os_time_get(void)
{
#if defined(PIPE_OS_UNIX)

   struct timeval tv;
   gettimeofday(&tv, NULL);
   return tv.tv_usec + tv.tv_sec*1000000LL;

#elif defined(PIPE_SUBSYSTEM_WINDOWS_DISPLAY)

   static LONGLONG frequency;
   LONGLONG counter;
   if(!frequency)
      EngQueryPerformanceFrequency(&frequency);
   EngQueryPerformanceCounter(&counter);
   return counter*INT64_C(1000000)/frequency;

#elif defined(PIPE_SUBSYSTEM_WINDOWS_USER) || defined(PIPE_SUBSYSTEM_WINDOWS_CE)

   static LARGE_INTEGER frequency;
   LARGE_INTEGER counter;
   if(!frequency.QuadPart)
      QueryPerformanceFrequency(&frequency);
   QueryPerformanceCounter(&counter);
   return counter.QuadPart*INT64_C(1000000)/frequency.QuadPart;

#elif defined(PIPE_SUBSYSTEM_WINDOWS_MINIPORT)

   /* Updated every 10 miliseconds, measured in units of 100 nanoseconds.
    * http://msdn.microsoft.com/en-us/library/ms801642.aspx */
   LARGE_INTEGER counter;
   KeQuerySystemTime(&counter);
   return counter.QuadPart/10;

#endif
}