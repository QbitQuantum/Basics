/*
 * Arguments: window_handle (number)
 * Returns: boolean
 */
static int
plsql_FlashWindow (lua_State *L)
{
	const HWND hwnd = (HWND) luaL_checkinteger(L, 1);

	lua_pushboolean(L, FlashWindow(hwnd, 1));
	return 1;
}