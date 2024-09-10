static void* HK_CALL hkWorkerThreadFunc(void *v)
{
    vHavokCpuJobThreadPool::WorkerThreadData& data = *static_cast<vHavokCpuJobThreadPool::WorkerThreadData*>(v);
    vHavokCpuJobThreadPool::SharedThreadData& sharedThreadData = *data.m_sharedThreadData;

    HK_THREAD_LOCAL_SET( hkThreadNumber, data.m_threadId);

#if defined(HK_COMPILER_HAS_INTRINSICS_IA32) && HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
    // Flush all denormal/subnormal numbers (2^-1074 to 2^-1022) to zero.
    // Typically operations on denormals are very slow, up to 100 times slower than normal numbers.
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif

#ifdef HK_PLATFORM_XBOX360
    XSetThreadProcessor(GetCurrentThread(), data.m_hardwareThreadId );
#elif defined(HK_PLATFORM_WIN32) && !defined(_VISION_WINRT)
    SetThreadIdealProcessor(GetCurrentThread(), data.m_hardwareThreadId);
    // Can use SetThreadAffityMask to be more force-full.
#endif

    hkMemoryRouter memoryRouter;
    hkMemorySystem::getInstance().threadInit( memoryRouter, "vHavokCpuJobThreadPool" );
    hkBaseSystem::initThread( &memoryRouter );
    //hkUint32 allLockVal = 0;
    //hkReferencedObject::initThread(&allLockVal);

    if (sharedThreadData.m_timerBufferAllocation > 0)
    {
        // Allocate a monitor stream for this thread - this  enables timers.
        hkMonitorStream::getInstance().resize(sharedThreadData.m_timerBufferAllocation);
    }
    data.m_monitorStreamBegin = hkMonitorStream::getInstance().getStart();
    data.m_monitorStreamEnd = hkMonitorStream::getInstance().getEnd();

    hkCheckDeterminismUtil::initThread();


    // VISION specific: Call any per thread callback
    if (sharedThreadData.m_OnWorkerThreadCreatedPtr)
    {
        sharedThreadData.m_CallbackProtect.enter();
        sharedThreadData.m_OnWorkerThreadCreatedPtr->TriggerCallbacks( /* data needed? */);
        sharedThreadData.m_CallbackProtect.leave();
    }
    // END  VISION specific

    // Wait for the main thread to release the worker thread
    data.m_semaphore.acquire();

    // The thread "main loop"
    while (data.m_killThread == false)
    {
        if (data.m_clearTimers)
        {
            hkMonitorStream::getInstance().reset();
            data.m_monitorStreamEnd = hkMonitorStream::getInstance().getEnd();
            data.m_clearTimers = false;
        }

        const bool isNotPrimary = false;
        hkCheckDeterminismUtil::workerThreadStartFrame(isNotPrimary);

        // Enable timers for critical sections just during the step call
        hkCriticalSection::setTimersEnabled();

        sharedThreadData.m_jobQueue->processAllJobs();

        // Disable timers for critical sections just during the step call
        hkCriticalSection::setTimersDisabled();

        // Note collected timer data
        hkMonitorStream& stream = hkMonitorStream::getInstance();
        data.m_monitorStreamEnd = stream.getEnd();

        hkCheckDeterminismUtil::workerThreadFinishFrame();

        if( sharedThreadData.m_gcThreadMemoryOnCompletion )
        {
            hkMemorySystem::getInstance().garbageCollectThread( memoryRouter );
        }

        // Release any thread (usually the main thread) which may be waiting for all worker threads to finish.
        sharedThreadData.m_workerThreadFinished.release();

        // Immediately wait until the main thread releases the thread again
        data.m_semaphore.acquire();
    }


    // Perform cleanup operations

    // VISION specific: Call any per thread callback
    if (sharedThreadData.m_OnWorkerThreadFinishedPtr)
    {
        sharedThreadData.m_CallbackProtect.enter();
        sharedThreadData.m_OnWorkerThreadFinishedPtr->TriggerCallbacks( /* data needed? */);
        sharedThreadData.m_CallbackProtect.leave();
    }
    // END  VISION specific

    hkCheckDeterminismUtil::quitThread();

    hkBaseSystem::quitThread();
    hkMemorySystem::getInstance().threadQuit( memoryRouter );

    sharedThreadData.m_workerThreadFinished.release();

    return 0;
}