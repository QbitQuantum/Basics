/*
 * Arguments: reg_udata, [name (string)]
 * Returns: [reg_udata]
 */
static int
reg_del_value (lua_State *L)
{
    HKEY hk = lua_unboxpointer(L, 1, WREG_TYPENAME);
    const char *name = lua_tostring(L, 2);
    int res;

    res = RegDeleteValueA(hk, name);
    if (!res) {
	lua_settop(L, 1);
	return 1;
    }
    return sys_seterror(L, res);
}