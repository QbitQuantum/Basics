static int icu_collator_strength(lua_State *L) {
	luaL_argcheck(L, lua_getmetatable(L,1) && lua_rawequal(L,-1,COLLATOR_UV_META), 1, "expecting collator");
	lua_pop(L,1);
	if (lua_gettop(L) == 1) {
		lua_pushnumber(L, ucol_getStrength(*(UCollator**)lua_touserdata(L,1)));
		return 1;
	}
	else {
		ucol_setStrength(*(UCollator**)lua_touserdata(L,1), (UCollationStrength)luaL_checknumber(L,2));
		lua_settop(L,1);
		return 1;
	}
}