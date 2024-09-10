int LuaChat::broadcastOps(lua_State* L) {
    luaL_checkany(L, 2);
    if (lua_type(L, 2) != LUA_TTABLE)
        return luaL_error(L, "broadcastOps requires a table as the second argument.");

    string message = luaL_checkstring(L, 1);
    message += " ";
    json_t* json = luaToJson(L);
    const char* jsonstr = json_dumps(json, JSON_COMPACT);
    message += jsonstr;
    free((void*) jsonstr);
    json_decref(json);
    lua_pop(L, 2);
    MessagePtr outMessage(MessageBuffer::FromString(message));
    const oplist_t ops = ServerState::getOpList();
    for (oplist_t::const_iterator i = ops.begin(); i != ops.end(); ++i) {
        string name(*i);
        int length = name.length();
        for (int x = 0; x < length; ++x) {
            name[x] = tolower(name[x]);
        }
        ConnectionPtr con = ServerState::getConnection(name);
        if (con != 0) {
            con->send(outMessage);
        }
    }
    return 0;
}