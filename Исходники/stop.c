int main( int argc, char **argv )
{
    POINTER mem_lock;
    uintptr_t size = 0;
    TEXTCHAR *myname = StrDup( pathrchr( DupCharToText( argv[0] ) ) );
    TEXTCHAR *endname;
    TEXTCHAR lockname[256];
    if( myname )
        myname++;
    else
        myname = DupCharToText( argv[0] );
    // go to the .exe extension
    endname = (TEXTCHAR*)StrRChr( myname, '.' );
    if( endname )
    {
        // remove .exe extension
        endname[0] = 0;
        // go to the .stop extension
        endname = (TEXTCHAR*)StrRChr( myname, '.' );
    }
    if( endname )
    {
        // remove .stop extension
        endname[0] = 0;
    }
    else
    {
        // this would be an invalid name.
        return 0;
    }
    snprintf( lockname, sizeof( lockname ), WIDE( "%s.instance.lock" ), myname );
    lprintf( WIDE( "Checking lock %s" ), lockname );
    mem_lock = OpenSpace( lockname
                          , NULL
                          //, WIDE("memory.delete")
                          , &size );
    if( mem_lock )
    {
#ifdef WIN32
        PRENDER_INTERFACE pri = GetDisplayInterface();
        PVIDEO video = (PVIDEO)mem_lock;
        if( video->hWndOutput )
        {
            ForceDisplayFocus( video );

            keybd_event( VK_MENU, 56, 0, 0 );
            keybd_event( VK_F4, 62, 0, 0 );
            keybd_event( VK_F4, 62, KEYEVENTF_KEYUP, 0 );
            keybd_event( VK_MENU, 56, KEYEVENTF_KEYUP, 0 );
#if 0
            {
                int tick = timeGetTime();
                while( ( tick + 15000  > timeGetTime() ) && IsWindow( video->hWndOutput ) )
                    WakeableSleep( 100 );
                if( IsWindow( video->hWndOutput ) )
#define WM_EXIT_PLEASE 0xd1e
                    if( !SendMessage( video->hWndOutput, WM_QUERYENDSESSION, 0, 0 ) )
                        printf( "Failed to post queyendsession." );
            }
#endif
        }
        else
        {
            // region found, but no content...
        }
#endif
    }
    else
        lprintf( WIDE("lock region not found.") );
    return 0;
}