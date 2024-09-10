static Int Pget(lua_State *L, int i)
{
 switch (lua_type(L,i))
 {
  case LUA_TNUMBER:
   return luaL_checknumber(L,i);
  case LUA_TSTRING:
   return atoI(luaL_checkstring(L,i));
  default:
   return *((Int*)luaL_checkudata(L,i,MYTYPE));
 }
}