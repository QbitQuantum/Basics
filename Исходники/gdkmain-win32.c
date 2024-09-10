void
_gdk_windowing_init (void)
{
  gchar buf[10];

#ifdef HAVE_WINTAB
  if (getenv ("GDK_IGNORE_WINTAB") != NULL)
    _gdk_input_ignore_wintab = TRUE;
  else if (getenv ("GDK_USE_WINTAB") != NULL)
    _gdk_input_ignore_wintab = FALSE;
#endif

  if (gdk_synchronize)
    GdiSetBatchLimit (1);

  _gdk_app_hmodule = GetModuleHandle (NULL);
  _gdk_display_hdc = CreateDC ("DISPLAY", NULL, NULL, NULL);
  _gdk_input_locale = GetKeyboardLayout (0);
  _gdk_input_locale_is_ime = ImmIsIME (_gdk_input_locale);
  GetLocaleInfo (MAKELCID (LOWORD (_gdk_input_locale), SORT_DEFAULT),
		 LOCALE_IDEFAULTANSICODEPAGE,
		 buf, sizeof (buf));
  _gdk_input_codepage = atoi (buf);
  GDK_NOTE (EVENTS, g_print ("input_locale:%p, codepage:%d\n",
			     _gdk_input_locale, _gdk_input_codepage));

  CoInitialize (NULL);

  _cf_rtf = RegisterClipboardFormat ("Rich Text Format");
  _cf_utf8_string = RegisterClipboardFormat ("UTF8_STRING");
  _cf_image_bmp = RegisterClipboardFormat ("image/bmp");

  _gdk_selection_property = gdk_atom_intern ("GDK_SELECTION", FALSE);
  _wm_transient_for = gdk_atom_intern ("WM_TRANSIENT_FOR", FALSE);
  _targets = gdk_atom_intern ("TARGETS", FALSE);
  _save_targets = gdk_atom_intern ("SAVE_TARGETS", FALSE);
  _utf8_string = gdk_atom_intern ("UTF8_STRING", FALSE);
  _text = gdk_atom_intern ("TEXT", FALSE);
  _compound_text = gdk_atom_intern ("COMPOUND_TEXT", FALSE);
  _text_uri_list = gdk_atom_intern ("text/uri-list", FALSE);
  _image_bmp = gdk_atom_intern ("image/bmp", FALSE);

  _local_dnd = gdk_atom_intern ("LocalDndSelection", FALSE);
  _gdk_win32_dropfiles = gdk_atom_intern ("DROPFILES_DND", FALSE);
  _gdk_ole2_dnd = gdk_atom_intern ("OLE2_DND", FALSE);

  _gdk_win32_selection_init ();
}