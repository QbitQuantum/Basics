static void setpath (lua_State *L, const char *fieldname, const wchar_t *envname1,
                                   const wchar_t *envname2, const wchar_t *def) {
  const wchar_t *path = _wgetenv(envname1);
  if (path == NULL)  /* no environment variable? */
    path = _wgetenv(envname2);  /* try alternative name */
  if (path == NULL || noenv(L))  /* no environment variable? */
    lua_pushlstring(L, (const char*)def, sizeof(wchar_t)*(1+wcslen(def)));  /* use default */
  else {
    /* replace ";;" by ";AUXMARK;" and then AUXMARK by default path */
    path = LF_Gsub(L, path, LUA_PATH_SEP LUA_PATH_SEP,
                            LUA_PATH_SEP AUXMARK LUA_PATH_SEP);
    LF_Gsub(L, path, AUXMARK, def);
    lua_remove(L, -2);
  }
  setprogdir(L);
  push_utf8_string(L, (const wchar_t*)lua_tostring(L, -1), -1);
  lua_remove(L, -2);
  lua_setfield(L, -2, fieldname);
}