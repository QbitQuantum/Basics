int  set_console_cursor_shape( FILE* confp, int ins )
{
    CONSOLE_CURSOR_INFO  ci;
    HANDLE  hStdErr;
    int     cons_fd;

    if ( !confp )
    {
        errno = EINVAL;
        return -1;
    }

    if ( ! _isatty( cons_fd = fileno( confp ) ) )
    {
        errno = EBADF;
        return -1;
    }

    hStdErr = (HANDLE) _get_osfhandle( cons_fd );
    ASSERT( hStdErr && INVALID_HANDLE_VALUE != hStdErr );

    ci.bVisible = TRUE;
    ci.dwSize = ins ? 20 : 100; // (note: values are percent of cell height)

    if ( !SetConsoleCursorInfo( hStdErr, &ci ) )
    {
        errno = EIO;
        return -1;
    }

    return 0;
}