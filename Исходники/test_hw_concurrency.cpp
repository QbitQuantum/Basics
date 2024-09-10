int TestMain () {
#if _WIN32||_WIN64 || __linux__ || __FreeBSD_version >= 701000
#if _WIN32||_WIN64
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    if ( si.dwNumberOfProcessors < 2 )
        return Harness::Skipped;
    int availableProcs = (int)si.dwNumberOfProcessors / 2;
    DWORD_PTR mask = 1;
    for ( int i = 1; i < availableProcs; ++i )
        mask |= mask << 1;
    bool err = !SetProcessAffinityMask( GetCurrentProcess(), mask );
#else /* !WIN */
#if __linux__
    int maxProcs = get_nprocs();
    typedef cpu_set_t mask_t;
#if __TBB_MAIN_THREAD_AFFINITY_BROKEN
    #define setaffinity(mask) sched_setaffinity(0 /*get the mask of the calling thread*/, sizeof(mask_t), &mask)
#else
    #define setaffinity(mask) sched_setaffinity(getpid(), sizeof(mask_t), &mask)
#endif
#else /* __FreeBSD__ */
    int maxProcs = sysconf(_SC_NPROCESSORS_ONLN);
    typedef cpuset_t mask_t;
#if __TBB_MAIN_THREAD_AFFINITY_BROKEN
    #define setaffinity(mask) cpuset_setaffinity(CPU_LEVEL_WHICH, CPU_WHICH_TID, -1, sizeof(mask_t), &mask)
#else
    #define setaffinity(mask) cpuset_setaffinity(CPU_LEVEL_WHICH, CPU_WHICH_PID, -1, sizeof(mask_t), &mask)
#endif
#endif /* __FreeBSD__ */
    if ( maxProcs < 2 )
        return Harness::Skipped;
    mask_t newMask;
    CPU_ZERO(&newMask);
    int availableProcs = min(maxProcs, (int)sizeof(mask_t) * CHAR_BIT) / 2;
    for ( int i = 0; i < availableProcs; ++i )
        CPU_SET( i, &newMask );
    int err = setaffinity( newMask );
#endif /* !WIN */
    ASSERT( !err, "Setting process affinity failed" );
    ASSERT( tbb::task_scheduler_init::default_num_threads() == availableProcs, NULL );
    ASSERT( (int)tbb::tbb_thread::hardware_concurrency() == availableProcs, NULL );
    return Harness::Done;
#else /* !(WIN || LIN || BSD) */
    return Harness::Skipped;
#endif /* !(WIN || LIN || BSD) */
}