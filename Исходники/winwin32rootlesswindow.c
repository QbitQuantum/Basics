void
winMWExtWMReorderWindows (ScreenPtr pScreen)
{
  winScreenPriv(pScreen);
  HWND hwnd = NULL;
  win32RootlessWindowPtr pRLWin = NULL;
  win32RootlessWindowPtr pRLWinSib = NULL;
  DWORD dwCurrentProcessID = GetCurrentProcessId ();
  DWORD dwWindowProcessID = 0;
  XID vlist[2];

#if CYGMULTIWINDOW_DEBUG && FALSE
  winDebug ("winMWExtWMReorderWindows\n");
#endif

  pScreenPriv->fRestacking = TRUE;

  if (pScreenPriv->fWindowOrderChanged)
    {
#if CYGMULTIWINDOW_DEBUG
      winDebug ("winMWExtWMReorderWindows - Need to restack\n");
#endif
      hwnd = GetTopWindow (NULL);

      while (hwnd)
	{
	  GetWindowThreadProcessId (hwnd, &dwWindowProcessID);

	  if ((dwWindowProcessID == dwCurrentProcessID)
	      && GetProp (hwnd, WIN_WINDOW_PROP))
	    {
	      pRLWinSib = pRLWin;
	      pRLWin = (win32RootlessWindowPtr)GetProp (hwnd, WIN_WINDOW_PROP);
	      
	      if (pRLWinSib)
		{
		  vlist[0] = pRLWinSib->pFrame->win->drawable.id;
		  vlist[1] = Below;

		  ConfigureWindow (pRLWin->pFrame->win, CWSibling | CWStackMode,
				   vlist, wClient(pRLWin->pFrame->win));
		}
	      else
		{
		  /* 1st window - raise to the top */
		  vlist[0] = Above;

		  ConfigureWindow (pRLWin->pFrame->win, CWStackMode,
				   vlist, wClient(pRLWin->pFrame->win));
		}
	    }
	  hwnd = GetNextWindow (hwnd, GW_HWNDNEXT);
	}
    }

  pScreenPriv->fRestacking = FALSE;
  pScreenPriv->fWindowOrderChanged = FALSE;
}