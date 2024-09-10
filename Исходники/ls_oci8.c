/*
** Return the list of field names as a table on top of the stack.
*/
static int cur_getcolnames (lua_State *L) {
	cur_data *cur = getcursor (L);
	if (cur->colnames != LUA_NOREF)
		lua_rawgeti (L, LUA_REGISTRYINDEX, cur->colnames);
	else {
		int i;
		lua_newtable (L);
		for (i = 1; i <= cur->numcols; i++) {
			column_data *col = &(cur->cols[i-1]);
			lua_pushlstring (L, col->name, col->namelen);
			lua_rawseti (L, -2, i);
		}
		lua_pushvalue (L, -1);
		cur->colnames = luaL_ref (L, LUA_REGISTRYINDEX);
	}
	return 1;
}