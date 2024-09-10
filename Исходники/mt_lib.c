int getChar_4lua(lua_State *L)
{
	putChar(L, getChar());
	
	return 1;
}