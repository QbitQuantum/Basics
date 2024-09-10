int lraknet_Send(lua_State* L)
{
    RakPeerInterface* peer = __self(L);

    size_t len = 0;
    const char* data = luaL_checklstring(L, 2, &len);
    lua_Integer priority = luaL_checkinteger(L, 3);
    lua_Integer reliability = luaL_checkinteger(L, 4);
    lua_Integer orderingChannel = luaL_checkinteger(L, 5);

    uint64_t guid = luaL_checkinteger(L, 6);
    lua_Integer broadcast = luaL_checkinteger(L, 7);

    uint32_t n = peer->Send(data,
                            len,
                            (PacketPriority)priority,
                            (PacketReliability)reliability,
                            (char)orderingChannel,
                            AddressOrGUID(RakNetGUID(guid)),
                            (bool)broadcast);

    lua_pushinteger(L, n);
    return 1;
}