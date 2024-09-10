/*
** Return the list of field names.
*/
static int cur_getcolnames(lua_State *L)
{
    cur_data *cur = getcursor(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, cur->colnames);
	return 1;
}