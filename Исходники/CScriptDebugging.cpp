bool CScriptDebugging::SetLogfile ( const char* szFilename, unsigned int uiLevel )
{
    assert ( szFilename );

    // Close the previously loaded file
    if ( m_pLogFile )
    {
        fprintf ( m_pLogFile, "INFO: Logging to this file ended\n" );
        // if we have a flush timer
        if ( m_flushTimerHandle != NULL )
        {
            // delete our flush timer
            DeleteTimerQueueTimer ( NULL, m_flushTimerHandle, INVALID_HANDLE_VALUE );   // INVALID_HANDLE_VALUE = wait for running callbacks to finish
        }
        fclose ( m_pLogFile );
        m_pLogFile = NULL;
    }

    // Apply log size limit
    uint uiMaxSizeKB = 0;
    g_pCore->GetCVars ()->Get ( "max_clientscript_log_kb", uiMaxSizeKB );
    CycleFile( szFilename, uiMaxSizeKB );


    // Try to load the new file
    FILE* pFile = fopen ( szFilename, "a+" );
    if ( pFile )
    {
        // [2014-07-09 14:39:31] WARNING: Bad argument @ 'setElementPosition' [Expected element at argument 1, got nil] [string "return addEventHandler("onClientRender", ro..."]
        // length = 158

        // set our buffer size

        // assumed message length of 158

        // if we pulse at 150FPS (unrealistic but whatever)
        // that's 1 update every 6.66666666ms
        // pulse rate is 50 so 50 / 6.6666666 = 7.5 (close enough)
        // if we are doing 5 error messages a pulse that's 5 * 7.5
        // 5 * 7.5 = 37.5
        // we need room for at least 37.5 messages in this buffer
        // round 37.5 to 38 because we can't have half a message
        // 8 * 256 bytes = 6004B
        // round 6004 up to the nearest divisible by 1024 = 6144
        // we have our buffer size.
        setvbuf ( pFile , NULL , _IOFBF , 6144 );

        // Set the new pointer and level and return true
        m_uiLogFileLevel = uiLevel;
        m_pLogFile = pFile;

        // Create a timer
        ::CreateTimerQueueTimer( &m_flushTimerHandle, NULL, TimerProc, NULL, 50, 50, WT_EXECUTEINTIMERTHREAD );
        return true;
    }

    return false;
}