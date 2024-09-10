int w_ImageData_setPixel(lua_State *L)
{
	ImageData *t = luax_checkimagedata(L, 1);
	int x = luaL_checkint(L, 2);
	int y = luaL_checkint(L, 3);
	pixel c;
	c.r = luaL_checkint(L, 4);
	c.g = luaL_checkint(L, 5);
	c.b = luaL_checkint(L, 6);
	c.a = luaL_checkint(L, 7);
	try
	{
		t->setPixel(x, y, c);
	}
	catch(love::Exception &e)
	{
		return luaL_error(L, "%s", e.what());
	}
	return 0;
}