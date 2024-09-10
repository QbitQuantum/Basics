// Overrides osThread
int CpuAffinityThread::entryPoint()
{
#if AMDT_BUILD_TARGET == AMDT_WINDOWS_OS
    //set the thread affinity to the 1 core specified
#pragma message ("TODO: Handle more than 64 cores")
    GT_ASSERT(m_core < 64);
    DWORD_PTR affinityMask = (DWORD_PTR)1 << m_core;
    SetThreadAffinityMask(osGetCurrentThreadHandle(),  affinityMask);

    //Let the thread affinity take affect
    while (GetCurrentProcessorNumber() != m_core)
    {
        osSleep(1);
    }

#else
    int numCPUs;

    osGetAmountOfLocalMachineCPUs(numCPUs);

    if (0 >= numCPUs)
    {
        // at least 1, as CPU_ALLOC_SIZE(0) returns 0
        numCPUs = m_core + 1;
    }

    size_t size = CPU_ALLOC_SIZE(numCPUs);
    cpu_set_t* mask = CPU_ALLOC(numCPUs);

    GT_ASSERT(nullptr != mask);

    // Step 1, bind thread to the logical processor
    CPU_ZERO_S(size, mask);
    CPU_SET(m_core, mask);

    if (-1 == sched_setaffinity((pid_t)syscall(__NR_gettid), size, mask))
    {
        CPU_FREE(mask);
        return -1;
    }


    // Step 2, get the thread's current mask and make sure that it
    //  is running on the target processor
    cpu_set_t* currentMask = CPU_ALLOC(numCPUs);

    GT_ASSERT(nullptr != currentMask);

    int retries = 8; // just don't loop forever!

    do
    {
        pthread_yield(); // trigger re-scheduling

        CPU_ZERO_S(size, currentMask);
        sched_getaffinity((pid_t)syscall(__NR_gettid), size, currentMask);

    }
    while (!CPU_EQUAL_S(size, mask, currentMask) && (0 != retries--));


    // OK, cleanup
    CPU_FREE(currentMask);
    CPU_FREE(mask);

    if (0 == retries)  // not a fatal error - an offline processor can cause this
    {
        return -1;
    }

#endif

    osCpuid cpuInfo;
    m_pSessionTopology->processor = cpuInfo.getcore();
    m_pSessionTopology->numaNode = cpuInfo.getNodeId();

    return 0;
}