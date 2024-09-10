void tUtil::ShowHelp(const char *filename, unsigned long context)
{
  // filename must have at least the extension
  if(!filename || strlen(filename) < 5)
    return;

  const char* extension = &filename[strlen(filename) - 4];

  if(_stricmp(extension, ".chm") == 0)
  {
    char context_param[50];
  
    if(context != 0)
      sprintf(context_param, "-mapid %d", context);
    else
      context_param[0] = '\0';
#if !defined(__WINE__) || defined(__MSVCRT__)
    _spawnlp(_P_NOWAIT, "hh.exe", "hh.exe", context_param, filename, NULL);
#else
    MessageBox(NULL, "FIX - not implemented - _spawnlp", "LuaCOM", MB_ICONEXCLAMATION);
    #warning FIX - not implemented - _spawnlp
#endif
  }
  else if(_stricmp(extension, ".hlp") == 0)
  {
    if(context != 0)
      WinHelp(NULL, filename, HELP_CONTEXT, context);
    else
      WinHelp(NULL, filename, HELP_FINDER, 0);
  }
}