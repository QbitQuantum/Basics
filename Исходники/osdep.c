int x264_rename( const char *oldname, const char *newname )
{
    wchar_t oldname_utf16[MAX_PATH];
    wchar_t newname_utf16[MAX_PATH];
    if( utf8_to_utf16( oldname, oldname_utf16 ) && utf8_to_utf16( newname, newname_utf16 ) )
    {
        /* POSIX says that rename() removes the destination, but Win32 doesn't. */
        _wunlink( newname_utf16 );
        return _wrename( oldname_utf16, newname_utf16 );
    }
    return -1;
}