static int hb_unzipExtractCurrentFile( unzFile hUnzip, const char * szFileName, const char * szPassword )
{
   char          szName[ HB_PATH_MAX ];
   HB_SIZE       nPos, nLen;
   char          cSep, * pString;
   unz_file_info ufi;
   int        iResult;
   HB_FHANDLE hFile;

   iResult = unzGetCurrentFileInfo( hUnzip, &ufi, szName, HB_PATH_MAX - 1,
                                    NULL, 0, NULL, 0 );
   if( iResult != UNZ_OK )
      return iResult;

   iResult = unzOpenCurrentFilePassword( hUnzip, szPassword );

   if( iResult != UNZ_OK )
      return iResult;

   if( szFileName )
      hb_strncpy( szName, szFileName, sizeof( szName ) - 1 );

   nLen = strlen( szName );

   /* Test shows that files in subfolders can be stored to zip file without
      explicitly adding folder. So, let's create a required path */

   nPos = 1;
   while( nPos < nLen )
   {
      cSep = szName[ nPos ];

      /* allow both path separators, ignore terminating path separator */
      if( ( cSep == '\\' || cSep == '/' ) && nPos < nLen - 1 )
      {
         szName[ nPos ] = '\0';
         hb_fsMkDir( szName );
         szName[ nPos ] = cSep;
      }
      nPos++;
   }

   if( ufi.external_fa & 0x40000000 ) /* DIRECTORY */
   {
      hb_fsMkDir( szName );
      iResult = UNZ_OK;
   }
   else
   {
      hFile = hb_fsCreate( szName, FC_NORMAL );

      if( hFile != FS_ERROR )
      {
         pString = ( char * ) hb_xgrab( HB_Z_IOBUF_SIZE );

         while( ( iResult = unzReadCurrentFile( hUnzip, pString, HB_Z_IOBUF_SIZE ) ) > 0 )
            hb_fsWriteLarge( hFile, pString, ( HB_SIZE ) iResult );

         hb_xfree( pString );

#if defined( HB_OS_WIN )
         {
            FILETIME   ftutc, ft;
            SYSTEMTIME st;

            st.wSecond       = ( WORD ) ufi.tmu_date.tm_sec;
            st.wMinute       = ( WORD ) ufi.tmu_date.tm_min;
            st.wHour         = ( WORD ) ufi.tmu_date.tm_hour;
            st.wDay          = ( WORD ) ufi.tmu_date.tm_mday;
            st.wMonth        = ( WORD ) ufi.tmu_date.tm_mon + 1;
            st.wYear         = ( WORD ) ufi.tmu_date.tm_year;
            st.wMilliseconds = 0;

            if( SystemTimeToFileTime( &st, &ft ) &&
                LocalFileTimeToFileTime( &ft, &ftutc ) )
            {
               SetFileTime( ( HANDLE ) hb_fsGetOsHandle( hFile ), &ftutc, &ftutc, &ftutc );
            }
         }
#endif

         hb_fsClose( hFile );
      }
      else
         iResult = -200 - hb_fsError();
   }
   unzCloseCurrentFile( hUnzip );

#if defined( HB_OS_WIN )
   {
      LPTSTR  lpFileNameFree;
      LPCTSTR lpFileName = HB_FSNAMECONV( szName, &lpFileNameFree );

      SetFileAttributes( ( LPCTSTR ) lpFileName, ufi.external_fa & 0xFF );

      if( lpFileNameFree )
         hb_xfree( lpFileNameFree );
   }
#elif defined( HB_OS_UNIX ) || defined( __DJGPP__ )
   {
      struct utimbuf utim;
      struct tm      st;
      time_t         tim;

      char *       pszFree;
      const char * szNameOS = hb_fsNameConv( szName, &pszFree );

#  if defined( __DJGPP__ )
      _chmod( szNameOS, 1, ufi.external_fa & 0xFF );
#  else
      HB_FATTR ulAttr = ufi.external_fa;

      if( ( ulAttr & 0xFFFF0000 ) == 0 )
         ulAttr = hb_translateExtAttr( szName, ulAttr );

      chmod( szNameOS,
             ( ( ulAttr & 0x00010000 ) ? S_IXOTH : 0 ) |
             ( ( ulAttr & 0x00020000 ) ? S_IWOTH : 0 ) |
             ( ( ulAttr & 0x00040000 ) ? S_IROTH : 0 ) |
             ( ( ulAttr & 0x00080000 ) ? S_IXGRP : 0 ) |
             ( ( ulAttr & 0x00100000 ) ? S_IWGRP : 0 ) |
             ( ( ulAttr & 0x00200000 ) ? S_IRGRP : 0 ) |
             ( ( ulAttr & 0x00400000 ) ? S_IXUSR : 0 ) |
             ( ( ulAttr & 0x00800000 ) ? S_IWUSR : 0 ) |
             ( ( ulAttr & 0x01000000 ) ? S_IRUSR : 0 ) );
#  endif
      memset( &st, 0, sizeof( st ) );

      st.tm_sec  = ufi.tmu_date.tm_sec;
      st.tm_min  = ufi.tmu_date.tm_min;
      st.tm_hour = ufi.tmu_date.tm_hour;
      st.tm_mday = ufi.tmu_date.tm_mday;
      st.tm_mon  = ufi.tmu_date.tm_mon;
      st.tm_year = ufi.tmu_date.tm_year - 1900;

      tim = mktime( &st );
#  if defined( HB_HAS_LOCALTIME_R )
      gmtime_r( &tim, &st );
#  else
      st = *gmtime( &tim );
#  endif
      utim.actime = utim.modtime = mktime( &st );

      utime( szNameOS, &utim );

      if( pszFree )
         hb_xfree( pszFree );
   }
#elif defined( HB_OS_DOS )
   {
#  if defined( __RSX32__ ) || defined( __GNUC__ )
      char * pszFree;

      _chmod( hb_fsNameConv( szName, &pszFree ), 1, ufi.external_fa & 0xFF );

      if( pszFree )
         hb_xfree( pszFree );
#  else
      hb_fsSetAttr( szName, ufi.external_fa & 0xFF );
#  endif
   }

#elif defined( HB_OS_OS2 )
   {
      FILESTATUS3 fs3;
      APIRET      ulrc;
      HB_FATTR    ulAttr = FILE_NORMAL;
      int         iAttr  = ufi.external_fa & 0xFF;

      char *       pszFree;
      const char * szNameOS = hb_fsNameConv( szName, &pszFree );

      if( iAttr & HB_FA_READONLY )
         ulAttr |= FILE_READONLY;
      if( iAttr & HB_FA_HIDDEN )
         ulAttr |= FILE_HIDDEN;
      if( iAttr & HB_FA_SYSTEM )
         ulAttr |= FILE_SYSTEM;
      if( iAttr & HB_FA_ARCHIVE )
         ulAttr |= FILE_ARCHIVED;

      ulrc = DosQueryPathInfo( ( PCSZ ) szNameOS, FIL_STANDARD, &fs3, sizeof( fs3 ) );

      if( ulrc == NO_ERROR )
      {
         FDATE fdate;
         FTIME ftime;

         fdate.year    = ufi.tmu_date.tm_year - 1980;
         fdate.month   = ufi.tmu_date.tm_mon;
         fdate.day     = ufi.tmu_date.tm_mday;
         ftime.hours   = ufi.tmu_date.tm_hour;
         ftime.minutes = ufi.tmu_date.tm_min;
         ftime.twosecs = ufi.tmu_date.tm_sec / 2;

         fs3.attrFile = ulAttr;

         fs3.fdateCreation = fs3.fdateLastAccess = fs3.fdateLastWrite = fdate;
         fs3.ftimeCreation = fs3.ftimeLastAccess = fs3.ftimeLastWrite = ftime;
         ulrc = DosSetPathInfo( ( PCSZ ) szNameOS, FIL_STANDARD,
                                &fs3, sizeof( fs3 ), DSPI_WRTTHRU );
      }

      if( pszFree )
         hb_xfree( pszFree );
   }
#else
   {
      hb_fsSetAttr( szName, ufi.external_fa );
   }
#endif

   return iResult;
}