bool
MakeNTEmacsClientCommandLine (/*[out]*/ string &	program,
			      /*[out]*/ string &	arguments)
{
  PathName pathEmacs;
  if (! LocateNTEmacs(pathEmacs, "gnuclientw.exe"))
  {
    wchar_t szEmacs[_MAX_PATH];
    wchar_t * lpszFileName;
    if (! SearchPathW(0, L"gnuclientw.exe", 0, _MAX_PATH, szEmacs, &lpszFileName))
    {
      return (false);
    }
    pathEmacs = szEmacs;
  }
  program = pathEmacs.Get();
  arguments = "-F +%l \"%f\"";
  return (true);
}