	static int l_set_centre_sector(lua_State *l) {
		GalaxyMap *map = LuaObject<GalaxyMap>::CheckFromLua(1);
		float x = luaL_checknumber(l, 2);
		float y = luaL_checknumber(l, 3);
		map->SetCentreSector(vector2f(x, y));
		lua_settop(l, 1);
		return 1;
	}