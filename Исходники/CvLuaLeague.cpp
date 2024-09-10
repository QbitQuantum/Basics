//------------------------------------------------------------------------------
// Lua member methods
//------------------------------------------------------------------------------
//bool IsNone();
int CvLuaLeague::lIsNone(lua_State* L)
{
	const bool bDoesNotExist = (GetInstance(L, false) == NULL);
	lua_pushboolean(L, bDoesNotExist);
	return 1;
}