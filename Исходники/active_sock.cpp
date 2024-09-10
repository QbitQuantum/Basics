EXPORT_C int active_sock_open(lua_State* L)
	{
	RSocketServ sockServ;

	if (sockServ.Connect() != KErrNone)
		{
		return 0;
		}

	/* Register socket server with global context */
	lua_pushstring(L, reinterpret_cast<const char*>(KSocketServ().Ptr()));
	lua_pushnumber(L, sockServ.Handle());
	lua_settable(L, LUA_REGISTRYINDEX);

	luaL_register(L, "socket", active_socket);

	luaL_newmetatable(L, reinterpret_cast<const char*>(KSocketType().Ptr()));
	lua_pushcfunction(L, socket_gc);
	lua_setfield(L, -2, "__gc");
	
	lua_pushstring(L, reinterpret_cast<const char*>(KSocketType().Ptr()));
	lua_settable(L, LUA_REGISTRYINDEX);

	return 1;
	}