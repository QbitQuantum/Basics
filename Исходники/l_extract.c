int
l_string_extract (lua_State *L)
{
	/* Init */
	char *fname = "extract";
	u_init(L, state, fname, NULL);

#ifdef TIMING
	/* Timestamp */
	TTR_START();
#endif

	/* Defines */
#ifdef LIBKIRK_DEBUG
	char pause;
#endif
	const char *string;
	long pos_1, pos_2;
	int len;

	/* Catches */
	if (lua_type(L, 1) == LUA_TSTRING)
		string = lua_tostring(L, 1);
	else
		return u_abort(1, "Incorrect argument type at position 1.");

	/* Get the first and last position to extract from. */
	if (lua_type(L, 2) == LUA_TNUMBER)
		pos_1 = lua_tonumber(L, 2);
	else
		return u_abort(1, "Incorrect argument type at position 2.");

	if (lua_type(L, 3) == LUA_TNUMBER)
		pos_2 = lua_tonumber(L, 3);
	else
		return u_abort(1, "Incorrect argument type at position 3.");

	/* Pop all values */
	lua_pop(L, 3);

#ifdef TIMING
	/* Get time to serve and all */
	TTR_END();
	TTR_ELAPSED();
#endif
	len = strlen(string);
	char n_value[(const int)len]; 

	/* Return results */
	lua_pushstring(L, n_value);
	return 1;
}