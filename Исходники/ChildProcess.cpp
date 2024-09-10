int __cdecl main( int argc, char **argv )
{
    /* local variables */
    HANDLE                  hEvent = NULL;
    WCHAR                   wcName[] = {'P','A','L','R','o','c','k','s','\0'};
    LPWSTR                  lpName = wcName;
    
    int result = PASS;

    /* initialize the PAL */
    if( PAL_Initialize(argc, argv) != 0 )
    {
	    return( FAIL );
    }


    /* open a handle to the event created in the child process */
    hEvent = OpenEventW( EVENT_ALL_ACCESS,  /* we want all rights */
                         FALSE,             /* no inherit         */
                         lpName );

    if( hEvent == NULL )
    {
        /* ERROR */
        Trace( "ERROR:%lu:OpenEventW() call failed\n", GetLastError() );
        result = FAIL;
        goto parentwait;
    }

    /* set the event -- should take effect in the child process */
    if( ! SetEvent( hEvent ) )
    {
        /* ERROR */
        Trace( "ERROR:%lu:SetEvent() call failed\n", GetLastError() );
        result = FAIL;
    }

parentwait:
    /* close the event handle */
    if( ! CloseHandle( hEvent ) )
    {
        /* ERROR */
        Fail(   "ERROR:%lu:CloseHandle() call failed in child\n",
                GetLastError());
    }

    /* terminate the PAL */
    PAL_TerminateEx(result);

    /* return success or failure */
    return result;
}