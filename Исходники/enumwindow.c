int winapi_GetClassNameW(lua_State* L)
{
  HWND hwnd;
  size_t size;
  char buffer[2048];
  LUASTACK_SET(L);

  hwnd = lua_toWindow(L, 1);

  size = GetClassNameW(hwnd, (LPWSTR)&buffer, sizeof(buffer)/sizeof(WCHAR));
  if (size)
  {
    lua_pushlstring(L, buffer, size*sizeof(WCHAR));

    LUASTACK_CLEAN(L, 1);
    return 1;
  }

  LUASTACK_CLEAN(L, 0);
  return 0;
}