/* createicon
 *
 * Creates an icon resource from its filename
 *
 * usage: luasystray.createicon(<icon description table>)
 *
 * @param 	options 	Systray Icon Description Table:
 *
 * Systray Icon Description Table
 *   resourceid	: resource identifier to load icon from
 *   filename 	: icon filename to load icon from
 *   bitmap 	: true if icon file is a bitmap
 *	 width		: desired width for icon
 *	 height		: desired height for icon
 */
int createIcon(lua_State*L) {
	luaL_checkany(L, 1);
	int type = lua_type(L, 1);

	HMODULE hinstance = 0;
	int imgtype = IMAGE_ICON;

	const char*filename = NULL;
	const char*resourceid = NULL;

	int width = 0;
	int height = 0;
	int bitmap = 0;

	int loadtype = LR_LOADFROMFILE;

	if(type==LUA_TSTRING) {
		filename = lua_tostring(L, 1);
	}

	if(type==LUA_TTABLE) {
		getoption(1, resourceid);
		getoption(1, filename);
		getoption(1, bitmap);
		getoption(1, width);
		getoption(1, height);
	}

	if(bitmap) {
		imgtype = IMAGE_BITMAP;
		width = 0;
		height = 0;
	}

	if(resourceid) {
		loadtype = LR_DEFAULTCOLOR | LR_DEFAULTSIZE;
		hinstance = GetModuleHandleW(NULL);
		filename = resourceid;
	}

	HANDLE img = LoadImageW(
		hinstance,
		_T(filename),
		imgtype,
		width, height,
		loadtype
	);

	if(img) {
		luaL_error(L, "Error loading image");
	}

	lua_settop(L, 0);
	lua_pushlightuserdata(L, img);

	return 1;
}