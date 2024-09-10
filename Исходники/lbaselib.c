/*
** If your system does not support `stderr', redefine this function, or
** redefine _ERRORMESSAGE so that it won't need _ALERT.
*/
static int luaB__ALERT (lua_State *L) {
  fputs(luaL_check_string(L, 1), stderr);
  return 0;
}