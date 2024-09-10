LUALIB_API void luaX_showtable(lua_State* L, int ix, const char* label/* = 0*/)
{
	lua_checkstack(L, 6);
	if (lua_istable(L, ix))
	{
		ATLTRACE2("%s:: Contents of table at index %i.\n", label, ix);
		int aix = ix; if (aix < 0) aix = lua_gettop(L) + aix + 1;
		lua_pushnil(L);
		while (lua_next(L, aix) != 0)
		{
			const char* ke = luaC_pushdstring(L, -2, 20);
			const char* vl = luaC_pushdstring(L, -2, 40);
			ATLTRACE2("++ Key: %s; Value: %s.\n", ke, vl);
			lua_pop(L, 3);
		}
	}
	else
	{
		ATLTRACE2("%s:: Value at index %i is not a table.\n", label, ix);
	}
}