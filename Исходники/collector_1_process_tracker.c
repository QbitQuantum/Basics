static RBOOL
    getSnapshot
    (
        processEntry* toSnapshot
    )
{
    RBOOL isSuccess = FALSE;
    RU32 i = 0;

    if( NULL != toSnapshot )
    {
        rpal_memory_zero( toSnapshot, sizeof( g_snapshot_1 ) );
    }

    if( NULL != toSnapshot )
    {
#ifdef RPAL_PLATFORM_WINDOWS
        HANDLE hSnapshot = NULL;
        PROCESSENTRY32W procEntry = { 0 };
        procEntry.dwSize = sizeof( procEntry );

        if( INVALID_HANDLE_VALUE != ( hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 ) ) )
        {
            if( Process32FirstW( hSnapshot, &procEntry ) )
            {
                isSuccess = TRUE;

                do
                {
                    if( 0 == procEntry.th32ProcessID )
                    {
                        continue;
                    }

                    toSnapshot[ i ].pid = procEntry.th32ProcessID;
                    toSnapshot[ i ].ppid = procEntry.th32ParentProcessID;
                    i++;
                } while( Process32NextW( hSnapshot, &procEntry ) &&
                         MAX_SNAPSHOT_SIZE > i );
            }

            CloseHandle( hSnapshot );
        }
#elif defined( RPAL_PLATFORM_LINUX )
        RWCHAR procDir[] = _WCH( "/proc/" );
        rDir hProcDir = NULL;
        rFileInfo finfo = {0};

        if( rDir_open( (RPWCHAR)&procDir, &hProcDir ) )
        {
            isSuccess = TRUE;

            while( rDir_next( hProcDir, &finfo ) &&
                   MAX_SNAPSHOT_SIZE > i )
            {
                if( rpal_string_wtoi( (RPWCHAR)finfo.fileName, &( toSnapshot[ i ].pid ) )
                    && 0 != toSnapshot[ i ].pid )
                {
                    i++;
                }
            }

            rDir_close( hProcDir );
        }
#elif defined( RPAL_PLATFORM_MACOSX )
        int mib[] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL };
        struct kinfo_proc* infos = NULL;
        size_t size = 0;
        int ret = 0;
        int j = 0;

        if( 0 == ( ret = sysctl( mib, ARRAY_N_ELEM( mib ), infos, &size, NULL, 0 ) ) )
        {
            if( NULL != ( infos = rpal_memory_alloc( size ) ) )
            {
                while( 0 != ( ret = sysctl( mib, ARRAY_N_ELEM( mib ), infos, &size, NULL, 0 ) ) && ENOMEM == errno )
                {
                    if( NULL == ( infos = rpal_memory_realloc( infos, size ) ) )
                    {
                        break;
                    }
                }
            }
        }

        if( 0 == ret && NULL != infos )
        {
            isSuccess = TRUE;
            size = size / sizeof( struct kinfo_proc );
            for( j = 0; j < size; j++ )
            {
                toSnapshot[ i ].pid = infos[ j ].kp_proc.p_pid;
                toSnapshot[ i ].ppid = infos[ j ].kp_eproc.e_ppid;
                i++;
            }

            if( NULL != infos )
            {
                rpal_memory_free( infos );
                infos = NULL;
            }
        }
#endif
    }

    return isSuccess;
}