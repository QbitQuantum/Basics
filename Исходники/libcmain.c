/* Allow apps which don't have a main work, as long as they define WinMain */
int
main ()
{
  HMODULE x = GetModuleHandleA(0);
  char *s = GetCommandLineA ();
  STARTUPINFO si;

  /* GetCommandLineA returns the entire command line including the
     program name, but WinMain is defined to accept the command
     line without the program name.  */
  while (*s != ' ' && *s != '\0')
    ++s;
  while (*s == ' ')
    ++s;

  GetStartupInfo (&si);

  return WinMain (x, 0, s,
		  ((si.dwFlags & STARTF_USESHOWWINDOW) != 0
		   ? si.wShowWindow
		   : SW_SHOWNORMAL));
}