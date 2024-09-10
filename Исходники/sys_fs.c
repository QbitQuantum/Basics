/*
 * Arguments: existing_path (string), new_path (string)
 * Returns: [boolean]
 */
static int
sys_rename (lua_State *L)
{
  const char *old = luaL_checkstring(L, 1);
  const char *new = luaL_checkstring(L, 2);
  int res;

#ifndef _WIN32
  sys_vm_leave(L);
  res = rename(old, new);
  sys_vm_enter(L);
#else
  {
    void *os_old = utf8_to_filename(old);
    void *os_new = utf8_to_filename(new);
    if (!os_old || !os_new) {
      free(os_old);
      free(os_new);
      return sys_seterror(L, ERROR_NOT_ENOUGH_MEMORY);
    }

    sys_vm_leave(L);
    res = is_WinNT
     ? !MoveFileW(os_old, os_new)
     : !MoveFileA(os_old, os_new);

    free(os_old);
    free(os_new);
    sys_vm_enter(L);
  }
#endif

  if (!res) {
    lua_pushboolean(L, 1);
    return 1;
  }
  return sys_seterror(L, 0);
}