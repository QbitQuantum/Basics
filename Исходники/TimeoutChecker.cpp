// Returns the time the current thread has spent executing, in milliseconds.
static inline unsigned getCPUTime()
{
#if OS(DARWIN)
    mach_msg_type_number_t infoCount = THREAD_BASIC_INFO_COUNT;
    thread_basic_info_data_t info;

    // Get thread information
    mach_port_t threadPort = mach_thread_self();
    thread_info(threadPort, THREAD_BASIC_INFO, reinterpret_cast<thread_info_t>(&info), &infoCount);
    mach_port_deallocate(mach_task_self(), threadPort);
    
    unsigned time = info.user_time.seconds * 1000 + info.user_time.microseconds / 1000;
    time += info.system_time.seconds * 1000 + info.system_time.microseconds / 1000;
    
    return time;
#elif OS(WINDOWS)
    union {
        FILETIME fileTime;
        unsigned long long fileTimeAsLong;
    } userTime, kernelTime;
    
    // GetThreadTimes won't accept NULL arguments so we pass these even though
    // they're not used.
    FILETIME creationTime, exitTime;
    
    GetThreadTimes(GetCurrentThread(), &creationTime, &exitTime, &kernelTime.fileTime, &userTime.fileTime);
    
    return static_cast<unsigned>(userTime.fileTimeAsLong / 10000 + kernelTime.fileTimeAsLong / 10000);
#elif OS(SYMBIAN)
    RThread current;
    TTimeIntervalMicroSeconds cpuTime;

    TInt err = current.GetCpuTime(cpuTime);
    ASSERT_WITH_MESSAGE(err == KErrNone, "GetCpuTime failed with %d", err);
    return cpuTime.Int64() / 1000;
#elif PLATFORM(BREWMP)
    // This function returns a continuously and linearly increasing millisecond
    // timer from the time the device was powered on.
    // There is only one thread in BREW, so this is enough.
    return GETUPTIMEMS();
#else
    // FIXME: We should return the time the current thread has spent executing.
    return currentTime() * 1000;
#endif
}