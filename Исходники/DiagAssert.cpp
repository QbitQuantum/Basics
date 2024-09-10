void DoStackTrace ( LPTSTR szString  ,
                    DWORD  dwSize     )
{
    HANDLE hProcess = GetCurrentProcess ( ) ;

    // If the symbol engine is not initialized, do it now.
    if ( FALSE == g_bSymIsInit )
    {
        DWORD dwOpts = SymGetOptions ( ) ;

        // Turn on load lines.
        SymSetOptions ( dwOpts                |
                        SYMOPT_LOAD_LINES      ) ;

        if ( FALSE == g_cSym.SymInitialize ( hProcess ,
                                             NULL     ,
                                             FALSE     ) )
        {
            TRACE ( "DiagAssert : Unable to initialize the "
                    "symbol engine!!!\n" ) ;
#ifdef _DEBUG
            DebugBreak ( ) ;
#endif
        }
        else
        {
            g_bSymIsInit = TRUE ;
        }
    }

    // The symbol engine is initialized so do the stack walk.

    // The array of addresses.
    ADDRVECTOR vAddrs ;

    // The thread information.
    CONTEXT    stCtx  ;

    stCtx.ContextFlags = CONTEXT_FULL ;

    // Get the thread context.  Since I am doing this on the CURRENT
    // executing thread, the context will be from down in the bowls of
    // KERNEL32.DLL.  Probably GetThreadContext itself.
    if ( GetThreadContext ( GetCurrentThread ( ) , &stCtx ) )
    {
        STACKFRAME stFrame ;
        DWORD      dwMachine ;

        ZeroMemory ( &stFrame , sizeof ( STACKFRAME ) ) ;

        stFrame.AddrPC.Mode = AddrModeFlat ;

#if defined (_M_IX86)
        dwMachine                = IMAGE_FILE_MACHINE_I386 ;

        stFrame.AddrPC.Offset    = stCtx.Eip    ;
        stFrame.AddrStack.Offset = stCtx.Esp    ;
        stFrame.AddrFrame.Offset = stCtx.Ebp    ;
        stFrame.AddrStack.Mode   = AddrModeFlat ;
        stFrame.AddrFrame.Mode   = AddrModeFlat ;

#elif defined (_M_ALPHA)
        dwMachine                = IMAGE_FILE_MACHINE_ALPHA ;
        stFrame.AddrPC.Offset    = (unsigned long)stCtx.Fir ;
#else
#error ( "Unknown machine!" )
#endif

        // Loop for the first 512 stack elements.
        for ( DWORD i = 0 ; i < 512 ; i++ )
        {
            if ( FALSE == StackWalk ( dwMachine              ,
                                      hProcess               ,
                                      hProcess               ,
                                      &stFrame               ,
                                      &stCtx                 ,
                                      NULL                   ,
                                      SymFunctionTableAccess ,
                                      GetModBase             ,
                                      NULL                    ) )
            {
                break ;
            }
            // Also check that the address is not zero.  Sometimes
            // StackWalk returns TRUE with a frame of zero.
            if ( 0 != stFrame.AddrPC.Offset )
            {
                vAddrs.push_back ( stFrame.AddrPC.Offset ) ;
            }
        }

        // Now start converting the addresses.
        DWORD dwSizeLeft = dwSize ;
        DWORD dwSymSize ;

        TCHAR szSym [ MAX_PATH * 2 ] ;
        LPTSTR szCurrPos = szString ;

        BOOL bSeenDiagAssert = FALSE ;
        ADDRVECTOR::iterator loop ;
        for ( loop =  vAddrs.begin ( ) ;
              loop != vAddrs.end ( )   ;
              loop++                     )
        {
            dwSymSize = ConvertAddress ( *loop , szSym ) ;
            // Throw out everything with DiagAssert.cpp in it.
            if ( _tcsstr ( szSym , _T ( "DiagAssert.cpp" ) ) )
            {
                bSeenDiagAssert = TRUE ;
                continue ;
            }
            // Throw out anything before the functions in
            // DiagAssert.cpp
            if ( FALSE == bSeenDiagAssert )
            {
                continue ;
            }
            if ( dwSizeLeft < dwSymSize )
            {
                break ;
            }
            _tcscpy ( szCurrPos , szSym ) ;
            szCurrPos += dwSymSize ;
            dwSizeLeft -= dwSymSize ;
        }
    }
}