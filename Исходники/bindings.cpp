static int image_get_pixel(lua_State *L) {
	Image *image = (Image *)luaL_checkudata(L, 1, "mb_vision_image");
	int x = luaL_checkint(L, 2);
	int y = luaL_checkint(L, 3);
	
	Pixel pixel = image->getPixel(x, y);
	
	lua_pushinteger(L, pixel.r);
	lua_pushinteger(L, pixel.g);
	lua_pushinteger(L, pixel.b);
	
	return 3;
}