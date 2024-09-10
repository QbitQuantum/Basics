static int lua_Focus(lua_State *L){

	if (IsWindowVisible(ASWN->TC->hwnd))
		SwitchToThisWindow(ASWN->TC->hwnd,0);
	return 0;
}