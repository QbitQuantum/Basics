static int lua_RemoveButton(lua_State *L)
{
	HANDLE hTTButton = (HANDLE)lua_touserdata(L, 1);

	INT_PTR res = ::CallService(MS_TTB_REMOVEBUTTON, (WPARAM)hTTButton, 0);
	lua_pushinteger(L, res);

	if (!res)
		TBButtons.remove(hTTButton);

	return 1;
}