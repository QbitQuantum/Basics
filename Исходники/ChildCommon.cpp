// unhide and display the window, if the current window is maximized make sure we
// maximize the window we're unhiding.
void CChildCommon::ActivateWindow( void )
{
  BOOL bMaximized = FALSE;
  CWindow ActiveWnd = g_pMainWnd->MDIGetActive(&bMaximized);
  CWindow ParentWnd = ActiveWnd.GetParent();

  if (bMaximized)
    ParentWnd.SetRedraw(FALSE);

  g_pMainWnd->MDIActivate(m_hWnd);
#ifdef USE_TABBEDMDI
	::SendMessage(GetParent(), UWM_MDICHILDACTIVATIONCHANGE, (WPARAM)m_hWnd, 0);
  SendMessage(WM_UPDATETAB, (WPARAM)0, (LPARAM)NULL);
  //SetTabText("SHOWN");
#endif

	if(bMaximized == TRUE)
  {
		ShowWindow(SW_SHOWMAXIMIZED);
		
		ParentWnd.SetRedraw(TRUE);
		ParentWnd.RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ALLCHILDREN);
	}

  /*
  if (BOOLPREF(PREF_bHideNotMinimize))
  {
    SetWindowPos(HWND_TOP,0,0,0,0,SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW );
    RedrawWindow(0,0,RDW_FRAME|RDW_INVALIDATE|RDW_ERASENOW|RDW_ALLCHILDREN);
  }
  else
  {
    g_pMainWnd->MDIActivate(m_hWnd);
  }
  */
}