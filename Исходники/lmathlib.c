static int math_ldexp (lua_State *L)
{
    lua_pushnumber(L, ldexp(luaL_checknumber(L, 1), luaL_checkint(L, 2)));
    return 1;
}