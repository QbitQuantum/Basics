    ~imp() {
#if defined(_WINDOWS) || defined(_CYGWIN)
        DeleteTimerQueueTimer(NULL,
                              m_timer,
                              INVALID_HANDLE_VALUE);
#elif defined(__APPLE__) && defined(__MACH__)
        // Mac OS X

        // If the waiting-thread is not up and waiting yet, 
        // we can make sure that it finishes quickly by 
        // setting the end-time to zero.
        m_end_time.tv_sec = 0;
        m_end_time.tv_nsec = 0;

        // Otherwise it's already up and waiting, and
        // we can send a signal on m_condition_var:
        pthread_mutex_lock(&m_mutex);
        pthread_cond_signal(&m_condition_var);
        pthread_mutex_unlock(&m_mutex);

        if (pthread_join(m_thread_id, NULL) != 0)
            throw default_exception("failed to join thread");
        if (pthread_mutex_destroy(&m_mutex) != 0)
            throw default_exception("failed to destroy pthread mutex");
        if (pthread_cond_destroy(&m_condition_var) != 0)
            throw default_exception("failed to destroy pthread condition variable");
        if (pthread_attr_destroy(&m_attributes) != 0)
            throw default_exception("failed to destroy pthread attributes object");
#elif defined(_LINUX_) || defined(_FREEBSD_)
    // Linux & FreeBSD
        timer_delete(m_timerid);
#else
    // Other Platforms
#endif
    }