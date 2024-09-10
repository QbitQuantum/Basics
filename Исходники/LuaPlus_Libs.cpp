static int LS_LOG( lua_State* L )
{
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	lua_getglobal(L, "towstring");
	lua_getglobal(L, "tostring");
	for (i=1; i<=n; i++) {
		const char *s = NULL;
		const lua_WChar *ws = NULL;
		if (lua_type(L, i) == LUA_TSTRING)
		{
			s = lua_tostring(L, -1);
		}
		else if (lua_type(L, i) != LUA_TWSTRING)
		{
			lua_pushvalue(L, -1);  /* function to be called */
			lua_pushvalue(L, i);   /* value to print */
			lua_call(L, 1, 1);
			s = lua_tostring(L, -1);  /* get result */
			if (s == NULL)
				return luaL_error(L, "`tostring' must return a string to `print'");
		}
		else
		{
			lua_pushvalue(L, -2);  /* function to be called */
			lua_pushvalue(L, i);   /* value to print */
			lua_call(L, 1, 1);
			ws = lua_towstring(L, -1);  /* get result */
			if (ws == NULL)
				return luaL_error(L, "`tostring' must return a string to `print'");
		}
		if (i>1)
		{
#ifdef WIN32
			OutputDebugStringA("\t");
#else
			fputs("\t", stdout);
#endif
		}
		if (s)
		{
#ifdef WIN32
			OutputDebugStringA(s);
#else
			fputs(s, stdout);
#endif
		}
		else if (ws)
		{
            wchar_t out[512];
            wchar_t* outEnd = out + sizeof(out) - 2;
            while (*ws) {
                wchar_t* outPos = out;
                while (*ws && outPos != outEnd) {
                *outPos++ = *ws++;
                }
                *outPos++ = 0;
#ifdef WIN32
			    OutputDebugStringW(out);
#else
    			fputws(out, stdout);
#endif
            }
		}
		lua_pop(L, 1);  /* pop result */
	}

#ifdef WIN32
	OutputDebugStringA("\n");
#else
	fputs("\n", stdout);
#endif

	return 0;
}