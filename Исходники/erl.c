int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		    PWSTR szCmdLine, int iCmdShow)
{
    int argc = __argc;
    wchar_t **argv = __wargv;
#else
#define WERL 0
int wmain(int argc, wchar_t **argv)
{
#endif
  HANDLE erlexec_handle; /* Instance */
  ErlexecFunction *win_erlexec;
  wchar_t *path = malloc(100*sizeof(wchar_t));
  wchar_t *npath;
  int pathlen;
  char ** utf8argv;
  int i, len;

  get_parameters();

  if ((pathlen = GetEnvironmentVariableW(L"PATH",path,100)) == 0) {
    error("No PATH variable (!)");
  } else if (pathlen > 100) {
    path = realloc(path,pathlen*sizeof(wchar_t));
    GetEnvironmentVariableW(L"PATH",path,pathlen);
  }
  pathlen = (wcslen(path) + wcslen(erlexec_dir) + 2);
  npath = (wchar_t *) malloc(pathlen*sizeof(wchar_t));
  swprintf(npath,pathlen,L"%s;%s",erlexec_dir,path);
  SetEnvironmentVariableW(L"PATH",npath);

  if ((erlexec_handle = LoadLibraryW(erlexec_name)) == NULL) {
    error("Could not load module %S.",erlexec_name);
  }

  if ((win_erlexec = (ErlexecFunction *) 
       GetProcAddress(erlexec_handle,"win_erlexec")) == NULL) {
    error("Could not find entry point \"win_erlexec\" in %S.", erlexec_name);
  }

  /* Convert argv to utf8 */
  utf8argv = malloc((argc+1) * sizeof(char*));
  for (i=0; i<argc; i++) {
      len = WideCharToMultiByte(CP_UTF8, 0, argv[i], -1, NULL, 0, NULL, NULL);
      utf8argv[i] = malloc(len*sizeof(char));
      WideCharToMultiByte(CP_UTF8, 0, argv[i], -1, utf8argv[i], len, NULL, NULL);
  }
  utf8argv[argc] = NULL;

#ifdef HARDDEBUG
	{
	    wchar_t tempbuf[2048] = L"";
	    wchar_t *sbuf;
	    int i;
	    sbuf=tempbuf;
	    sbuf += swprintf(sbuf, 2048, L"utf16: %d\n", argc);
	    for (i = 0; i < argc; ++i) {
		sbuf += swprintf(sbuf, 2048, L"|%s|", argv[i]);
	    };
	    sbuf += swprintf(sbuf, 2048, L"\nutf8: \n");
	    for (i = 0; i < argc; ++i) {
		sbuf += swprintf(sbuf, 2048, L"|%S|", utf8argv[i]);
	    };
	    MessageBoxW(NULL, tempbuf, L"erl_exec args", MB_OK|MB_ICONERROR);
	}
#endif

  return (*win_erlexec)(argc,utf8argv,erlexec_handle,WERL);
  
} 