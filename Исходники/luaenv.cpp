int LuaBinder::luaDispatcherShutdown(lua_State*)
{
	g_dispatcher.shutdown();
	return 1;
}