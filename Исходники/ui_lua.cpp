/**\brief Get the Position and size of a Widget
 */
int UI_Lua::GetEdges(lua_State *L){
	int n = lua_gettop(L);  // Number of arguments
	if (n != 1)
		return luaL_error(L, "Got %d arguments expected 1 (self)", n);

	Widget *widget = checkWidget(L,1);
	lua_pushinteger(L, widget->GetX() );
	lua_pushinteger(L, widget->GetY() );
	lua_pushinteger(L, widget->GetW() );
	lua_pushinteger(L, widget->GetH() );

	return 4;
}