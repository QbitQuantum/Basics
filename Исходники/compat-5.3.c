COMPAT53_API int luaL_loadfilex (lua_State *L, const char *filename, const char *mode) {
  compat53_LoadF lf;
  int status, readstatus;
  int c;
  int fnameindex = lua_gettop(L) + 1;  /* index of filename on the stack */
  if (filename == NULL) {
    lua_pushliteral(L, "=stdin");
    lf.f = stdin;
  }
  else {
    lua_pushfstring(L, "@%s", filename);
#if defined(_MSC_VER)
    /* This code is here to stop a deprecation error that stops builds
     * if a certain macro is defined. While normally not caring would
     * be best, some header-only libraries and builds can't afford to
     * dictate this to the user. A quick check shows that fopen_s this
     * goes back to VS 2005, and _fsopen goes back to VS 2003 .NET,
     * possibly even before that so we don't need to do any version
     * number checks, since this has been there since forever.
     */

    /* TO USER: if you want the behavior of typical fopen_s/fopen,
     * which does lock the file on VC++, define the macro used below to 0
    */
#if COMPAT53_FOPEN_NO_LOCK
    lf.f = _fsopen(filename, "r", _SH_DENYNO); /* do not lock the file in any way */
    if (lf.f == NULL)
      return compat53_errfile(L, "open", fnameindex);
#else /* use default locking version */
    if (fopen_s(&lf.f, filename, "r") != 0)
      return compat53_errfile(L, "open", fnameindex);
#endif /* Locking vs. No-locking fopen variants */
#else
    lf.f = fopen(filename, "r"); /* default stdlib doesn't forcefully lock files here */
    if (lf.f == NULL) return compat53_errfile(L, "open", fnameindex);
#endif
  }
  if (compat53_skipcomment(&lf, &c))  /* read initial portion */
    lf.buff[lf.n++] = '\n';  /* add line to correct line numbers */
  if (c == LUA_SIGNATURE[0] && filename) {  /* binary file? */
#if defined(_MSC_VER)
    if (freopen_s(&lf.f, filename, "rb", lf.f) != 0)
      return compat53_errfile(L, "reopen", fnameindex);
#else
    lf.f = freopen(filename, "rb", lf.f);  /* reopen in binary mode */
    if (lf.f == NULL) return compat53_errfile(L, "reopen", fnameindex);
#endif
    compat53_skipcomment(&lf, &c);  /* re-read initial portion */
  }
  if (c != EOF)
    lf.buff[lf.n++] = c;  /* 'c' is the first character of the stream */
  status = lua_load(L, &compat53_getF, &lf, lua_tostring(L, -1), mode);
  readstatus = ferror(lf.f);
  if (filename) fclose(lf.f);  /* close file (even in case of errors) */
  if (readstatus) {
    lua_settop(L, fnameindex);  /* ignore results from 'lua_load' */
    return compat53_errfile(L, "read", fnameindex);
  }
  lua_remove(L, fnameindex);
  return status;
}