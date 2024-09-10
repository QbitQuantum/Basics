static int lua_MessageBox(lua_State *L)
{
	HWND hwnd = (HWND)lua_touserdata(L, 1);
	ptrT text(mir_utf8decodeT(lua_tostring(L, 2)));
	ptrT caption(mir_utf8decodeT(lua_tostring(L, 3)));
	UINT flags = lua_tointeger(L, 4);
	LANGID langId = GetUserDefaultUILanguage();
	DWORD timeout = luaL_optinteger(L, 5, 0xFFFFFFFF);

	int res = ::MessageBoxTimeout(hwnd, text, caption, flags, langId, timeout);
	lua_pushinteger(L, res);

	return 1;
}