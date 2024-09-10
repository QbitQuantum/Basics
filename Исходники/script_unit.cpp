/**
**  Remove unit from the map.
**
**  @param l  Lua state.
**
**  @return   Returns 1.
*/
static int CclRemoveUnit(lua_State *l)
{
	LuaCheckArgs(l, 1);
	lua_pushvalue(l, 1);
	CUnit *unit = CclGetUnit(l);
	lua_pop(l, 1);
	unit->Remove(NULL);
	lua_pushvalue(l, 1);
	return 1;
}