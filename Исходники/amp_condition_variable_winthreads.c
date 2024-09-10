int amp_raw_condition_variable_init(amp_condition_variable_t cond)
{
    int retval = AMP_UNSUPPORTED;
    
    assert(NULL != cond);
    
    retval = InitializeCriticalSectionAndSpinCount(&cond->access_waiting_threads_count_critsec,
                                                   AMP_RAW_MUTEX_WINTHREADS_CRITICAL_SECTION_DEFAULT_SPIN_COUNT | AMP_RAW_MUTEX_WINTHREADS_CRITICAL_SECTION_CREATE_IMMEDIATELY_ON_WIN2000);
    
    if (FALSE == retval) {
        DWORD const last_error = GetLastError();
        /**
         * TODO: @todo Differentiate between no-memory and other errors.
         */
        return AMP_ERROR;
    }

    retval = InitializeCriticalSectionAndSpinCount(&cond->wake_waiting_threads_critsec,
                                                   AMP_RAW_MUTEX_WINTHREADS_CRITICAL_SECTION_DEFAULT_SPIN_COUNT | AMP_RAW_MUTEX_WINTHREADS_CRITICAL_SECTION_CREATE_IMMEDIATELY_ON_WIN2000);
    if (FALSE  == retval) {
        DWORD const last_error = GetLastError();
        /**
         * TODO: @todo Differentiate between no-memory and other errors.
         */
        
        DeleteCriticalSection(&cond->access_waiting_threads_count_critsec);
        
        return AMP_ERROR;
    }

    /* Assuming that less threads exist than max possible semaphore count.
     */
    cond->waking_waiting_threads_count_control_sem = CreateSemaphore(NULL, /* No inheritance to child processes */
                                                                     0, /* Initially no threads can pass */
                                                                     LONG_MAX, /* Max semaphore count */
                                                                     NULL); /* Only intra-process semaphore */
    
    if (NULL == cond->waking_waiting_threads_count_control_sem) {
        DWORD const last_error = GetLastError();
        assert(ERROR_ALREADY_EXISTS != last_error);
        
        DeleteCriticalSection(&cond->wake_waiting_threads_critsec);
        DeleteCriticalSection(&cond->access_waiting_threads_count_critsec);
        
        return AMP_ERROR;
    }

    cond->finished_waking_waiting_threads_event = CreateEvent(NULL, /* Default security and no inheritance to child processes */
                                                              FALSE, /* No manual reset */
                                                              0, /* Initially not signaled */
                                                              NULL /* Not inter-process available */
                                                              );
    
    if (NULL == cond->finished_waking_waiting_threads_event) {
        BOOL close_retval = FALSE;
        DWORD const create_event_error = GetLastError();
        assert(ERROR_ALREADY_EXISTS != create_event_error);
        
        DeleteCriticalSection(&cond->wake_waiting_threads_critsec);
        DeleteCriticalSection(&cond->access_waiting_threads_count_critsec);

        close_retval = CloseHandle(&cond->waking_waiting_threads_count_control_sem);
        
        if (FALSE == close_retval) {
            DWORD const close_handle_error = GetLastError();
            assert(ERROR_INVALID_HANDLE != close_handle_error);
            assert(0);
        }
        
        /* I don't know the possible return values of GetLastError if event
         * creation didn't work - just returning an error code.
         */
        return AMP_ERROR;
    }
    
    
    cond->waiting_thread_count = 0l;
    cond->broadcast_in_progress = FALSE;
    
    
    /* Preliminary tests that waiting_thread_count and broadcast_in_progress
     * are correctly aligned to allow atomic access to them.
     *
     * TODO: @todo Re-enable alignment test assertions.
     *
     * TODO: @todo Check which alignment is needed on 32bit and 64bit systems
     *             and on which platforms.
     */
    /* assert(0x0 == ((uintptr_t)(&cond->waiting_thread_count) & 0x3)); */
    /* assert(0x0 ==((uintptr_t)(&cond->broadcast_in_progress) & 0x3)); */
    
    return AMP_SUCCESS;
}