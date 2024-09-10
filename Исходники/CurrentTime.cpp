double currentCPUTime()
{
#if OS(DARWIN)
    mach_msg_type_number_t infoCount = THREAD_BASIC_INFO_COUNT;
    thread_basic_info_data_t info;

    // Get thread information
    mach_port_t threadPort = mach_thread_self();
    thread_info(threadPort, THREAD_BASIC_INFO, reinterpret_cast<thread_info_t>(&info), &infoCount);
    mach_port_deallocate(mach_task_self(), threadPort);
    
    double time = info.user_time.seconds + info.user_time.microseconds / 1000000.;
    time += info.system_time.seconds + info.system_time.microseconds / 1000000.;
    
    return time;
#elif OS(WINDOWS)
    union {
        FILETIME fileTime;
        unsigned long long fileTimeAsLong;
    } userTime, kernelTime;
    
    // GetThreadTimes won't accept null arguments so we pass these even though
    // they're not used.
    FILETIME creationTime, exitTime;
    
    GetThreadTimes(GetCurrentThread(), &creationTime, &exitTime, &kernelTime.fileTime, &userTime.fileTime);
    
    return userTime.fileTimeAsLong / 10000000. + kernelTime.fileTimeAsLong / 10000000.;
#elif OS(QNX)
    struct timespec time;
    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time))
        CRASH();
    return time.tv_sec + time.tv_nsec / 1.0e9;
#else
    // FIXME: We should return the time the current thread has spent executing.

    // use a relative time from first call in order to avoid an overflow
    static double firstTime = currentTime();
    return currentTime() - firstTime;
#endif
}