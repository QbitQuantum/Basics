static int icu_normalizer_lessorequal(lua_State *L) {
	const UChar* left = icu4lua_checkustring(L,1,NORMALIZER_UV_USTRING_META);
	int32_t left_length = (int32_t)icu4lua_ustrlen(L,1);
	const UChar* right = icu4lua_checkustring(L,2,NORMALIZER_UV_USTRING_META);
	int32_t right_length = (int32_t)icu4lua_ustrlen(L,2);
	int32_t options = luaL_optint(L,3,0);
	UErrorCode status = U_ZERO_ERROR;
	lua_pushboolean(L, unorm_compare(left, left_length, right, right_length, options, &status) <= 0);
	if (U_FAILURE(status)) {
		lua_pushstring(L, u_errorName(status));
		return lua_error(L);
	}
	return 1;
}