/* Manager of signals for windows */
static LONG s_signalHandler( int type, int sig, PEXCEPTION_RECORD exc )
{
    HB_SIZE  nPos;
    HB_UINT  uiSig;

    /* let's find the right signal handler. */
    hb_threadEnterCriticalSectionGC( &s_ServiceMutex );

    /* avoid working if PRG signal handling has been disabled */
    if( ! s_bSignalEnabled )
    {
        hb_threadLeaveCriticalSection( &s_ServiceMutex );
        return EXCEPTION_EXECUTE_HANDLER;
    }

    s_bSignalEnabled = HB_FALSE;
    nPos = hb_arrayLen( s_pHooks );
    /* subsig not necessary */
    uiSig = ( HB_UINT ) s_translateSignal( ( HB_UINT ) type, ( HB_UINT ) sig );

    while( nPos > 0 )
    {
        PHB_ITEM pFunction;
        HB_UINT  uiMask;

        pFunction = hb_arrayGetItemPtr( s_pHooks, nPos );
        uiMask    = ( HB_UINT ) hb_arrayGetNI( pFunction, 1 );
        if( ( uiMask & uiSig ) == uiSig )
        {
            PHB_ITEM pExecArray, pRet;
            int      iRet;

            /* we don't unlock the mutex now, even if it is
               a little dangerous. But we are in a signal hander...
               for now just 2 parameters */
            pExecArray = hb_itemArrayNew( 3 );
            hb_arraySetForward( pExecArray, 1, hb_arrayGetItemPtr( pFunction, 2 ) );
            hb_arraySetNI( pExecArray, 2, uiSig );

            /* the third parameter is an array:
             * 1: low-level signal
             * 2: low-level subsignal
             * 3: low-level system error
             * 4: address that rised the signal
             * 5: process id of the signal riser
             * 6: UID of the riser
             */

            pRet = hb_arrayGetItemPtr( pExecArray, 3 );
            hb_arrayNew( pRet, 6 );

            hb_arraySetNI( pRet, HB_SERVICE_OSSIGNAL, type );
            hb_arraySetNI( pRet, HB_SERVICE_OSSUBSIG, sig );
            /* could be meaningless, but does not matter here */
            hb_arraySetNI( pRet, HB_SERVICE_OSERROR, GetLastError() );

            if( type == 0 ) /* exception */
                hb_arraySetPtr( pRet, HB_SERVICE_ADDRESS, ( void * ) exc->ExceptionAddress );
            else
                hb_arraySetPtr( pRet, HB_SERVICE_ADDRESS, NULL );

            /* TODO: */
            hb_arraySetNI( pRet, HB_SERVICE_PROCESS, GetCurrentThreadId() );
            /* TODO: */
            hb_arraySetNI( pRet, HB_SERVICE_UID, 0 );

            pRet = hb_itemDo( pExecArray, 0 );
            iRet = hb_itemGetNI( pRet );
            hb_itemRelease( pRet );
            hb_itemRelease( pExecArray );

            switch( iRet )
            {
            case HB_SERVICE_HANDLED:
                s_bSignalEnabled = HB_TRUE;
                hb_threadLeaveCriticalSection( &s_ServiceMutex );
                return EXCEPTION_CONTINUE_EXECUTION;

            case HB_SERVICE_QUIT:
                s_bSignalEnabled = HB_FALSE;
                hb_threadLeaveCriticalSection( &s_ServiceMutex );
                hb_vmRequestQuit();
#ifndef HB_THREAD_SUPPORT
                hb_vmQuit();
                exit( 0 );
#else
                hb_threadCancelInternal();
#endif
            }
        }
        nPos--;
    }

    s_bSignalEnabled = HB_TRUE;
    return EXCEPTION_EXECUTE_HANDLER;
}