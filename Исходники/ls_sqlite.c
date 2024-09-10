/*
** Get another row of the given cursor.
*/
static int cur_fetch (lua_State *L) {
	cur_data *cur = getcursor(L);
    sqlite_vm *vm = cur->sql_vm;
    const char **row = NULL;
    int res;

    if (vm == NULL)
        return 0;

    res = sqlite_step(vm, NULL, &row, NULL);

    /* no more results? */
    if (res == SQLITE_DONE)
        return finalize(L, cur);

    if (res != SQLITE_ROW)
        return finalize(L, cur);

	if (lua_istable (L, 2))
    {
		int i;
		const char *opts = luaL_optstring(L, 3, "n");

		if (strchr(opts, 'n') != NULL)
        {
			/* Copy values to numerical indices */
			for (i = 0; i < cur->numcols;)
            {
                lua_pushstring(L, row[i]);
				lua_rawseti(L, 2, ++i);
			}
        }
		if (strchr(opts, 'a') != NULL)
        {
			/* Copy values to alphanumerical indices */
            lua_rawgeti(L, LUA_REGISTRYINDEX, cur->colnames);

			for (i = 0; i < cur->numcols; i++)
            {
				lua_rawgeti(L, -1, i+1);
                lua_pushstring(L, row[i]);
				lua_rawset (L, 2);
			}
        }
		lua_pushvalue(L, 2);
		return 1; /* return table */
	}
	else
    {
		int i;
		luaL_checkstack (L, cur->numcols, LUASQL_PREFIX"too many columns");
		for (i = 0; i < cur->numcols; ++i)
			lua_pushstring(L, row[i]);
		return cur->numcols; /* return #numcols values */
	}
}