/*
** Push the number of rows.
*/
static int cur_numrows (lua_State *L) {
	lua_pushnumber (L, (lua_Number)mysql_num_rows (getcursor(L)->my_res));
	return 1;
}