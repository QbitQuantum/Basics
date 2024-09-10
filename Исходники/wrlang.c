static res_language_enumeration check_code_page( void )
/*****************************************************/
{
    unsigned int        codepage = 0;
#if defined __OS2__
    OS_UINT             cp;
    OS_UINT             bytesOutput;
#elif defined __WINDOWS__
    char                lang[4];
#endif

    /*** Determine the system default code page ***/
    #if defined __NT__
        codepage = GetOEMCP();
    #elif defined __OS2__
        DosGetCp( 2, &cp, &bytesOutput );
        codepage = cp;
    #elif defined __OSI__
        codepage = 437;         // Maybe we could try harder...
    #elif defined __DOS__
        codepage = dos_get_code_page();
    #elif defined __WINDOWS__
        if( GetProfileString( "Intl", "sLanguage", "ENU", lang, 4 ) ) {
            if( !stricmp( lang, "JPN" ) )  codepage = 932;
        }
    #endif

    /*** Try to match the returned code page to known ones ***/
    switch( codepage ) {
        case 932:   return( RLE_JAPANESE );
        default:    return( RLE_ENGLISH );
    }
}