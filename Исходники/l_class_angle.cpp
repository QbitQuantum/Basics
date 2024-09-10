int SOPAngle::__div(lua_State *L) {
    SOPAngle *ang = Div(luaL_checknumber(L, 1));
    if(ang)
    {
        Lunar<SOPAngle>::push(L, ang, true);
        return 1;
    }
    lua_pushnil(L);
    return 1;
}