LUA_API lua_State *lua_newstate(lua_Alloc f, void *ud)
{
  UNUSED(f); UNUSED(ud);
  fputs("Must use luaL_newstate() for 64 bit target\n", stderr);
  return NULL;
}