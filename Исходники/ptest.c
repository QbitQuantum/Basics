static HWND
main_window (void)
{
  HWND retval;

  retval = GetTopWindow (NULL);
  return retval;
}