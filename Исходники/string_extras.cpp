int _vscprintf(const char *format, va_list argptr)
{
  FILE* f = NULL;
  int result = 0; 
  WCHAR path [MAX_PATH];
  WCHAR wtmpfile [MAX_PATH];
  char atmpfile [MAX_PATH];

  GetTempPath(MAX_PATH,path);
  if (GetTempFileNameW(path,L"tmp",0,wtmpfile) == 0)
    return NULL;
  wcstombs(atmpfile,wtmpfile,MAX_PATH);
  f = fopen (atmpfile,"w+b");
  if (!f)
  {
    errno = EINVAL;
    return -1;
  }
  vfprintf(f, format, argptr);
  fflush(f);
  fseek(f, 0, SEEK_END);
  result = ftell(f);
  fclose(f);
  DeleteFileW(wtmpfile);
  return result;
}