void Logger::logPrint( bool hex, const char * const file, const int line, const int level, const char *fstring, ... )
{
    if ( level <= mEffectiveLevel )
    {
        char            classString[4];
        char            timeString[64];
        char            logString[8192];
        va_list         argPtr;
        struct timeval  timeVal;
        
        if ( level < PANIC || level > DEBUG9 )
            Panic( "Invalid logger level %d", level );

        strncpy( classString, smCodes[level].c_str(), sizeof(classString) );

        gettimeofday( &timeVal, NULL );

    #if 0
        if ( logRuntime )
        {
            static struct timeval logStart;

            subtractTime( &timeVal, &logStart );

            snprintf( timeString, sizeof(timeString), "%ld.%03ld", timeVal.tv_sec, timeVal.tv_usec/1000 );
        }
        else
        {
    #endif
            char *timePtr = timeString;
            timePtr += strftime( timePtr, sizeof(timeString), "%x %H:%M:%S", localtime(&timeVal.tv_sec) );
            snprintf( timePtr, sizeof(timeString)-(timePtr-timeString), ".%06ld", timeVal.tv_usec );
    #if 0
        }
    #endif

        pid_t tid;
#ifdef HAVE_SYSCALL
        if ( (tid = syscall(SYS_gettid)) < 0 ) // Thread/Process id
#endif // HAVE_SYSCALL
        tid = getpid(); // Process id

        char *logPtr = logString;
        logPtr += snprintf( logPtr, sizeof(logString), "%s %s[%d].%s-%s/%d [", 
                    timeString,
                    mId.c_str(),
                    tid,
                    classString,
                    file,
                    line
                );
        char *syslogStart = logPtr;

        va_start( argPtr, fstring );
        if ( hex )
        {
            unsigned char *data = va_arg( argPtr, unsigned char * );
            int len = va_arg( argPtr, int );
            int i;
            logPtr += snprintf( logPtr, sizeof(logString)-(logPtr-logString), "%d:", len );
            for ( i = 0; i < len; i++ )
            {
                logPtr += snprintf( logPtr, sizeof(logString)-(logPtr-logString), " %02x", data[i] );
            }
        }
        else
        {