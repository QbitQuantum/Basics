void xbt_os_threadtimer_resume(xbt_os_timer_t timer)
{
#ifdef HAVE_POSIX_GETTIME
    timer->elapse.tv_sec += timer->stop.tv_sec - timer->start.tv_sec;
    timer->elapse.tv_nsec += timer->stop.tv_nsec - timer->start.tv_nsec;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &(timer->start));
#elif defined(HAVE_GETTIMEOFDAY) && defined(__MACH__) && defined(__APPLE__)
    timer->elapse.tv_sec += timer->stop.tv_sec - timer->start.tv_sec;
    timer->elapse.tv_usec += timer->stop.tv_usec - timer->start.tv_usec;
    mach_msg_type_number_t count = THREAD_BASIC_INFO_COUNT;
    thread_basic_info_data_t thi_data;
    thread_basic_info_t thi = &thi_data;
    thread_info(mach_thread_self(), THREAD_BASIC_INFO, (thread_info_t)thi, &count);
    timer->start.tv_usec =  thi->system_time.microseconds + thi->user_time.microseconds;
    timer->start.tv_sec = thi->system_time.seconds + thi->user_time.seconds;
#elif defined(HAVE_GETTIMEOFDAY)
    timer->elapse.tv_sec += timer->stop.tv_sec - timer->start.tv_sec;
    timer->elapse.tv_usec += timer->stop.tv_usec - timer->start.tv_usec;
    gettimeofday(&(timer->start), NULL);
#elif defined(_XBT_WIN32)
    timer->elapse.tv_sec += timer->stop.tv_sec - timer->start.tv_sec;
    timer->elapse.tv_usec += timer->stop.tv_usec - timer->start.tv_usec;
#  if defined(WIN32_WCE) || (_WIN32_WINNT < 0x0400)
    THROW_UNIMPLEMENTED;
#  else
    HANDLE h = GetCurrentThread();
    FILETIME creationTime, exitTime, kernelTime, userTime;
    GetThreadTimes(h, &creationTime, &exitTime, &kernelTime, &userTime);
    unsigned __int64 ktm, utm;
    ktm = (unsigned __int64) kernelTime.dwHighDateTime << 32;
    ktm |= kernelTime.dwLowDateTime;
    ktm /= 10;
    utm = (unsigned __int64) userTime.dwHighDateTime << 32;
    utm |= userTime.dwLowDateTime;
    utm /= 10;
    timer->start.tv_sec = (long) (ktm / 1000000L) + (long) (utm / 1000000L);
    timer->start.tv_usec = (long) (ktm % 1000000L) + (long) (utm % 1000000L);
#  endif                        /* windows version checker */
#endif
}