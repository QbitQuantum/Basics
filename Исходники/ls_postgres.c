/*
** Return the list of field types.
*/
static int cur_getcoltypes (lua_State *L) {
	pushtable (L, getcursor(L), coltypes, create_coltypes);
	return 1;
}