static int l_surface_rect(lua_State *L)
{
    THRenderTarget* pCanvas = luaT_testuserdata<THRenderTarget>(L);
    if(pCanvas->fillRect(static_cast<uint32_t>(luaL_checkinteger(L, 2)),
        static_cast<int>(luaL_checkinteger(L, 3)), static_cast<int>(luaL_checkinteger(L, 4)), static_cast<int>(luaL_checkinteger(L, 5)),
        static_cast<int>(luaL_checkinteger(L, 6))))
    {
        lua_settop(L, 1);
        return 1;
    }
    lua_pushnil(L);
    lua_pushstring(L, pCanvas->getLastError());
    return 2;
}