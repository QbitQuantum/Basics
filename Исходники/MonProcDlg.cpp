void
CMonProcDlg::OnCheckTomcatButton( )
{
   CString csTomcat = "java";
   CWnd    *pWnd = 0;
   bool    bStatus;
#ifdef DEBUG_TRACE
   bool    bTrace = FALSE;
#endif
   int     nCnt;
   int     nStartupDelay = m_nStartupDelay / 20;
   long    lRC;

   if ( nStartupDelay < 100 )
      nStartupDelay = 100;

   CButton *pCheckButton = (CButton *) GetDlgItem( IDC_CHECKTOMCAT );
   CButton *pCancelButton = (CButton *) GetDlgItem( IDC_CANCELCHECKTOMCAT );

   pCheckButton->EnableWindow( FALSE );
   PumpMessages( );

   g_nCheckTomcat = 1;  // going to begin checking Tomcat
   while ( g_nCheckTomcat )
   {
      if ( !m_win32proc.GetProcessStatus( &csTomcat, &bStatus ) )
      {
         AfxMessageBox( m_win32proc.GetLastError( ) );
         return;
      }

      if ( pWnd == 0 && m_csWindowTitle.IsEmpty( ) == FALSE )
         pWnd = FindWindow( m_csWindowClass, m_csWindowTitle );

      if ( bStatus == FALSE ) // Tomcat not running
      {
         if ( m_nWriteLogMessage )
         {
            if ( pWnd && ::IsWindow( pWnd->m_hWnd ) )
            {
               ::SendMessage( pWnd->m_hWnd, WM_USER + m_nWriteLogMessage, 0, 0 );
               PumpMessages( );
            }
         }

         WinExec( m_csKillApp, SW_SHOW );
         pWnd = 0;
#ifdef DEBUG_TRACE
         TRACE0( "Tomcat not running\n" );
         bTrace = FALSE;
#endif
         Sleep( m_nKillAppDelay );  // two-second delay to let OE go down
         WinExec( m_csStartup, SW_SHOW );
#ifdef DEBUG_TRACE
         TRACE0( "WinExec Tomcat startup\n" );
#endif

         nCnt = 0;
         while ( g_nCheckTomcat && nCnt++ < 20 )
         {
            PumpMessages( );
            Sleep( nStartupDelay );  // twenty-second delay to let Tomcat start
         }
      }
      else
      {
#ifdef DEBUG_TRACE
         if ( bTrace == FALSE )
         {
            TRACE0( "Tomcat is running\n" );
            bTrace = TRUE;
         }
#endif
         if ( pWnd )
         {
            if ( ::IsWindow( pWnd->m_hWnd ) )
            {
               lRC = ::SendMessage( pWnd->m_hWnd, WM_USER + m_nQueryAliveMessage, 0, 0 );
               PumpMessages( );
            }
            else
               lRC = 0;
         }
         else
            lRC = -1;

         if ( lRC != -1 )
         {
         // ::SendMessage( pWnd->m_hWnd, WM_USER + m_nWriteLogMessage, 0, 0 );  doesn't exist
         // PumpMessages( );
            WinExec( m_csKillApp, SW_SHOW );   // stop OE
            pWnd = 0;
#ifdef DEBUG_TRACE
            TRACE0( "Zeidon not running\n" );
            bTrace = FALSE;
#endif
            WinExec( m_csShutdown, SW_SHOW );  // stop Tomcat
            Sleep( m_nKillAppDelay );  // two-second delay to let OE go down
            WinExec( m_csStartup, SW_SHOW );
#ifdef DEBUG_TRACE
            TRACE0( "WinExec Tomcat2 startup\n" );
#endif
         }
      }

      if ( g_nCheckTomcat == 1 )  // beginning to check Tomcat
      {
         g_nCheckTomcat = 2;  // check for Tomcat now in full swing
         pCheckButton->ShowWindow( SW_HIDE );
         pCancelButton->ShowWindow( SW_SHOW );
      }

      PumpMessages( );
      Sleep( 1000 );  // one-second delay to let other apps work
   }
}