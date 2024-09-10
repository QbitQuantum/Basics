int luaU_str2oid(lua_State* L)
{
	const char *s1 = luaL_checkstring(L, 1);
	char *s2;
	double n;
	UINT64 value;
	n = strtod(s1, &s2);
	if (s1 != s2) {  /* at least one valid digit? */
		while (isspace((unsigned char)(*s2))) s2++;  /* skip trailing spaces */
		if (*s2 == '\0') {  /* no invalid trailing characters? */
			value = _strtoi64(s1, &s2, 10);
			memcpy(&n, &value, sizeof(UINT64));
			lua_pushnumber(L, (lua_Number)n);
			return 1;
		}
	}
	lua_pushnil(L);  /* else not a number */
	return 1;
}