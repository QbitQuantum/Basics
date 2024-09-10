static void
gui_unique_win32_init (Gimp *gimp)
{
  WNDCLASSW wc;

  g_return_if_fail (GIMP_IS_GIMP (gimp));
  g_return_if_fail (unique_gimp == NULL);

  unique_gimp = gimp;

  /* register window class for proxy window */
  memset (&wc, 0, sizeof (wc));

  wc.hInstance     = GetModuleHandle (NULL);
  wc.lpfnWndProc   = gui_unique_win32_message_handler;
  wc.lpszClassName = GIMP_UNIQUE_WIN32_WINDOW_CLASS;

  RegisterClassW (&wc);

  proxy_window = CreateWindowExW (0,
                                  GIMP_UNIQUE_WIN32_WINDOW_CLASS,
                                  GIMP_UNIQUE_WIN32_WINDOW_NAME,
                                  WS_POPUP, 0, 0, 1, 1, NULL, NULL, wc.hInstance, NULL);
}