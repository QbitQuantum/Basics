int __mbinit( int codepage )
{
#ifdef __NT__
    CPINFO                  cpInfo;
    BOOL                    rc;
#elif defined __OS2__
    COUNTRYCODE             countryInfo;
    unsigned short          leadBytes[6];
    APIRET                  rc;
    OS_UINT                 buf[8];
    OS_UINT                 bytes;
#elif defined __OSI__
#elif defined __DOS__
    unsigned short          __far *leadBytes;
#elif defined __WINDOWS__
    DWORD                   version;
#elif defined __LINUX__
#elif defined __RDOS__
#endif

    clear_dbcs_table();
    /*** Handle values from _setmbcp ***/
    if( codepage == _MBINIT_CP_ANSI ) {
#ifdef __NT__
        codepage = GetACP();
#else
        codepage = 0;
#endif
    } else if( codepage == _MBINIT_CP_OEM ) {
#ifdef __NT__
        codepage = GetOEMCP();
#else
        codepage = 0;
#endif
    } else if( codepage == _MBINIT_CP_SBCS ) {
        return( 0 );
    } else if( codepage == _MBINIT_CP_932 ) {
        _set_dbcs_table( 0x81, 0x9F );
        _set_dbcs_table( 0xE0, 0xFC );
        __IsDBCS = 1;
        __MBCodePage = 932;
        return( 0 );
    }

#ifdef __NT__
    /*** Initialize the __MBCSIsTable values ***/
    if( codepage == 0 )
        codepage = CP_OEMCP;
    rc = GetCPInfo( codepage, &cpInfo );    /* get code page info */
    if( rc == FALSE )
        return( 1 );
    set_dbcs_table( (unsigned short *)cpInfo.LeadByte );
    /*** Update __MBCodePage ***/
    if( codepage == CP_OEMCP ) {
        __MBCodePage = GetOEMCP();
    } else {
        __MBCodePage = codepage;
    }
#elif defined __OS2__
    /*** Initialize the __MBCSIsTable values ***/
    countryInfo.country = 0;                /* default country */
    countryInfo.codepage = codepage;        /* specified code page */
  #if defined(__WARP__)
    rc = DosQueryDBCSEnv( sizeof( leadBytes ), &countryInfo, (PCHAR)leadBytes );
  #else
    rc = DosGetDBCSEv( sizeof( leadBytes ), &countryInfo, (PCHAR)leadBytes );
  #endif
    if( rc != 0 )
        return( 1 );
    set_dbcs_table( leadBytes );
    /*** Update __MBCodePage ***/
    if( codepage == 0 ) {
  #if defined(__386__) || defined(__PPC__)
        rc = DosQueryCp( sizeof( buf ), &buf, &bytes );
  #else
        rc = DosGetCp( sizeof( buf ), &buf, &bytes );
  #endif
        if( rc != 0 ) {
            __MBCodePage = 0;
        } else {
            __MBCodePage = (unsigned int)buf[0];
        }
    } else {
        __MBCodePage = codepage;
    }
#elif defined __OSI__
#elif defined __DOS__
    /*** Initialize the __MBCSIsTable values ***/
    if( codepage != 0 )
        return( 1 );        /* can only handle default */
    leadBytes = dos_get_dbcs_lead_table();
    if( leadBytes == NULL )
        return( 0 );
    set_dbcs_table( leadBytes );
    __MBCodePage = dos_get_code_page();
#elif defined __WINDOWS__
    /*** Initialize the __MBCSIsTable values ***/
    if( codepage != 0 )
        return( 1 );        /* can only handle default */
    version = GetVersion();
    if( LOWORD(version) < 0x0A03 )
        return( 1 );        /* 3.1+ needed */
    set_dbcs_table();
    __MBCodePage = GetKBCodePage();
#elif defined __LINUX__
#elif defined __RDOS__
#endif
    return( 0 );                                /* return success code */
}