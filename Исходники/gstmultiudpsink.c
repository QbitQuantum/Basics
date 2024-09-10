static gchar *
socket_last_error_message (void)
{
#ifdef G_OS_WIN32
  int errorcode = WSAGetLastError ();
  wchar_t buf[1024];
  DWORD result =
      FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL, errorcode, 0, (LPSTR) buf, sizeof (buf) / sizeof (wchar_t), NULL);
  if (FAILED (result)) {
    return g_strdup ("failed to get error message from system");
  } else {
    gchar *res =
        g_convert ((gchar *) buf, -1, "UTF-16", "UTF-8", NULL, NULL, NULL);
    /* g_convert() internally calls windows functions which reset the
       windows error code, so fix it up again like this */
    WSASetLastError (errorcode);
    return res;
  }
#else
  return g_strdup (g_strerror (errno));
#endif
}