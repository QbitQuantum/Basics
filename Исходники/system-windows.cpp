void MythSystemManager::run(void)
{
    RunProlog();

    LOG(VB_GENERAL, LOG_INFO, "Starting process manager");

    // run_system is set to NULL during shutdown, and we need this thread to
    // exit during shutdown.
    while( run_system )
    {
        // check for any running processes
        m_mapLock.lock();

        if( m_childCount == 0 )
        {
            m_mapLock.unlock();
            usleep( 100000 );
            continue;
        }

        DWORD result = WaitForMultipleObjects( m_childCount, m_children,
                                               FALSE, 100 );

        if ( result == WAIT_TIMEOUT || result == WAIT_FAILED )
        {
            m_mapLock.unlock();
            continue;
        }

        int index = result - WAIT_OBJECT_0;
        if ( index < 0 || index > m_childCount - 1 )
        {
            m_mapLock.unlock();
            continue;
        }
        HANDLE child = m_children[index];

        // pop exited process off managed list, add to cleanup list
        MythSystemWindows  *ms = m_pMap.take(child);
        ChildListRebuild();
        m_mapLock.unlock();

        // Occasionally, the caller has deleted the structure from under
        // our feet.  If so, just log and move on.
        if (!ms)
        {
            LOG(VB_SYSTEM, LOG_ERR,
                QString("Structure for child handle %1 already deleted!")
                .arg((long long)child));
            continue;
        }

        listLock.lock();
        msList.append(ms);

        DWORD               status;
        GetExitCodeProcess( child, &status );

        ms->SetStatus(status);
        LOG(VB_SYSTEM, LOG_INFO,
                QString("Managed child (Handle: %1) has exited! "
                        "command=%2, status=%3, result=%4")
                .arg((long long)child) .arg(ms->GetLogCmd()) .arg(status) 
                .arg(ms->GetStatus()));

        // loop through running processes for any that require action
        MSMap_t::iterator   i;
        time_t              now = time(NULL);

        m_mapLock.lock();
        m_jumpLock.lock();
        for (i = m_pMap.begin(); i != m_pMap.end(); ++i)
        {
            child = i.key();
            ms    = i.value();

            // handle processes beyond marked timeout
            if( ms->m_timeout > 0 && ms->m_timeout < now )
            {
                // issuing KILL signal after TERM failed in a timely manner
                if( ms->GetStatus() == GENERIC_EXIT_TIMEOUT )
                {
                    LOG(VB_SYSTEM, LOG_INFO,
                        QString("Managed child (Handle: %1) timed out, "
                                "issuing KILL signal").arg((long long)child));
                    // Prevent constant attempts to kill an obstinate child
                    ms->m_timeout = 0;
                    ms->Signal(SIGKILL);
                }

                // issuing TERM signal
                else
                {
                    LOG(VB_SYSTEM, LOG_INFO,
                        QString("Managed child (Handle: %1) timed out"
                                ", issuing TERM signal").arg((long long)child));
                    ms->SetStatus( GENERIC_EXIT_TIMEOUT );
                    ms->m_timeout = now + 1;
                    ms->Term();
                }
            }

            if ( m_jumpAbort && ms->GetSetting("AbortOnJump") )
                ms->Term();
        }

        m_jumpAbort = false;
        m_jumpLock.unlock();

        m_mapLock.unlock();

        // hold off unlocking until all the way down here to 
        // give the buffer handling a chance to run before
        // being closed down by signal thread
        listLock.unlock();
    }

    // kick to allow them to close themselves cleanly
    readThread->wake();
    writeThread->wake();

    RunEpilog();
}