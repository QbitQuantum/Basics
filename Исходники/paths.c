static int 
lua_tmpname(lua_State *L)
{
#ifdef _WIN32
  char *tmp = _tempnam("c:/temp", "luatmp");
#else
  char *tmp = tempnam(NULL, "luatmp");
#endif
  if (tmp)
  {
    lua_pushstring(L, tmp);
    add_tmpname(L, tmp);
    free(tmp);
    return 1;
  }
  else
  {
    lua_pushnil(L);
    return 1;
  }
}