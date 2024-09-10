static int os_rename (lua_State *L) {
  const char *fromname = luaL_checkstring(L, 1);
  const char *toname = luaL_checkstring(L, 2);
#ifdef WIN32
  wchar_t wfromname[MAX_PATH+1];
  wchar_t wtoname[MAX_PATH+1];
  MultiByteToWideChar(CP_UTF8, 0, fromname, -1, wfromname, MAX_PATH+1);
  MultiByteToWideChar(CP_UTF8, 0, toname, -1, wtoname, MAX_PATH+1);
  return os_pushresult(L, _wrename(wfromname, wtoname) == 0, fromname);
#else
  // FIXME: non-win32 conversion to local filesystem encoding?
  return os_pushresult(L, rename(fromname, toname) == 0, fromname);
#endif
}