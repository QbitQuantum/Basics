mfxStatus mfxSchedulerCore::StartWakeUpThread(void)
{
    // stop the thread before creating it again
    // don't try to check thread status, it might lead to interesting effects.
    if (m_hwWakeUpThread.handle)
        StopWakeUpThread();
    
    m_timer_hw_event = MFX_THREAD_TIME_TO_WAIT; //!!!!!! 
    // wa for case if it will be outside of coming 15.31 Beta
    //m_timer_hw_event = 10; 

#ifdef MFX_VLV_PLATFORM    
    m_timer_hw_event = 10; //temporary fix for VLV
#endif

#if defined(_WIN32) || defined(_WIN64)
    m_hwTaskDone.handle = CreateEventExW(NULL, 
                                        _T("Global\\IGFXKMDNotifyBatchBuffersComplete"), 
                                        CREATE_EVENT_MANUAL_RESET, 
                                        STANDARD_RIGHTS_ALL | EVENT_MODIFY_STATE);
    if (m_hwTaskDone.handle)
    {
        // create 'hardware task done' thread
        Ipp32s iRes = vm_thread_create(&m_hwWakeUpThread,
                                        scheduler_wakeup_thread_proc,
                                        this);
        if (0 == iRes)
        {
            return MFX_ERR_UNKNOWN;
        }
        m_zero_thread_wait = 15; //let wait 15 ms instead of 1 sec (we might miss event in case of GlobalEvents, it affects latency in multi-instance)
    }
    else
        m_zero_thread_wait = 1; // w/o events main thread should poll driver to get status 
#else
#if !defined(SYNCHRONIZATION_BY_NON_ZERO_THREAD)
    m_zero_thread_wait = 1;
#endif
#endif // defined(_WIN32) || defined(_WIN64)

    return MFX_ERR_NONE;

} // mfxStatus mfxSchedulerCore::StartWakeUpThread(void)