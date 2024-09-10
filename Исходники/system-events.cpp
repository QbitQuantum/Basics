INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_HOTKEY:
		switch ( HIWORD( lParam ) )
		{
		case VK_RIGHT:
			PostEvent( EVENT_TYPE_HOTKEY_NEXT );
			break;

		case VK_SPACE:
			PostEvent( EVENT_TYPE_HOTKEY_PAUSE );
			break;
		}
		break;
	
   case WM_WTSSESSION_CHANGE:
      switch ( wParam )
      {
      case WTS_SESSION_LOCK:	  
			PostEvent( EVENT_TYPE_CONSOLE_LOCK );
			break;
		 
      case WTS_SESSION_UNLOCK:
			PostEvent( EVENT_TYPE_CONSOLE_UNLOCK );
			break;
      }
      break;

   case WM_WINDOWPOSCHANGING:
      {
         WINDOWPOS * pPos = (WINDOWPOS*) lParam;
         pPos->flags |= SWP_HIDEWINDOW;
         pPos->flags &= ~SWP_SHOWWINDOW;
      }
      break;
   
	case WM_INITDIALOG:
		g_hwnd = hDlg;
		WTSRegisterSessionNotification( hDlg, NOTIFY_FOR_ALL_SESSIONS );
		RegisterHotKey( g_hwnd, 1, MOD_ALT | MOD_CONTROL, VK_SPACE );
		RegisterHotKey( g_hwnd, 2, MOD_ALT | MOD_CONTROL, VK_RIGHT );
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}