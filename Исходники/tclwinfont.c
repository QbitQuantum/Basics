static int
win_choose_font (ClientData cd, Tcl_Interp *interp, int argc, CONST84 char **argv)
{
  CONST84 char *deffont;
  Tk_Window parent;
  int i, oldMode;
  CHOOSEFONTA cf;
  LOGFONTA lf;
  HDC hdc;
  HFONT hfont;
  char facebuf[LF_FACESIZE];
  TEXTMETRIC tm;
  int pointsize;
  char *s;
  Tcl_DString resultStr;             /* used to translate result in UTF8 in Tcl/Tk8.1 */
  deffont = NULL;
  parent = Tk_MainWindow (interp);

  for (i = 1; i < argc; i += 2)
    {
      if (i + 1 >= argc)
	{
	  Tcl_ResetResult (interp);
	  Tcl_AppendStringsToObj (Tcl_GetObjResult (interp),
				  "value for \"", argv[i], "\" missing",
				  (char *) NULL);
	  return TCL_ERROR;
	}

      if (strcmp (argv[i], "-default") == 0)
	deffont = argv[i + 1];
      else if (strcmp (argv[i], "-parent") == 0)
	{
	  parent = Tk_NameToWindow (interp, argv[i + 1],
				    Tk_MainWindow (interp));
	  if (parent == NULL)
	    return TCL_ERROR;
	}
      else
	{
	  Tcl_ResetResult (interp);
	  Tcl_AppendStringsToObj (Tcl_GetObjResult (interp),
				  "unknown option \"", argv[i], "\"",
				  (char *) NULL);
	  return TCL_ERROR;
	}
    }

  memset (&cf, 0, sizeof (CHOOSEFONT));
  cf.lStructSize = sizeof (CHOOSEFONT);

  if (Tk_WindowId (parent) == None)
    Tk_MakeWindowExist (parent);
  cf.hwndOwner = Tk_GetHWND (Tk_WindowId (parent));

  cf.lpLogFont = &lf;
  cf.Flags = CF_SCREENFONTS | CF_FORCEFONTEXIST;

  memset (&lf, 0, sizeof (LOGFONT));

  if (deffont != NULL)
    {
      Tk_Font tkfont;
      const TkFontAttributes *fa;

      tkfont = Tk_GetFont (interp, parent, deffont);
      if (tkfont == NULL)
	return TCL_ERROR;

      cf.Flags |= CF_INITTOLOGFONTSTRUCT;

      /* In order to initialize LOGFONT, we need to extract the real
	 font attributes from the Tk internal font information.  */
      fa = &((TkFont *) tkfont)->fa;

      /* This code is taken from TkpGetFontFromAttributes.  It
         converts a TkFontAttributes structure into a LOGFONT
         structure.  */
#if (TCL_MAJOR_VERSION >= 8) && (TCL_MINOR_VERSION >= 1)
      lf.lfHeight = - fa->size;
#else
      lf.lfHeight = - fa->pointsize;
#endif
      if (lf.lfHeight < 0)
	lf.lfHeight = MulDiv (lf.lfHeight,
			      254 * WidthOfScreen (Tk_Screen (parent)),
			      720 * WidthMMOfScreen (Tk_Screen (parent)));
      lf.lfWeight = fa->weight == TK_FW_NORMAL ? FW_NORMAL : FW_BOLD;
      lf.lfItalic = fa->slant;
      lf.lfUnderline = fa->underline;
      lf.lfStrikeOut = fa->overstrike;
      lf.lfCharSet = DEFAULT_CHARSET;
      lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
      lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
      lf.lfQuality = DEFAULT_QUALITY;
      lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
      if (fa->family == NULL)
	lf.lfFaceName[0] = '\0';
      else
	strncpy (lf.lfFaceName, fa->family, sizeof (lf.lfFaceName));

      Tk_FreeFont (tkfont);
    }

  oldMode = Tcl_SetServiceMode(TCL_SERVICE_ALL);
  if (!ChooseFontA (&cf))
    {
      DWORD code;

      code = CommDlgExtendedError ();
      if (code == 0)
	{
	  /* The user pressed cancel.  */
	  Tcl_ResetResult (interp);
	  return TCL_OK;
	}
      else
	{
	  char buf[200];

	  sprintf (buf, "Windows common dialog error 0x%lx", (unsigned long) code);
	  Tcl_ResetResult (interp);
          #if (TCL_MAJOR_VERSION >= 8) && (TCL_MINOR_VERSION >= 1)
            Tcl_ExternalToUtfDString(NULL, buf, -1, &resultStr);
          #else
            Tcl_InitDString(&resultStr);
            Tcl_DStingAppend(&resultStr, buf, -1);
          #endif
	  Tcl_AppendStringsToObj (Tcl_GetObjResult (interp),
				  Tcl_DStringValue(&resultStr),
				  (char *) NULL);
          Tcl_DStringFree(&resultStr);
	  return TCL_ERROR;
	}
    }
  Tcl_SetServiceMode(oldMode);
  /* We now have a LOGFONT structure.  We store it into a device
     context, and then extract enough information to build a Tk font
     specification.  With luck, when Tk interprets the font
     specification it will wind up with the font that the user expects
     to see.  Some of this code is taken from AllocFont.  */

  hfont = CreateFontIndirectA (&lf);
  if (hfont == NULL)
    {
      /* This should be impossible.  */
      #if (TCL_MAJOR_VERSION >= 8) && (TCL_MINOR_VERSION >= 1)
        Tcl_ExternalToUtfDString(NULL, "CreateFontIndirect failed on chosen font", -1, &resultStr);
      #else
        Tcl_InitDString(&resultStr);
        Tcl_DStingAppend(&resultStr, "CreateFontIndirect failed on chosen font", -1);
      #endif
      Tcl_SetResult (interp, Tcl_DStringValue(&resultStr), TCL_STATIC);
      Tcl_DStringFree(&resultStr);
      return TCL_ERROR;
    }

  hdc = GetDC (cf.hwndOwner);
  hfont = SelectObject (hdc, hfont);
  GetTextFaceA (hdc, sizeof (facebuf), facebuf);
  GetTextMetrics (hdc, &tm);

  Tcl_ResetResult (interp);

#if (TCL_MAJOR_VERSION >= 8) && (TCL_MINOR_VERSION >= 1)
  Tcl_ExternalToUtfDString(NULL, facebuf, -1, &resultStr);
#else
  Tcl_InitDString(&resultStr);
  Tcl_DStingAppend(&resultStr,facebuf,-1);
#endif

  if (Tcl_ListObjAppendElement (interp, Tcl_GetObjResult (interp),
				Tcl_NewStringObj (Tcl_DStringValue(&resultStr), -1)) != TCL_OK) {
    Tcl_DStringFree(&resultStr);
    return TCL_ERROR;
  }

  Tcl_DStringFree(&resultStr);

  pointsize = MulDiv (tm.tmHeight - tm.tmInternalLeading,
		      720 * WidthMMOfScreen (Tk_Screen (parent)),
		      254 * WidthOfScreen (Tk_Screen (parent)));

  if (Tcl_ListObjAppendElement (interp, Tcl_GetObjResult (interp),
				Tcl_NewIntObj (pointsize)) != TCL_OK) {
     return TCL_ERROR;
  }

   if (tm.tmWeight > FW_MEDIUM)
    s = "bold";
  else
    s = "normal";

#if (TCL_MAJOR_VERSION >= 8) && (TCL_MINOR_VERSION >= 1)
  Tcl_ExternalToUtfDString(NULL, s, -1, &resultStr);
#else
  Tcl_InitDString(&resultStr);
  Tcl_DStingAppend(&resultStr, s, -1);
#endif

  if (Tcl_ListObjAppendElement (interp, Tcl_GetObjResult (interp),
				Tcl_NewStringObj (Tcl_DStringValue(&resultStr), -1)) != TCL_OK) {
    Tcl_DStringFree(&resultStr);
    return TCL_ERROR;
  }

  Tcl_DStringFree(&resultStr);

  if (tm.tmItalic)
    s = "italic";
  else
    s = "roman";

#if (TCL_MAJOR_VERSION >= 8) && (TCL_MINOR_VERSION >= 1)
  Tcl_ExternalToUtfDString(NULL, s, -1, &resultStr);
#else
  Tcl_InitDString(&resultStr);
  Tcl_DStingAppend(&resultStr, s, -1);
#endif

  if (Tcl_ListObjAppendElement (interp, Tcl_GetObjResult (interp),
				Tcl_NewStringObj (Tcl_DStringValue(&resultStr), -1)) != TCL_OK) {
    Tcl_DStringFree(&resultStr);
    return TCL_ERROR;
  }
  Tcl_DStringFree(&resultStr);

  if (tm.tmUnderlined)
    {
      #if (TCL_MAJOR_VERSION >= 8) && (TCL_MINOR_VERSION >= 1)
        Tcl_ExternalToUtfDString(NULL, "underline", -1, &resultStr);
      #else
        Tcl_InitDString(&resultStr);
        Tcl_DStingAppend(&resultStr,"underline",-1);
      #endif
      if (Tcl_ListObjAppendElement (interp, Tcl_GetObjResult (interp),
				    Tcl_NewStringObj (Tcl_DStringValue(&resultStr), -1))
	  != TCL_OK) {
        Tcl_DStringFree(&resultStr);
	return TCL_ERROR;
      }
      Tcl_DStringFree(&resultStr);
    }

  if (tm.tmStruckOut)
    {
      #if (TCL_MAJOR_VERSION >= 8) && (TCL_MINOR_VERSION >= 1)
        Tcl_ExternalToUtfDString(NULL, "overstrike", -1, &resultStr);
      #else
        Tcl_InitDString(&resultStr);
        Tcl_DStingAppend(&resultStr, "overstrike", -1);
      #endif
      if (Tcl_ListObjAppendElement (interp, Tcl_GetObjResult (interp),
				    Tcl_NewStringObj (Tcl_DStringValue(&resultStr), -1))
	  != TCL_OK) {
        Tcl_DStringFree(&resultStr);
	return TCL_ERROR;
      }
      Tcl_DStringFree(&resultStr);
    }

  hfont = SelectObject (hdc, hfont);
  ReleaseDC (cf.hwndOwner, hdc);
  DeleteObject (hfont);

  return TCL_OK;
}