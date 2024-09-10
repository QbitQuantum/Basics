static gboolean
text_is_simple (const char *text,
		gint        length)
{
  gboolean retval;
  wchar_t *wtext;
  long wlen;

  wtext = (wchar_t *) g_utf8_to_utf16 (text, length, NULL, &wlen, NULL);
  if (wtext == NULL)
    return TRUE;

  retval = (ScriptIsComplex (wtext, wlen, SIC_COMPLEX) == S_FALSE);

  g_free (wtext);

#ifdef BASIC_WIN32_DEBUGGING
  if (pango_win32_debug)
    g_print ("text_is_simple: %.*s (%ld wchar_t): %s\n",
	     MIN (length, 10), text, wlen, retval ? "YES" : "NO");
#endif

  return retval;
}