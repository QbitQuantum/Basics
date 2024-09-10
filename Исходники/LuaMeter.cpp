static int GetW(lua_State* L)
{
	CMeter* self = GetSelf(L);
	lua_pushnumber(L, self->GetW());

	return 1;
}