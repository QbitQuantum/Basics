    void Thread::ThreadBody()
    {
        Utils::ThreadNamesLocker locker(GetCurrentThreadID(), m_name);

        run();  // run user code
    }