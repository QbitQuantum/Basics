VOID
IN_PROCESS_APPLICATION::ShutDownInternal()
{
    DWORD    dwThreadStatus = 0;
    DWORD    dwTimeout = m_pConfig->QueryShutdownTimeLimitInMS();
    HANDLE   handle = NULL;
    WIN32_FIND_DATA fileData;

    if (IsDebuggerPresent())
    {
        dwTimeout = INFINITE;
    }

    if (m_fShutdownCalledFromNative ||
        m_status == APPLICATION_STATUS::STARTING ||
        m_status == APPLICATION_STATUS::FAIL)
    {
        return;
    }

    {
        SRWLockWrapper lock(m_srwLock);

        if (m_fShutdownCalledFromNative ||
            m_status == APPLICATION_STATUS::STARTING ||
            m_status == APPLICATION_STATUS::FAIL)
        {
            return;
        }

        // We need to keep track of when both managed and native initiate shutdown
        // to avoid AVs. If shutdown has already been initiated in managed, we don't want to call into
        // managed. We still need to wait on main exiting no matter what. m_fShutdownCalledFromNative
        // is used for detecting redundant calls and blocking more requests to OnExecuteRequestHandler.
        m_fShutdownCalledFromNative = TRUE;
        m_status = APPLICATION_STATUS::SHUTDOWN;

        if (!m_fShutdownCalledFromManaged)
        {
            // We cannot call into managed if the dll is detaching from the process.
            // Calling into managed code when the dll is detaching is strictly a bad idea,
            // and usually results in an AV saying "The string binding is invalid"
            if (!g_fProcessDetach)
            {
                m_ShutdownHandler(m_ShutdownHandlerContext);
                m_ShutdownHandler = NULL;
            }
        }

        // Release the lock before we wait on the thread to exit.
    }

    if (!m_fShutdownCalledFromManaged)
    {
        if (m_hThread != NULL &&
            GetExitCodeThread(m_hThread, &dwThreadStatus) != 0 &&
            dwThreadStatus == STILL_ACTIVE)
        {
            // wait for graceful shutdown, i.e., the exit of the background thread or timeout
            if (WaitForSingleObject(m_hThread, dwTimeout) != WAIT_OBJECT_0)
            {
                // if the thread is still running, we need kill it first before exit to avoid AV
                if (GetExitCodeThread(m_hThread, &dwThreadStatus) != 0 && dwThreadStatus == STILL_ACTIVE)
                {
                    // Calling back into managed at this point is prone to have AVs
                    // Calling terminate thread here may be our best solution.
                    TerminateThread(m_hThread, STATUS_CONTROL_C_EXIT);
                }
            }
        }
    }

    CloseHandle(m_hThread);
    m_hThread = NULL;
    s_Application = NULL;

    CloseStdErrHandles();

    if (m_pStdFile != NULL)
    {
        fflush(stdout);
        fflush(stderr);
        fclose(m_pStdFile);
    }

    if (m_hLogFileHandle != INVALID_HANDLE_VALUE)
    {
        m_Timer.CancelTimer();
        CloseHandle(m_hLogFileHandle);
        m_hLogFileHandle = INVALID_HANDLE_VALUE;
    }

    // delete empty log file
    handle = FindFirstFile(m_struLogFilePath.QueryStr(), &fileData);
    if (handle != INVALID_HANDLE_VALUE &&
        fileData.nFileSizeHigh == 0 &&
        fileData.nFileSizeLow == 0) // skip check of nFileSizeHigh
    {
        FindClose(handle);
        // no need to check whether the deletion succeeds
        // as nothing can be done
        DeleteFile(m_struLogFilePath.QueryStr());
    }
}