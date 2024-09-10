BOOL create_confirm_Internal (HWND hwnd,
    SQLPOINTER dsn,
    SQLPOINTER text,
    SQLCHAR waMode)
{
  EventTypeSpec controlSpec = { kEventClassControl, kEventControlHit };
  RgnHandle cursorRgn = NULL;
  ControlID controlID;
  ControlRef control;
  WindowRef wconfirm;
  TCONFIRM confirm_t;
  EventRecord event;
  IBNibRef nibRef;
  CFStringRef msg;
  OSStatus err;

  /* Search the bundle for a .nib file named 'odbcadmin'. */
  err =
      CreateNibReferenceWithCFBundle (CFBundleGetBundleWithIdentifier (CFSTR
	("org.iodbc.drvproxy")), CFSTR ("confirmation"), &nibRef);
  if (err == noErr)
    {
      /* Nib found ... so create the window */
      CreateWindowFromNib (nibRef, CFSTR ("Dialog"), &wconfirm);
      DisposeNibReference (nibRef);
      /* Set the title with the DSN name */
      if (dsn)
	{
          if (waMode == 'A')
            msg = CFStringCreateWithBytes (NULL, (unsigned char*)dsn, STRLEN(dsn), 
              kCFStringEncodingUTF8, false);
          else
            msg = convert_wchar_to_CFString((wchar_t*)dsn);
          SetWindowTitleWithCFString (wconfirm, msg);
          CFRelease(msg);
	}
      /* Install handlers for the finish button, the cancel */
      GETCONTROLBYID (controlID, CNTL_SIGNATURE, CONFYES_CNTL, wconfirm,
	  control);
      InstallEventHandler (GetControlEventTarget (control),
	  NewEventHandlerUPP (confirmadm_yes_clicked), 1, &controlSpec,
	  &confirm_t, NULL);
      GETCONTROLBYID (controlID, CNTL_SIGNATURE, CONFNO_CNTL, wconfirm,
	  control);
      InstallEventHandler (GetControlEventTarget (control),
	  NewEventHandlerUPP (confirmadm_no_clicked), 1, &controlSpec,
	  &confirm_t, NULL);
      /* Change the static field with the message */
      GETCONTROLBYID (controlID, CNTL_SIGNATURE, CONFTEXT_CNTL, wconfirm,
	  control);
      if (waMode == 'A')
        SetControlData (control, 0, kControlEditTextTextTag, STRLEN (text), text);
      else
        {
          msg = convert_wchar_to_CFString((wchar_t*)text);
          SetControlData (control, 0, kControlEditTextCFStringTag, sizeof(CFStringRef), &msg);
          CFRelease(msg);
        }
      DrawOneControl (control);
      confirm_t.yes_no = FALSE;
      confirm_t.mainwnd = wconfirm;
      /* Show the window and run the loop */
      ShowWindow (wconfirm);
      /* The main loop */
      while (confirm_t.mainwnd)
	WaitNextEvent (everyEvent, &event, 60L, cursorRgn);
    }
  else
    goto error;

  return confirm_t.yes_no;

error:
  fprintf (stderr, "Can't load Window. Err: %d\n", (int) err);
  return confirm_t.yes_no;
}