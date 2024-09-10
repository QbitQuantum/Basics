/**
 * Cleans up after system_Init() and system_Configure().
 */
void system_End(void)
{
    HWND ipcwindow;

    /* FIXME: thread-safety... */
    if (p_helper)
    {
        if( ( ipcwindow = FindWindow( 0, L"VLC ipc "VERSION ) ) != 0 )
        {
            SendMessage( ipcwindow, WM_QUIT, 0, 0 );
        }
        vlc_object_release (p_helper);
        p_helper = NULL;
    }

    timeEndPeriod(5);

    /* XXX: In theory, we should not call this if WSAStartup() failed. */
    WSACleanup();
}