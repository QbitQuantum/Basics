int SFCbrt(lua_State* l)
{
    double x = lua_tonumber(Scripts.vm, 1);
    lua_pushnumber(Scripts.vm, cbrt(x));
    return 1;
}