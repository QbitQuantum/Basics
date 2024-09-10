/*
  spawnvp by file system codepage
*/
int
fsyscp_spawnvp (int mode, const char *command, const char* const *argv)
{
    int ret;
    wchar_t *commandw, **argvw, **pw;
    int i;
    const char* const *p;

    assert(command && argv);
    for (i = 0, p = argv; *p; p++)
      i++;
    argvw = xcalloc (i + 3, sizeof (wchar_t *));
    commandw = get_wstring_from_fsyscp(command, commandw=NULL);
    p = argv;
    pw = argvw;
    while (*p) {
      *pw = get_wstring_from_fsyscp(*p, *pw=NULL);
      p++;
      pw++;
    }
    *pw = NULL;
    ret = _wspawnvp (mode, (const wchar_t *)commandw, (const wchar_t* const*) argvw);
    if(commandw) free(commandw);
    if (argvw) {
      pw = argvw;
      while (*pw) {
	free (*pw);
	pw++;
      }
      free (argvw);
    }

    return ret;
}