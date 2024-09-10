static int
winprint_page_setup_command (ClientData cd, Tcl_Interp *interp, int argc,
			     char **argv)
{
  struct winprint_data *wd = (struct winprint_data *) cd;
  Tk_Window parent;
  int i, mode, ret;
  PAGESETUPDLG psd;

  parent = Tk_MainWindow (interp);

  for (i = 2; i < argc; i += 2)
    {
      if (i + 1 >= argc)
	{
	  Tcl_ResetResult (interp);
	  Tcl_AppendStringsToObj (Tcl_GetObjResult (interp),
				  "value for \"", argv[i], "\" missing",
				  (char *) NULL);
	  return TCL_ERROR;
	}

      if (strcmp (argv[i], "-parent") == 0)
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

  if (wd->page_setup != NULL)
    psd = *wd->page_setup;
  else
    {
      memset (&psd, 0, sizeof (PAGESETUPDLG));
      psd.lStructSize = sizeof (PAGESETUPDLG);
      psd.Flags = PSD_DEFAULTMINMARGINS;
    }

  if (Tk_WindowId (parent) == None)
    Tk_MakeWindowExist (parent);
  psd.hwndOwner = Tk_GetHWND (Tk_WindowId (parent));

  mode = Tcl_SetServiceMode (TCL_SERVICE_ALL);

  ret = PageSetupDlg (&psd);

  (void) Tcl_SetServiceMode (mode);

  if (! ret)
    {
      DWORD code;

      code = CommDlgExtendedError ();
      if (code == 0)
	{
	  /* The user pressed cancel.  */
	  return TCL_OK;
	}
      else
	{
	  char buf[20];

	  sprintf (buf, "0x%lx", (unsigned long) code);
	  Tcl_ResetResult (interp);
	  Tcl_AppendStringsToObj (Tcl_GetObjResult (interp),
				  "Windows common dialog error ", buf,
				  (char *) NULL);
	  return TCL_ERROR;
	}
    }

  if (wd->page_setup == NULL)
    wd->page_setup = (PAGESETUPDLG *) ckalloc (sizeof (PAGESETUPDLG));

  *wd->page_setup = psd;

  return TCL_OK;
}