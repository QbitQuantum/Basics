 inline void push(lua_State* L, const rapidjson::Value& v)
 {
     ToLuaHandler handler(L);
     v.Accept(handler);
 }