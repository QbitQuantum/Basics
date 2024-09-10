int os_getversion(lua_State* L)
{
	struct OsVersionInfo info;
	getversion(&info);

	lua_newtable(L);

	lua_pushstring(L, "majorversion");
	lua_pushnumber(L, info.majorversion);
	lua_settable(L, -3);
	
	lua_pushstring(L, "minorversion");
	lua_pushnumber(L, info.minorversion);
	lua_settable(L, -3);

	lua_pushstring(L, "revision");
	lua_pushnumber(L, info.revision);
	lua_settable(L, -3);

	lua_pushstring(L, "description");
	lua_pushstring(L, info.description);
	lua_settable(L, -3);

	return 1;
}