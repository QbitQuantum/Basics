/*********************************************************************
 *		_searchenv_s (MSVCRT.@)
 */
int _tsearchenv_s(const _TCHAR* file, const _TCHAR* env, _TCHAR *buf, size_t count)
{
  _TCHAR *envVal, *penv;
  _TCHAR curPath[MAX_PATH];

  if (!MSVCRT_CHECK_PMT(file != NULL) || !MSVCRT_CHECK_PMT(buf != NULL) ||
      !MSVCRT_CHECK_PMT(count > 0))
  {
      *_errno() = EINVAL;
      return EINVAL;
  }

  *buf = '\0';

  /* Try CWD first */
  if (GetFileAttributes( file ) != INVALID_FILE_ATTRIBUTES)
  {
    GetFullPathName( file, MAX_PATH, buf, NULL );
    _dosmaperr(GetLastError());
    return 0;
  }

  /* Search given environment variable */
  envVal = _tgetenv(env);
  if (!envVal)
  {
    _set_errno(ENOENT);
    return ENOENT;
  }

  penv = envVal;

  do
  {
    _TCHAR *end = penv;

    while(*end && *end != ';') end++; /* Find end of next path */
    if (penv == end || !*penv)
    {
      _set_errno(ENOENT);
      return ENOENT;
    }
    memcpy(curPath, penv, (end - penv) * sizeof(_TCHAR));
    if (curPath[end - penv] != '/' && curPath[end - penv] != '\\')
    {
      curPath[end - penv] = '\\';
      curPath[end - penv + 1] = '\0';
    }
    else
      curPath[end - penv] = '\0';

    _tcscat(curPath, file);
    if (GetFileAttributes( curPath ) != INVALID_FILE_ATTRIBUTES)
    {
      if (_tcslen(curPath) + 1 > count)
      {
          MSVCRT_INVALID_PMT("buf[count] is too small", ERANGE);
          return ERANGE;
      }
      _tcscpy(buf, curPath);
      return 0;
    }
    penv = *end ? end + 1 : end;
  } while(1);

}