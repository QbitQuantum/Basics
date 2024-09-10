void
InitOutput (ScreenInfo *screenInfo, int argc, char *argv[])
{
  int		i;

  /* Log the command line */
  winLogCommandLine (argc, argv);

#if CYGDEBUG
  winDebug ("InitOutput\n");
#endif

  /* Validate command-line arguments */
  if (serverGeneration == 1 && !winValidateArgs ())
    {
      FatalError ("InitOutput - Invalid command-line arguments found.  "
		  "Exiting.\n");
    }

  /* Check for duplicate invocation on same display number.*/
  if (serverGeneration == 1 && !winCheckDisplayNumber ())
    {
      if (g_fSilentDupError)
        g_fSilentFatalError = TRUE;  
      FatalError ("InitOutput - Duplicate invocation on display "
		  "number: %s.  Exiting.\n", display);
    }

#ifdef XWIN_XF86CONFIG
  /* Try to read the xorg.conf-style configuration file */
  if (!winReadConfigfile ())
    winErrorFVerb (1, "InitOutput - Error reading config file\n");
#else
  winMsg(X_INFO, "xorg.conf is not supported\n");
  winMsg(X_INFO, "See http://x.cygwin.com/docs/faq/cygwin-x-faq.html "
         "for more information\n");
  winConfigFiles ();
#endif

  /* Load preferences from XWinrc file */
  LoadPreferences();

  /* Setup global screen info parameters */
  screenInfo->imageByteOrder = IMAGE_BYTE_ORDER;
  screenInfo->bitmapScanlinePad = BITMAP_SCANLINE_PAD;
  screenInfo->bitmapScanlineUnit = BITMAP_SCANLINE_UNIT;
  screenInfo->bitmapBitOrder = BITMAP_BIT_ORDER;
  screenInfo->numPixmapFormats = NUMFORMATS;
  
  /* Describe how we want common pixmap formats padded */
  for (i = 0; i < NUMFORMATS; i++)
    {
      screenInfo->formats[i] = g_PixmapFormats[i];
    }

  /* Load pointers to DirectDraw functions */
  winGetDDProcAddresses ();
  
  /* Detect supported engines */
  winDetectSupportedEngines ();

  /* Load common controls library */
  g_hmodCommonControls = LoadLibraryEx ("comctl32.dll", NULL, 0);

  /* Load TrackMouseEvent function pointer */  
  g_fpTrackMouseEvent = GetProcAddress (g_hmodCommonControls,
					 "_TrackMouseEvent");
  if (g_fpTrackMouseEvent == NULL)
    {
      winErrorFVerb (1, "InitOutput - Could not get pointer to function\n"
	      "\t_TrackMouseEvent in comctl32.dll.  Try installing\n"
	      "\tInternet Explorer 3.0 or greater if you have not\n"
	      "\talready.\n");

      /* Free the library since we won't need it */
      FreeLibrary (g_hmodCommonControls);
      g_hmodCommonControls = NULL;

      /* Set function pointer to point to no operation function */
      g_fpTrackMouseEvent = (FARPROC) (void (*)(void))NoopDDA;
    }

  /* Store the instance handle */
  g_hInstance = GetModuleHandle (NULL);

  /* Initialize each screen */
  for (i = 0; i < g_iNumScreens; ++i)
    {
      /* Initialize the screen */
      if (-1 == AddScreen (winScreenInit, argc, argv))
	{
	  FatalError ("InitOutput - Couldn't add screen %d", i);
	}
    }

#if defined(XWIN_CLIPBOARD) || defined(XWIN_MULTIWINDOW)

  /* Generate a cookie used by internal clients for authorization */
  if (g_fXdmcpEnabled || g_fAuthEnabled)
    winGenerateAuthorization ();

  /* Perform some one time initialization */
  if (1 == serverGeneration)
    {
      /*
       * setlocale applies to all threads in the current process.
       * Apply locale specified in LANG environment variable.
       */
      setlocale (LC_ALL, "");
    }
#endif

#if CYGDEBUG || YES
  winDebug ("InitOutput - Returning.\n");
#endif
}