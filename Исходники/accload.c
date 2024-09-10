/*
 * AccLoadProg - create a new process for debugging
 */
trap_retval ReqProg_load( void )
{
    char            *parm;
    char            *src;
    char            *dst;
    char            *endsrc;
    char            exe_name[PATH_MAX];
    char            ch;
    BOOL            rc;
    int             len;
    MYCONTEXT       con;
    thread_info     *ti;
    HANDLE          handle;
    prog_load_req   *acc;
    prog_load_ret   *ret;
    header_info     hi;
    WORD            stack;
    WORD            version;
    DWORD           pid;
    DWORD           pid_started;
    DWORD           cr_flags;
    char            *buff;
    size_t          nBuffRequired;
    char            *dll_name;
    char            *service_name;
    char            *dll_destination;
    char            *service_parm;

    acc = GetInPtr( 0 );
    ret = GetOutPtr( 0 );
    parm = GetInPtr( sizeof( *acc ) );

    /*
     * reset status variables
     */
    LastExceptionCode = -1;
    DebugString = NULL;
    DebugeeEnded = FALSE;
    RemoveAllThreads();
    FreeLibList();
    DidWaitForDebugEvent = FALSE;
    DebugeePid = 0;
    DebugeeTid = 0;
    SupportingExactBreakpoints = 0;

    /*
     * check if pid is specified
     */
    ParseServiceStuff( parm, &dll_name, &service_name, &dll_destination, &service_parm );
    pid = 0;
    src = parm;

    /*
    //  Just to be really safe!
    */
    nBuffRequired = GetTotalSize() + PATH_MAX + 16;
    buff = LocalAlloc( LMEM_FIXED, nBuffRequired );
    if( buff == NULL ) {
        ret->err = ERROR_NOT_ENOUGH_MEMORY;
        return( sizeof( *ret ) );
    }

    if( *src == '#' ) {
        src++;
        pid = strtoul( src, &endsrc, 16 );
        if( pid == 0 ) {
            pid = -1;
        }
        strcpy( buff, endsrc );
    } else {
        while( isdigit( *src ) ) {
            src++;
        }
        if( *src == 0 && src != parm ) {
            pid = atoi( parm );
        }
    }

    /*
     * get program to debug.  If the user has specified a pid, then
     * skip directly to doing a DebugActiveProcess
     */
    IsWOW = FALSE;
#if !defined( MD_x64 )
    IsDOS = FALSE;
#endif
    if( pid == 0 ) {
        ret->err = FindProgFile( parm, exe_name, NtExtList );
        if( ret->err != 0 ) {
            goto error_exit;
        }

        /*
         * Get type of application
         */
        handle = CreateFile( (LPTSTR)exe_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0 );
        if( handle == INVALID_HANDLE_VALUE ) {
            ret->err = GetLastError();
            goto error_exit;
        }
        GetFullPathName( exe_name, MAX_PATH, CurrEXEName, NULL );

        /*
         * get the parm list
         */
        if( strchr( CurrEXEName, ' ' ) != NULL ) {
            strcpy( buff, "\"" );
            strcat( buff, CurrEXEName );
            strcat( buff, "\"" );
        } else {
            strcpy( buff, CurrEXEName );
        }
        dst = &buff[strlen( buff )];
        src = parm;
        while( *src != 0 ) {
            ++src;
        }
        // parm layout
        // <--parameters-->0<--program_name-->0<--arguments-->0
        //
        for( len = GetTotalSize() - sizeof( *acc ) - (src - parm) - 1; len > 0; --len ) {
            ch = *src;
            if( ch == 0 ) {
                ch = ' ';
            }
            *dst = ch;
            ++dst;
            ++src;
        }
        *dst = 0;

        cr_flags = DEBUG_ONLY_THIS_PROCESS;

        if( !GetEXEHeader( handle, &hi, &stack ) ) {
            ret->err = GetLastError();
            CloseHandle( handle );
            goto error_exit;
        }
        if( hi.sig == EXE_PE ) {
            if( IS_PE64( hi.u.peh ) ) {
                DebugeeSubsystem = PE64( hi.u.peh ).subsystem;
            } else {
                DebugeeSubsystem = PE32( hi.u.peh ).subsystem;
#if defined( MD_x64 )
                IsWOW = TRUE;
#endif
            }
            if( DebugeeSubsystem == SS_WINDOWS_CHAR ) {
                cr_flags |= CREATE_NEW_CONSOLE;
            }
#if !defined( MD_x64 )
        } else if( hi.sig == EXE_NE ) {
            IsWOW = TRUE;
            /*
             * find out the pid of WOW, if it is already running.
             */
            pVDMEnumProcessWOW( EnumWOWProcessFunc, (LPARAM)&pid );
            if( pid != 0 ) {
                version = LOWORD( GetVersion() );
                if( LOBYTE( version ) == 3 && HIBYTE( version ) < 50 ) {
                    int kill = MessageBox( NULL, TRP_NT_wow_warning, TRP_The_WATCOM_Debugger, MB_APPLMODAL + MB_YESNO );
                    if( kill == IDYES ) {
                        DWORD axs = PROCESS_TERMINATE+STANDARD_RIGHTS_REQUIRED;
                        HANDLE hprocess = OpenProcess( axs, FALSE, pid );

                        if( hprocess != 0 && TerminateProcess( hprocess, 0 ) ) {
                            CloseHandle( hprocess );
                            pid = 0;
                        }
                    }
                } else {
                    cr_flags |= CREATE_SEPARATE_WOW_VDM;
                    pid = 0; // always start a new VDM.
                }
            }
            if( pid != 0 ) {
                ret->err = GetLastError();
                CloseHandle( handle );
                goto error_exit;
            }
        } else {
            IsDOS = TRUE;
#endif
        }
        CloseHandle( handle );
    }

    /*
     * start the debugee
     */
    pid_started = pid;
    if( *dll_name ) {
        strcat( buff, LOAD_PROG_STR_DELIM );
        strcat( buff, LOAD_PROG_STR_DLLNAME );
        strcat( buff, dll_name );
    }
    if( *service_name ) {
        strcat( buff, LOAD_PROG_STR_DELIM );
        strcat( buff, LOAD_PROG_STR_SERVICE );
        strcat( buff, service_name );
    }
    if( *dll_destination ) {
        strcat( buff, LOAD_PROG_STR_DELIM );
        strcat( buff, LOAD_PROG_STR_COPYDIR );
        strcat( buff, dll_destination );
    }
    if( *service_parm ) {
        strcat( buff, LOAD_PROG_STR_DELIM );
        strcat( buff, LOAD_PROG_STR_SERVICEPARM );
        strcat( buff, service_parm );
    }
    ret->err = StartControlThread( buff, &pid_started, cr_flags );
    if( ret->err != 0 ) {
        goto error_exit;
    }
    /*
     * CREATE_PROCESS_DEBUG_EVENT will always be the first debug event.
     * If it is not, then something is horribly wrong.
     */
    rc = MyWaitForDebugEvent();
    if( !rc || ( DebugEvent.dwDebugEventCode != CREATE_PROCESS_DEBUG_EVENT ) || ( DebugEvent.dwProcessId != pid_started ) ) {
        ret->err = GetLastError();
        goto error_exit;
    }
    ProcessInfo.pid = DebugEvent.dwProcessId;
    ProcessInfo.process_handle = DebugEvent.u.CreateProcessInfo.hProcess;
    ProcessInfo.base_addr = DebugEvent.u.CreateProcessInfo.lpBaseOfImage;
    AddProcess( &hi );
    AddThread( DebugEvent.dwThreadId, DebugEvent.u.CreateProcessInfo.hThread, DebugEvent.u.CreateProcessInfo.lpStartAddress );
    DebugeePid = DebugEvent.dwProcessId;
    DebugeeTid = DebugEvent.dwThreadId;
    LastDebugEventTid = DebugEvent.dwThreadId;

#if defined( MD_x86 )
#ifdef WOW
    if( IsWOW ) {
        ret->flags = LD_FLAG_IS_PROT;
        ret->err = 0;
        ret->task_id = DebugeePid;
        /*
         * we use our own CS and DS as the Flat CS and DS, for lack
         * of anything better
         */
        FlatDS = GetDS();
        FlatCS = GetCS();
        if( !executeUntilVDMStart() ) {
            ret->err = GetLastError();
            goto error_exit;
        }
        if( pid ) {
            addAllWOWModules();
        } else {
            addKERNEL();
        }
        /*
         * we save the starting CS:IP of the WOW app, since we will use
         * it to force execution of code later
         */
        ti = FindThread( DebugeeTid );
        MyGetThreadContext( ti, &con );
        WOWAppInfo.segment = ( WORD ) con.SegCs;
        WOWAppInfo.offset = ( WORD ) con.Eip;
        con.SegSs = con.SegDs; // Wow lies about the stack segment.  Reset it
        con.Esp = stack;
        MySetThreadContext( ti, &con );
    } else if( IsDOS ) {
        // TODO! Clean up this code
        ret->flags = 0; //LD_FLAG_IS_PROT;
        ret->err = 0;
        ret->task_id = DebugeePid;
        /*
         * we use our own CS and DS as the Flat CS and DS, for lack
         * of anything better
         */
        FlatDS = GetDS();
        FlatCS = GetCS();
        if( !executeUntilVDMStart() ) {
            ret->err = GetLastError();
            goto error_exit;
        }
#if 0
        if( pid ) {
            addAllWOWModules();
        } else {
            addKERNEL();
        }
#endif
        /*
         * we save the starting CS:IP of the WOW app, since we will use
         * it to force execution of code later
         */
        ti = FindThread( DebugeeTid );
        MyGetThreadContext( ti, &con );
        WOWAppInfo.segment = ( WORD )con.SegCs;
        WOWAppInfo.offset = ( WORD )con.Eip;
        con.SegSs = con.SegDs; // Wow lies about the stack segment.  Reset it
        con.Esp = stack;
        MySetThreadContext( ti, &con );
    } else {
#else
    {
#endif
#else
    {
#endif
        LPVOID base;

        if( pid == 0 ) {
            base = (LPVOID)DebugEvent.u.CreateProcessInfo.lpStartAddress;
        } else {
            base = 0;
        }

        ret->flags = LD_FLAG_IS_PROT;
        ret->err = 0;
        ret->task_id = DebugeePid;
        if( executeUntilStart( pid != 0 ) ) {
            LPVOID old;
            /*
             * make the application load our DLL, so that we can have it
             * run code out of it.  One small note: this will not work right
             * if the app does not load our DLL at the same address the
             * debugger loaded it at!!!
             */

            ti = FindThread( DebugeeTid );
            MyGetThreadContext( ti, &con );
            old = (LPVOID)AdjustIP( &con, 0 );
            if( base != 0 ) {
                SetIP( &con, base );
            }
            MySetThreadContext( ti, &con );
            SetIP( &con, old );
            MySetThreadContext( ti, &con );
        }
        ti = FindThread( DebugeeTid );
        MyGetThreadContext( ti, &con );
#if defined( MD_x86 )
        FlatCS = con.SegCs;
        FlatDS = con.SegDs;
#endif
        ret->flags |= LD_FLAG_IS_BIG;
    }
    ret->flags |= LD_FLAG_HAVE_RUNTIME_DLLS;
    if( pid != 0 ) {
        ret->flags |= LD_FLAG_IS_STARTED;
    }
    ret->mod_handle = 0;

error_exit:
    if( buff != NULL ) {
        LocalFree( buff );
    }
    return( sizeof( *ret ) );

}

trap_retval ReqProg_kill( void )
{
    prog_kill_ret   *ret;

    ret = GetOutPtr( 0 );
    ret->err = 0;
    DelProcess( TRUE );
    StopControlThread();
    return( sizeof( *ret ) );
}