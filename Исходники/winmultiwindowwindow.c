void
winReorderWindowsMultiWindow (void)
{
  HWND hwnd = NULL;
  WindowPtr pWin = NULL;
  WindowPtr pWinSib = NULL;
  XID vlist[2];
  static Bool fRestacking = FALSE; /* Avoid recusive calls to this function */
  DWORD dwCurrentProcessID = GetCurrentProcessId ();
  DWORD dwWindowProcessID = 0;

#if CYGMULTIWINDOW_DEBUG || CYGWINDOWING_DEBUG
  winTrace ("winReorderWindowsMultiWindow\n");
#endif

  if (fRestacking)
    {
      /* It is a recusive call so immediately exit */
#if CYGWINDOWING_DEBUG
      ErrorF ("winReorderWindowsMultiWindow - "
	      "exit because fRestacking == TRUE\n");
#endif
      return;
    }
  fRestacking = TRUE;

  /* Loop through top level Window windows, descending in Z order */
  for ( hwnd = GetTopWindow (NULL);
	hwnd;
	hwnd = GetNextWindow (hwnd, GW_HWNDNEXT) )
    {
      /* Don't take care of other Cygwin/X process's windows */
      GetWindowThreadProcessId (hwnd, &dwWindowProcessID);

      if ( GetProp (hwnd, WIN_WINDOW_PROP)
	   && (dwWindowProcessID == dwCurrentProcessID)
	   && !IsIconic (hwnd) ) /* ignore minimized windows */
	{
	  pWinSib = pWin;
	  pWin = GetProp (hwnd, WIN_WINDOW_PROP);
	      
	  if (!pWinSib)
	    { /* 1st window - raise to the top */
	      vlist[0] = Above;
		  
	      ConfigureWindow (pWin, CWStackMode, vlist, wClient(pWin));
	    }
	  else
	    { /* 2nd or deeper windows - just below the previous one */
	      vlist[0] = winGetWindowID (pWinSib);
	      vlist[1] = Below;

	      ConfigureWindow (pWin, CWSibling | CWStackMode,
			       vlist, wClient(pWin));
	    }
	}
    }

  fRestacking = FALSE;
}