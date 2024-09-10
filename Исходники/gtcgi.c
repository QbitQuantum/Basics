static void hb_gt_cgi_Init( PHB_GT pGT, HB_FHANDLE hFilenoStdin, HB_FHANDLE hFilenoStdout, HB_FHANDLE hFilenoStderr )
{
   PHB_GTCGI pGTCGI;

   HB_TRACE( HB_TR_DEBUG, ( "hb_gt_cgi_Init(%p,%p,%p,%p)", pGT, ( void * ) ( HB_PTRDIFF ) hFilenoStdin, ( void * ) ( HB_PTRDIFF ) hFilenoStdout, ( void * ) ( HB_PTRDIFF ) hFilenoStderr ) );

   pGTCGI = ( PHB_GTCGI ) hb_xgrab( sizeof( HB_GTCGI ) );
   memset( pGTCGI, 0, sizeof( HB_GTCGI ) );
   HB_GTLOCAL( pGT ) = pGTCGI;

   pGTCGI->hStdout = hFilenoStdout;

#if defined( HB_OS_WIN ) && ! defined( HB_OS_WIN_CE )
   if( IsValidCodePage( CP_UTF8 ) )
   {
      pGTCGI->uiOldCP = GetConsoleOutputCP();
      SetConsoleOutputCP( CP_UTF8 );
      HB_GTSELF_SETDISPCP( pGT, "UTF8", NULL, HB_FALSE );
   }
#endif

   pGTCGI->szCrLf = hb_strdup( hb_conNewLine() );
   pGTCGI->nCrLf = strlen( pGTCGI->szCrLf );

   hb_fsSetDevMode( pGTCGI->hStdout, FD_BINARY );

   HB_GTSUPER_INIT( pGT, hFilenoStdin, hFilenoStdout, hFilenoStderr );
   HB_GTSELF_SETFLAG( pGT, HB_GTI_STDOUTCON, HB_TRUE );
}