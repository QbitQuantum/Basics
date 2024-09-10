int LuaPrinter2::abort(lua_State *L)
{
	QPrinter* obj = ValueInstaller<LuaPrinter2>::check( L, 1 );
	lua_pushboolean( L, obj->abort() );
	return 1;
}