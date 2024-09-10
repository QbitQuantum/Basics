static void MBInit( void )
/************************/
{
#if defined( __NT__ ) && !defined( __UNIX__ )
    int                 countRange, countVal;
    CPINFO              cpInfo;
    BOOL                rc;
#elif defined __OS2__ || defined __OS2_PM__
    int                 countRange, countVal;
    COUNTRYCODE         countryInfo;
    CHAR                leadBytes[12];
  #ifdef _M_I86
        USHORT          rc;
  #else
        APIRET          rc;
  #endif
#elif defined( __WINDOWS__ ) || defined( __UNIX__ )
    int                 countVal;
    DWORD               version;
#endif

    memset( __CharLenTable, 1, sizeof( __CharLenTable ) );              /* zero table to start */

    #if defined( __NT__) && !defined( __UNIX__ )
        /*** Initialize the __CharLenTable values ***/
        rc = GetCPInfo( CP_OEMCP, &cpInfo );    /* get code page info */
        if( rc == FALSE )  return;
        for( countRange=0; !(cpInfo.LeadByte[countRange]==0x00 &&
             cpInfo.LeadByte[countRange+1]==0x00); countRange+=2 ) {
            for( countVal=cpInfo.LeadByte[countRange];
                 countVal<=cpInfo.LeadByte[countRange+1]; countVal++) {
                __CharLenTable[countVal] = 2;
                IsDBCS = TRUE;
            }
        }
    #elif defined __OS2__ || defined __OS2_PM__
        /*** Initialize the __CharLenTable values ***/
        countryInfo.country = 0;                /* default country */
        countryInfo.codepage = 0;       /* specified code page */
      #ifdef _M_I86
        rc = DosGetDBCSEv( 12, &countryInfo, leadBytes );
      #else
        rc = DosQueryDBCSEnv( 12, &countryInfo, leadBytes );
      #endif
        if( rc != 0 )  return;
        for( countRange=0; !(leadBytes[countRange]==0x00 &&
             leadBytes[countRange+1]==0x00); countRange+=2 ) {
            for( countVal=leadBytes[countRange];
                 countVal<=leadBytes[countRange+1]; countVal++) {
                __CharLenTable[countVal] = 2;
                IsDBCS = TRUE;
            }
        }
    #elif defined( __WINDOWS__ ) || defined( __UNIX__ )
        /*** Initialize the __CharLenTable values ***/
        version = GetVersion();
        if( LOWORD(version) < ((10<<8)+3) )  return;   /* 3.1+ needed */
        for( countVal=0; countVal<256; countVal++ ) {
            if( IsDBCSLeadByte( (BYTE)countVal ) ) {
                __CharLenTable[countVal] = 2;
                IsDBCS = TRUE;
            }
        }
    #endif

}