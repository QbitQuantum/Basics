void CThreadQueue::run()
{
    if(__rhoCurrentCategory.getName() == "NO_LOGGING")
		m_logThreadId = getThreadID();

	LOG(INFO) + "Starting main routine...";

	int nLastPollInterval = getLastPollInterval();
	while( !isStopping() )
	{
        unsigned int nWait = m_nPollInterval > 0 ? m_nPollInterval : QUEUE_POLL_INTERVAL_INFINITE;

        if ( m_nPollInterval > 0 && nLastPollInterval > 0 )
        {
            int nWait2 = m_nPollInterval - nLastPollInterval;
            if ( nWait2 <= 0 )
                nWait = QUEUE_STARTUP_INTERVAL_SECONDS;
            else
                nWait = nWait2;
        }

        if ( !m_bNoThreaded && !isStopping() && isNoCommands() )
		{
            LOG(INFO) + "ThreadQueue blocked for " + nWait + " seconds...";
            if ( wait(nWait*1000) == 1 )
                onTimeout();
        }
        nLastPollInterval = 0;

        if ( !m_bNoThreaded && !isStopping() )
    		processCommands();
	}

    LOG(INFO) + "Thread shutdown";
}