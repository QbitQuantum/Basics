int
w32_window_app (void)
{
  static int window_app = -1;
  char szTitle[MAX_PATH];

  if (window_app < 0)
    {
      /* Checking for STDOUT does not work; it's a valid handle also in
         nonconsole apps.  Testing for the console title seems to work. */
      window_app = (GetConsoleTitleA (szTitle, MAX_PATH) == 0);
      if (window_app)
        InitCommonControls ();
    }

  return window_app;
}