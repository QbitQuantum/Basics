/*---------------------------------------------------------------------------*/ 
static int tostring_u64(lua_State *L)
{
        char temp[64];
    //    sprintf_s(temp, "%I64u", *(unsigned long long*)lua_topointer(L, 1));
		_ui64toa_s(*(unsigned long long*)lua_topointer(L, 1),temp,sizeof(temp),10);
        lua_pushstring(L, temp);
        return 1;
}