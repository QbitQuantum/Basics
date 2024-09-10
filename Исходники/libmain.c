long __far __pascal __export SDKWndProc( HWND hWnd, WORD Msg, WORD wParam, LONG lParam )
{
  CREATESTRUCT __far * lpCreateStruct;   /* Data passed in LPARAM. */
  HWND __far * hTwinViewWnd;             /* Handle to the TWINVIEW.EXE main window. */

  HWNDDATA        hWndData ;             /* Handle to window extrabyte data. */
  FPWNDDATA       fpWndData ;            /* Pointer to window extrabyte data. */
  
  char lpszClassName[ MAX_CLASS_NAME ];  /* Name of a window's class. */
  
  HWND hHelpWnd;                         /* Handle to a help window. */

  
  /* 
  ** Handle WinHelp special messages - WM_WINDOC & WM_WINHELP. 
  */

  if( Msg == GetWINHELPMsg() || Msg == GetWINDOCMsg() )
  {
    /* Get window list. */
    hWndData = (HWNDDATA) GetWindowWord (hWnd, TVL_WNDEXTRABYTES ) ;
    fpWndData = (FPWNDDATA) GlobalLock( hWndData );

    /* Get/create the application's help window. */
    hHelpWnd = GetHelpWindow( hWnd, (HWND) wParam, &(fpWndData)->hWndInfoList );
          
    /* Send message to correct help window. */  
    if( hHelpWnd != 0 )
    {
      /* Route the message to the correct help window. */
      SendMessage( hHelpWnd, Msg, wParam, lParam );
    }

    return 0 ;
  }


  /* 
  ** Other Windows messages. 
  */
  switch (Msg)
  {
    case WM_CREATE:
    {
      /* Allocate memory for window private data. */
      hWndData = GlobalAlloc ( LMEM_MOVEABLE | LMEM_ZEROINIT, sizeof (WNDDATA) ) ;
                              
      /* Error retrieving memory. */
      if ( hWndData == NULL ) 
      {
        /* Allocation error. */ 
        MsgBox( GetLibInst(), hWnd, IDS_ERRORTITLE, IDS_MEMORYALLOC, MB_ICONHAND | MB_OK );
        return -1;
      }

      /* Initialize the window data. */
      fpWndData = (FPWNDDATA) GlobalLock( hWndData );
      fpWndData->hTwinViewWnd = 0;
      fpWndData->hWndInfoList = 0;
      GlobalUnlock( hWndData );

      /* Save handle to allocated window data. */
      SetWindowWord ( hWnd, TVL_WNDEXTRABYTES, (WORD) hWndData ) ;
        
      /*
      ** If we are running under TWINVIEW.EXE when the last help 
      ** window is tell TWINVIEW.EXE to close also.  To do this we
      ** will need to save the window handle for TWINVIEW.EXE's 
      ** main window.
      */

      /* Get class of window. */
      GetClassName( hWnd, (LPSTR) lpszClassName, MAX_CLASS_NAME );

      /* 
      ** If we were launched by TWINVIEW.EXE, via a MS-Windows
      ** WinHelp() call, save TWINVIEW's window handle? 
      */
      if( _fstricmp( lpszClassName, MS_WINHELP_CLASS ) == 0 )
      {
        /* Get TWINVIEW's window handle.*/
        lpCreateStruct = ( CREATESTRUCT __far * ) lParam;
        hTwinViewWnd = ( HWND __far * ) lpCreateStruct->lpCreateParams;
      
        /* Save TWINVIEW's window handle.*/
        fpWndData = (FPWNDDATA) GlobalLock( hWndData );
        fpWndData->hTwinViewWnd = *hTwinViewWnd;
        GlobalUnlock( hWndData );
      }
            
      /* Success. */
      return 0;
    }
    
    
    /* 
    ** A help window closed - see if we should close this main redirector 
    ** window. 
    */
    case HELPWM_CLOSE:
    {
      /* Get window list. */
      hWndData = (HWNDDATA) GetWindowWord (hWnd, TVL_WNDEXTRABYTES ) ;
      fpWndData = (FPWNDDATA) GlobalLock( hWndData );
      
      /* Remove the window from the list. */
      RemoveHelpWndInfo( &(fpWndData)->hWndInfoList, (HWND) wParam );
          
      /* Still have help windows under this window. */
      if( GetHelpWndCount( fpWndData->hWndInfoList ) != 0 ) 
      {
        GlobalUnlock( hWndData );
        return 0;
      }
      
      /* 
      ** Last help window - close this parent window. 
      */
      
      /* 
      ** If we were launched by TWINVIEW.EXE, via a MS-Windows
      ** WinHelp() call, close down TWINVIEW.EXE.
      */
      GetClassName( hWnd, (LPSTR) lpszClassName, MAX_CLASS_NAME );
          
      if( _fstricmp( lpszClassName, MS_WINHELP_CLASS ) == 0 )
      {
        /* Tell twinview to close down. */
        PostMessage( fpWndData->hTwinViewWnd, WM_SYSCOMMAND, SC_CLOSE, 0L );
      }
                
      GlobalUnlock( hWndData );
              
      /* Destroy the window. */
      DestroyWindow( hWnd ) ;
              
      return 0;
    }

    
    case WM_DESTROY:
    {
      hWndData = (HWNDDATA) GetWindowWord (hWnd, TVL_WNDEXTRABYTES ) ;
      GlobalFree ( hWndData ) ;
      return 0 ; 
    }
  }

  // Pass unprocessed message to DefWindowProc
  return DefWindowProc (hWnd, Msg, wParam, lParam) ;
}