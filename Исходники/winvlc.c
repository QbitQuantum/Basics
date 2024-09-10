static void get_crashdump_path(wchar_t * wdir)
{
    if( S_OK != SHGetFolderPathW( NULL,
                        CSIDL_APPDATA | CSIDL_FLAG_CREATE,
                        NULL, SHGFP_TYPE_CURRENT, wdir ) )
        fprintf( stderr, "Can't open the vlc conf PATH\n" );

    swprintf( wdir+wcslen( wdir ), L"%s", L"\\vlc\\crashdump" );
}