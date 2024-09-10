int DERPEditor::net_client_connect(lua_State *L)
{
    if (lua_gettop(L) == 3)
    {
        lua_getfield(L, -3, "instance");
        Client* client = *(Client**)lua_touserdata(L, -1);
        bool ret = client->Connect(lua_tolstring(L, -3, NULL), lua_tonumber(L, -2));
//		Message("aoeu", "connecting to %s", lua_tolstring(L, -3, NULL));

        if (!ret)
        {
            lua_pushstring(L, "Couldn't connect.");
            return 1;
        }

        return 0;
    }
    else
    {
        lua_pushstring(L, "Invalid arguments passed to connect function!");
        lua_error(L);
    }

    return 0;
}