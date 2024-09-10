static int io_remove (lua_State *L) {
  return pushresult(L, remove(luaL_check_string(L, 1)) == 0);
}