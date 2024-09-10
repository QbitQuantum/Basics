/*
 * WHtmlHelp - open an HTML Help file
 */
bool WHtmlHelp( HWND hwnd, LPCSTR helpFile, UINT fuCommand, HELP_DATA data )
{
#ifdef __NT__
    char    buff[_MAX_PATH];
    if( pfnHtmlHelp == NULL ) {
        HINSTANCE hInstance = LoadLibrary( "HHCTRL.OCX" );
        if( hInstance == NULL ) {
            return( false );
        }
        pfnHtmlHelp = (PFNHH)GetProcAddress( hInstance, "HtmlHelpA" );
        if( pfnHtmlHelp == NULL ) {
            return( false );
        }
    }
    switch( fuCommand ) {
    case HELP_CONTENTS:
        fuCommand = HH_DISPLAY_TOC;
        break;
    case HELP_CONTEXT:
        fuCommand = HH_HELP_CONTEXT;
        break;
    case HELP_PARTIALKEY:
    case HELP_KEY:
        fuCommand = HH_DISPLAY_INDEX;
        break;
    default:
        return( false );
    }
    _searchenv( helpFile, "WHTMLHELP", buff );
    if( buff[0] != '\0' ) {
        helpFile = buff;
    }
    return( pfnHtmlHelp( hwnd, helpFile, fuCommand, data ) != NULL );
#else
    hwnd = hwnd;
    helpFile = helpFile;
    fuCommand = fuCommand;
    data = data;
    return( false );
#endif

} /* WHtmlHelp */