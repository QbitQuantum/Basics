static HB_BOOL hb_fsTempName( char * pszBuffer, const char * pszDir, const char * pszPrefix )
{
   HB_BOOL fResult;

   pszBuffer[ 0 ] = '\0';

   hb_vmUnlock();

#if defined( HB_OS_WIN )
   {
      LPCTSTR lpPrefix, lpDir;
      LPTSTR lpPrefixFree = NULL, lpDirFree = NULL;

      TCHAR lpBuffer[ HB_PATH_MAX ];
      TCHAR lpTempDir[ HB_PATH_MAX ];

      lpPrefix = pszPrefix ? HB_FSNAMECONV( pszPrefix, &lpPrefixFree ) : NULL;

      if( pszDir && pszDir[ 0 ] != '\0' )
         lpDir = HB_FSNAMECONV( pszDir, &lpDirFree );
      else
      {
         if( ! GetTempPath( HB_PATH_MAX, lpTempDir ) )
         {
            hb_fsSetIOError( HB_FALSE, 0 );
            return HB_FALSE;
         }
         lpTempDir[ HB_PATH_MAX - 1 ] = TEXT( '\0' );
         lpDir = lpTempDir;
      }

      fResult = GetTempFileName( lpDir, lpPrefix ? lpPrefix : TEXT( "hb" ), 0, lpBuffer );

      if( fResult )
         HB_OSSTRDUP2( lpBuffer, pszBuffer, HB_PATH_MAX - 1 );

      if( lpPrefixFree )
         hb_xfree( lpPrefixFree );
      if( lpDirFree )
         hb_xfree( lpDirFree );
   }
#else
   {
      char * pTmpBuffer = ( char * ) hb_xgrab( L_tmpnam + 1 );

      /* TODO: Implement these: */
      HB_SYMBOL_UNUSED( pszDir );
      HB_SYMBOL_UNUSED( pszPrefix );

      pTmpBuffer[ 0 ] = '\0';
      fResult = ( tmpnam( pszBuffer ) != NULL );
      pTmpBuffer[ L_tmpnam ] = '\0';

      if( fResult )
      {
#  if defined( __DJGPP__ )
         /* convert '/' to '\' */
         char * pszDelim = pTmpBuffer;
         while( ( pszDelim = strchr( pszDelim, '/' ) ) != NULL )
            *pszDelim = '\\';
#  endif
         hb_osStrDecode2( pTmpBuffer, pszBuffer, HB_PATH_MAX - 1 );
      }
      hb_xfree( pTmpBuffer );
   }
#endif

   hb_fsSetIOError( fResult, 0 );
   hb_vmLock();

   return fResult;
}