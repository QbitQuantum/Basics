	int SetPixel(lua_State *L)
	{
		int x = (int)lua_tointeger( L, -3 );
		int y = (int)lua_tointeger( L, -2 );
		bool bit = (int)lua_tointeger( L, -1 ) != 0;
		image.setPixel( x, y, bit );
		return 0;
	}