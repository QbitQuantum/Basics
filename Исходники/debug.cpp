///////////////////////////////////////////////////////////////////////////////
// Debugger - Constructor for debugger class
Debug::Debugger::Debugger(Bool bLogging)
{
    m_bLogging = bLogging;

#if defined ( WIN32 ) || defined ( WIN64 )
    // Create critical section
    m_CsFileWrite = new CRITICAL_SECTION;
    InitializeCriticalSection( m_CsFileWrite );
#else
    ASSERT( False );  // Only Windows critical sections are supported
#endif

    if(m_bLogging)
    {
	    // Copy the s_LogFiles into the instance
	    memcpy( m_LogFiles, s_LogFiles, sizeof( s_LogFiles ) );

	    // Create a directory with the current timestamp
        // ( Format: Month_Day_HourMinute )
	    time_t Time;
	    time( &Time );

	    tm Date;
	    localtime_s( &Date, &Time );

	    char FolderName[ MAX_STRING_LENGTH ];
	    sprintf_s( FolderName, MAX_STRING_LENGTH, "..\\Logs\\%.2d%.2d%.2d%.2d\\", (Date.tm_mon + 1), Date.tm_mday, Date.tm_hour, Date.tm_min );

	    int Result = _mkdir( FolderName );
        
        ASSERT( Result == 0 );
        if( Result == 0 )
        {
	        // Open all the log files
	        for( u8 Index = 0; Index < LogType::e_LogTypeCount; Index++ )
	        {
		        char FileName[ MAX_STRING_LENGTH ];
		        strncpy_s( FileName, MAX_STRING_LENGTH, FolderName, MAX_STRING_LENGTH - strlen( m_LogFiles[ Index ].FileName ) );
		        strcat_s( FileName, MAX_STRING_LENGTH, m_LogFiles[ Index ].FileName );

		        fopen_s( &m_LogFiles[ Index ].FileHandle, FileName, "w" );
	        }
        }
    }
}