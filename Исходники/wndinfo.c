/*************************************
*  
*  Engine for the CloseAllTVWindows()
*  function.   
*
*  Receives the each library's info.
*
*  Attempts to close window,
*  close library, and free associated
*  menu items for window.
*
**************************************/
BOOL __far __pascal CloseAllLibsWindows( FPTVLIBINFO fpTVLibInfo, LPARAM lParam )
{
  BOOL __far * bAllWndClosed;
  FPTVWNDINFO fpWndInfo;
  HTVWNDINFO hWndInfo;

  HWND hChildWnd;  
  HWND hChildsPopupWnd;  
  
  TVLIBCLOSEWINDOWPROC fpfnTVLibCloseWnd;


  /* Get LPARAM data. */
  bAllWndClosed = (BOOL __far *) lParam;
  
  /* Get library's handle to first window info. */
  hWndInfo = GetLibWndInfo( fpTVLibInfo );
  
  while( hWndInfo != 0 )
  {
    /* Lock it. */
    fpWndInfo = (FPTVWNDINFO) GlobalLock( hWndInfo ) ;
  
    /* Get the handle of the window we are closing. */
    hChildWnd = fpWndInfo->hWnd;

    /* Unlock it. */
    GlobalUnlock( hWndInfo ) ;

    /* 
    ** If we are already in the window's
    ** Wndproc() and awaiting it return,
    ** activate the last popup window.
    */
    if( GetTVEntryCount( hChildWnd ) != 0 )
    {
      /* Change focus to window. */
      MessageBeep( MB_ICONEXCLAMATION );
      hChildsPopupWnd = GetLastActivePopup( hChildWnd );
      SetActiveWindow( hChildsPopupWnd ); 

      /* Not all windows closed. */
      *bAllWndClosed = FALSE; 

      /* Stop enumerating. */
      return FALSE;
    }

    /* 
    **  Tell window to close by sending calling
    **  the TVLibWindowClose() function.
    */   
    /* Retrieve the address of the control's LibInfo() function. */
    (FARPROC) fpfnTVLibCloseWnd = GetProcAddress( fpTVLibInfo->hInstance, MAKEINTRESOURCE(TVLIB_CLOSEWINDOW_ORD) );
                                              
    /* Verify the GetProcAddress() function returned data. */
    if ( fpfnTVLibCloseWnd == NULL)
    {
      /* Not all windows closed. */
      *bAllWndClosed = FALSE; 

      /* Error message. */
      MessageBox(  NULL, (LPSTR)"GetProcAddress() failed!", (LPSTR)"Library Functions", MB_ICONHAND | MB_OK );

      /* Stop enumerating. */
      return FALSE;
    }
  
    /* 
    **  Restore the window's WndProc() to its original
    **  WndProc() so we aren't trapping for the
    **  WM_NCDESTROY message and won't therefore call
    **  PostCloseLibrary().
    */
//    RemoveChildWindowFilter( hChildWnd );

    /* Tell the library to close the window. */
    (*fpfnTVLibCloseWnd)(hChildWnd);

    /* 
    **  Window is still around. 
    */
    if( IsWindow( hChildWnd ) )
    {
      /* 
      **  Set the window's WndProc() to our special
      **  WndProc() so we can keep trapping for the
      **  WM_NCDESTROY message to call
      **  PostCloseLibrary().
      */
//      SetChildWindowFilter( hChildWnd );

      /* Not all windows closed. */
      *bAllWndClosed = FALSE; 
      
      /* Stop enumerating. */
      return FALSE;
    }
  
    /* 
    **  Window is not still around. 
    */

    /* Remove menu alias' associated with the window. */  
    DeleteMenuInfoForWnd( hChildWnd );
    
    /* Find and delete the window info. */
    DeleteWndInfo( &(fpTVLibInfo)->hTVWndInfo, hChildWnd );
  
    /* Close the library. */
    CloseLibrary( fpTVLibInfo );

    /* Get library's handle to first window info. */
    hWndInfo = GetLibWndInfo( fpTVLibInfo );
  }

  /* Keep enumerating - next library. */
  return TRUE;
}