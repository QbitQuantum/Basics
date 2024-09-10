Bool
winCreateBoundingWindowWindowed (ScreenPtr pScreen)
{
  winScreenPriv(pScreen);
  winScreenInfo		*pScreenInfo = pScreenPriv->pScreenInfo;
  int			iWidth = pScreenInfo->dwUserWidth;
  int			iHeight = pScreenInfo->dwUserHeight;
  int                   iPosX;
  int                   iPosY;
  HWND			*phwnd = &pScreenPriv->hwndScreen;
  WNDCLASSEX		wc;
  RECT			rcClient, rcWorkArea;
  DWORD			dwWindowStyle;
  BOOL			fForceShowWindow = FALSE;
  char			szTitle[256];
  
  winDebug ("winCreateBoundingWindowWindowed - User w: %d h: %d\n",
	  (int) pScreenInfo->dwUserWidth, (int) pScreenInfo->dwUserHeight);
  winDebug ("winCreateBoundingWindowWindowed - Current w: %d h: %d\n",
	  (int) pScreenInfo->dwWidth, (int) pScreenInfo->dwHeight);

  /* Set the common window style flags */
  dwWindowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
  
  /* Decorated or undecorated window */
  if (pScreenInfo->fDecoration
#ifdef XWIN_MULTIWINDOWEXTWM
      && !pScreenInfo->fMWExtWM
#endif
      && !pScreenInfo->fRootless
#ifdef XWIN_MULTIWINDOW
      && !pScreenInfo->fMultiWindow
#endif
      )
    {
        /* Try to handle startup via run.exe. run.exe instructs Windows to 
         * hide all created windows. Detect this case and make sure the 
         * window is shown nevertheless */
        STARTUPINFO   startupInfo;
        GetStartupInfo(&startupInfo);
        if (startupInfo.dwFlags & STARTF_USESHOWWINDOW && 
                startupInfo.wShowWindow == SW_HIDE)
        {
          fForceShowWindow = TRUE;
        } 
        dwWindowStyle |= WS_CAPTION;
        if (pScreenInfo->iResizeMode != notAllowed)
            dwWindowStyle |= WS_THICKFRAME | WS_MAXIMIZEBOX;
    }
  else
    dwWindowStyle |= WS_POPUP;

  /* Setup our window class */
  wc.cbSize=sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = winWindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = g_hInstance;
  wc.hIcon = (HICON)LoadImage (g_hInstance, MAKEINTRESOURCE(IDI_XWIN), IMAGE_ICON,
		GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);
  wc.hCursor = 0;
  wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = WINDOW_CLASS;
  wc.hIconSm = (HICON)LoadImage (g_hInstance, MAKEINTRESOURCE(IDI_XWIN), IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTSIZE);
  RegisterClassEx (&wc);

  /* Get size of work area */
  winGetWorkArea (&rcWorkArea, pScreenInfo);

  /* Adjust for auto-hide taskbars */
  winAdjustForAutoHide (&rcWorkArea);

  /* Did the user specify a position? */
  if (pScreenInfo->fUserGavePosition)
    {
      iPosX = pScreenInfo->dwInitialX;
      iPosY = pScreenInfo->dwInitialY;
    }
  else
    {
      iPosX = rcWorkArea.left;
      iPosY = rcWorkArea.top;
    }

  /* Clean up the scrollbars flag, if necessary */
  if ((!pScreenInfo->fDecoration
#ifdef XWIN_MULTIWINDOWEXTWM
       || pScreenInfo->fMWExtWM
#endif
       || pScreenInfo->fRootless
#ifdef XWIN_MULTIWINDOW
       || pScreenInfo->fMultiWindow
#endif
       )
      && (pScreenInfo->iResizeMode == resizeWithScrollbars))
    {
      /* We cannot have scrollbars if we do not have a window border */
      pScreenInfo->iResizeMode = notAllowed;
    }

  /* Did the user specify a height and width? */
  if (pScreenInfo->fUserGaveHeightAndWidth)
    {
      /* User gave a desired height and width, try to accomodate */
#if CYGDEBUG
      winDebug ("winCreateBoundingWindowWindowed - User gave height "
	      "and width\n");
#endif
      
      /* Adjust the window width and height for borders and title bar */
      if (pScreenInfo->fDecoration
#ifdef XWIN_MULTIWINDOWEXTWM
	  && !pScreenInfo->fMWExtWM
#endif
	  && !pScreenInfo->fRootless
#ifdef XWIN_MULTIWINDOW
	  && !pScreenInfo->fMultiWindow
#endif
	  )
	{
#if CYGDEBUG
	  winDebug ("winCreateBoundingWindowWindowed - Window has decoration\n");
#endif

          /* Are we resizable */
          if (pScreenInfo->iResizeMode != notAllowed)
	    {
#if CYGDEBUG
	      winDebug ("winCreateBoundingWindowWindowed - Window is resizable\n");
#endif

	      iWidth += 2 * GetSystemMetrics (SM_CXSIZEFRAME);
	      iHeight += 2 * GetSystemMetrics (SM_CYSIZEFRAME) 
		+ GetSystemMetrics (SM_CYCAPTION);
	    }
	  else
	    {
#if CYGDEBUG
	      winDebug ("winCreateBoundingWindowWindowed - Window is not resizable\n");
#endif

	      iWidth += 2 * GetSystemMetrics (SM_CXFIXEDFRAME);
	      iHeight += 2 * GetSystemMetrics (SM_CYFIXEDFRAME) 
		+ GetSystemMetrics (SM_CYCAPTION);
	    }
	}
    }
  else
    {
      /* By default, we are creating a window that is as large as possible */
#if CYGDEBUG
      winDebug ("winCreateBoundingWindowWindowed - User did not give "
	      "height and width\n");
#endif
      /* Defaults are wrong if we have multiple monitors */
      if (pScreenInfo->fMultipleMonitors)
	{
	  iWidth = GetSystemMetrics (SM_CXVIRTUALSCREEN);
	  iHeight = GetSystemMetrics (SM_CYVIRTUALSCREEN);
	}
    }

  /* Make sure window is no bigger than work area */
  if (TRUE 
#ifdef XWIN_MULTIWINDOWEXTWM
       && !pScreenInfo->fMWExtWM
#endif
#ifdef XWIN_MULTIWINDOW
       && !pScreenInfo->fMultiWindow
#endif
     )
    {
      /* Trim window width to fit work area */
      if (iWidth > (rcWorkArea.right - rcWorkArea.left))
        iWidth = rcWorkArea.right - rcWorkArea.left;
  
      /* Trim window height to fit work area */
      if (iHeight >= (rcWorkArea.bottom - rcWorkArea.top))
        iHeight = rcWorkArea.bottom - rcWorkArea.top;
  
#if CYGDEBUG
      winDebug ("winCreateBoundingWindowWindowed - Adjusted width: %d "\
	      "height: %d\n",
    	  iWidth, iHeight);
#endif
    }

  /* Set display and screen-specific tooltip text */
  if (g_pszQueryHost != NULL)
    snprintf (szTitle,
	    sizeof (szTitle),
	    WINDOW_TITLE_XDMCP,
	    g_pszQueryHost,
	    display,
	    (int) pScreenInfo->dwScreen);
  else    
    snprintf (szTitle,
	    sizeof (szTitle),
	    WINDOW_TITLE,
	    display, 
	    (int) pScreenInfo->dwScreen);

  /* Create the window */
  *phwnd = CreateWindowExA (0,			/* Extended styles */
			    WINDOW_CLASS,	/* Class name */
			    szTitle,		/* Window name */
			    dwWindowStyle,
			    iPosX,	        /* Horizontal position */
			    iPosY,	        /* Vertical position */
			    iWidth,		/* Right edge */
			    iHeight,		/* Bottom edge */
			    (HWND) NULL,	/* No parent or owner window */
			    (HMENU) NULL,	/* No menu */
			    GetModuleHandle (NULL),/* Instance handle */
			    pScreenPriv);	/* ScreenPrivates */
  if (*phwnd == NULL)
    {
      ErrorF ("winCreateBoundingWindowWindowed - CreateWindowEx () failed\n");
      return FALSE;
    }

#if CYGDEBUG
  winDebug ("winCreateBoundingWindowWindowed - CreateWindowEx () returned\n");
#endif

  if (fForceShowWindow)
  {
      ErrorF("winCreateBoundingWindowWindowed - Setting normal windowstyle\n");
      ShowWindow(*phwnd, SW_SHOW);      
  }

  /* Get the client area coordinates */
  if (!GetClientRect (*phwnd, &rcClient))
    {
      ErrorF ("winCreateBoundingWindowWindowed - GetClientRect () "
	      "failed\n");
      return FALSE;
    }

  winDebug ("winCreateBoundingWindowWindowed - WindowClient "
	  "w %ld h %ld r %ld l %ld b %ld t %ld\n",
	  rcClient.right - rcClient.left,
	  rcClient.bottom - rcClient.top,
	  rcClient.right, rcClient.left,
	  rcClient.bottom, rcClient.top);
  
  /* We adjust the visual size if the user did not specify it */
  if (!((pScreenInfo->iResizeMode == resizeWithScrollbars) && pScreenInfo->fUserGaveHeightAndWidth))
    {
      /*
       * User did not give a height and width with scrollbars enabled,
       * so we will resize the underlying visual to be as large as
       * the initial view port (page size).  This way scrollbars will
       * not appear until the user shrinks the window, if they ever do.
       *
       * NOTE: We have to store the viewport size here because
       * the user may have an autohide taskbar, which would
       * cause the viewport size to be one less in one dimension
       * than the viewport size that we calculated by subtracting
       * the size of the borders and caption.
       */
      pScreenInfo->dwWidth = rcClient.right - rcClient.left;
      pScreenInfo->dwHeight = rcClient.bottom - rcClient.top;
    }

#if 0
  /*
   * NOTE: For the uninitiated, the page size is the number of pixels
   * that we can display in the x or y direction at a time and the
   * range is the total number of pixels in the x or y direction that we
   * have available to display.  In other words, the page size is the
   * size of the window area minus the space the caption, borders, and
   * scrollbars (if any) occupy, and the range is the size of the
   * underlying X visual.  Notice that, contrary to what some of the
   * MSDN Library arcticles lead you to believe, the windows
   * ``client area'' size does not include the scrollbars.  In other words,
   * the whole client area size that is reported to you is drawable by
   * you; you do not have to subtract the size of the scrollbars from
   * the client area size, and if you did it would result in the size
   * of the scrollbars being double counted.
   */

  /* Setup scrollbar page and range, if scrollbars are enabled */
  if (pScreenInfo->fScrollbars)
    {
      SCROLLINFO		si;
      
      /* Initialize the scrollbar info structure */
      si.cbSize = sizeof (si);
      si.fMask = SIF_RANGE | SIF_PAGE;
      si.nMin = 0;
      
      /* Setup the width range and page size */
      si.nMax = pScreenInfo->dwWidth - 1;
      si.nPage = rcClient.right - rcClient.left;
      winDebug ("winCreateBoundingWindowWindowed - HORZ nMax: %d nPage :%d\n",
	      si.nMax, si.nPage);
      SetScrollInfo (*phwnd, SB_HORZ, &si, TRUE);
      
      /* Setup the height range and page size */
      si.nMax = pScreenInfo->dwHeight - 1;
      si.nPage = rcClient.bottom - rcClient.top;
      winDebug ("winCreateBoundingWindowWindowed - VERT nMax: %d nPage :%d\n",
	      si.nMax, si.nPage);
      SetScrollInfo (*phwnd, SB_VERT, &si, TRUE);
    }
#endif

  /* Show the window */
  if (FALSE
#ifdef XWIN_MULTIWINDOWEXTWM
      || pScreenInfo->fMWExtWM
#endif
#ifdef XWIN_MULTIWINDOW
      || pScreenInfo->fMultiWindow
#endif
      )
    {
#if defined(XWIN_MULTIWINDOW) || defined(XWIN_MULTIWINDOWEXTWM)
      pScreenPriv->fRootWindowShown = FALSE;
#endif
      ShowWindow (*phwnd, SW_HIDE);
    }
  else
    ShowWindow (*phwnd, SW_SHOWNORMAL);
  if (!UpdateWindow (*phwnd))
    {
      ErrorF ("winCreateBoundingWindowWindowed - UpdateWindow () failed\n");
      return FALSE;
    }
  
  /* Attempt to bring our window to the top of the display */
  if (TRUE
#ifdef XWIN_MULTIWINDOWEXTWM
      && !pScreenInfo->fMWExtWM
#endif
      && !pScreenInfo->fRootless
#ifdef XWIN_MULTIWINDOW
      && !pScreenInfo->fMultiWindow
#endif
      )
    {
      if (!BringWindowToTop (*phwnd))
	{
	  ErrorF ("winCreateBoundingWindowWindowed - BringWindowToTop () "
		  "failed\n");
	  return FALSE;
	}
    }

#ifdef XWIN_NATIVEGDI
  /* Paint window background blue */
  if (pScreenInfo->dwEngine == WIN_SERVER_NATIVE_GDI)
    winPaintBackground (*phwnd, RGB (0x00, 0x00, 0xFF));
#endif

  winDebug ("winCreateBoundingWindowWindowed -  Returning\n");

  return TRUE;
}