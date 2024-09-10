// get_player_information()
int ModApiServer::l_get_player_information(lua_State *L)
{

	NO_MAP_LOCK_REQUIRED;
	const char * name = luaL_checkstring(L, 1);
	Player *player = getEnv(L)->getPlayer(name);
	if(player == NULL)
	{
		lua_pushnil(L); // no such player
		return 1;
	}

	Address addr;
	try
	{
		addr = getServer(L)->getPeerAddress(player->peer_id);
	}
	catch(con::PeerNotFoundException) // unlikely
	{
		dstream << __FUNCTION_NAME << ": peer was not found" << std::endl;
		lua_pushnil(L); // error
		return 1;
	}

	float min_rtt,max_rtt,avg_rtt,min_jitter,max_jitter,avg_jitter;
	ClientState state;
	u32 uptime;
	u16 prot_vers;
	u8 ser_vers,major,minor,patch;
	std::string vers_string;

#define ERET(code)                                                             \
	if (!(code)) {                                                             \
		dstream << __FUNCTION_NAME << ": peer was not found" << std::endl;     \
		lua_pushnil(L); /* error */                                            \
		return 1;                                                              \
	}

	ERET(getServer(L)->getClientConInfo(player->peer_id,con::MIN_RTT,&min_rtt))
	ERET(getServer(L)->getClientConInfo(player->peer_id,con::MAX_RTT,&max_rtt))
	ERET(getServer(L)->getClientConInfo(player->peer_id,con::AVG_RTT,&avg_rtt))
	ERET(getServer(L)->getClientConInfo(player->peer_id,con::MIN_JITTER,&min_jitter))
	ERET(getServer(L)->getClientConInfo(player->peer_id,con::MAX_JITTER,&max_jitter))
	ERET(getServer(L)->getClientConInfo(player->peer_id,con::AVG_JITTER,&avg_jitter))

	ERET(getServer(L)->getClientInfo(player->peer_id,
										&state, &uptime, &ser_vers, &prot_vers,
										&major, &minor, &patch, &vers_string))

	lua_newtable(L);
	int table = lua_gettop(L);

	lua_pushstring(L,"address");
	lua_pushstring(L, addr.serializeString().c_str());
	lua_settable(L, table);

	lua_pushstring(L,"ip_version");
	if (addr.getFamily() == AF_INET) {
		lua_pushnumber(L, 4);
	} else if (addr.getFamily() == AF_INET6) {
		lua_pushnumber(L, 6);
	} else {
		lua_pushnumber(L, 0);
	}
	lua_settable(L, table);

	lua_pushstring(L,"min_rtt");
	lua_pushnumber(L, min_rtt);
	lua_settable(L, table);

	lua_pushstring(L,"max_rtt");
	lua_pushnumber(L, max_rtt);
	lua_settable(L, table);

	lua_pushstring(L,"avg_rtt");
	lua_pushnumber(L, avg_rtt);
	lua_settable(L, table);

	lua_pushstring(L,"min_jitter");
	lua_pushnumber(L, min_jitter);
	lua_settable(L, table);

	lua_pushstring(L,"max_jitter");
	lua_pushnumber(L, max_jitter);
	lua_settable(L, table);

	lua_pushstring(L,"avg_jitter");
	lua_pushnumber(L, avg_jitter);
	lua_settable(L, table);

	lua_pushstring(L,"connection_uptime");
	lua_pushnumber(L, uptime);
	lua_settable(L, table);

#ifndef NDEBUG
	lua_pushstring(L,"serialization_version");
	lua_pushnumber(L, ser_vers);
	lua_settable(L, table);

	lua_pushstring(L,"protocol_version");
	lua_pushnumber(L, prot_vers);
	lua_settable(L, table);

	lua_pushstring(L,"major");
	lua_pushnumber(L, major);
	lua_settable(L, table);

	lua_pushstring(L,"minor");
	lua_pushnumber(L, minor);
	lua_settable(L, table);

	lua_pushstring(L,"patch");
	lua_pushnumber(L, patch);
	lua_settable(L, table);

	lua_pushstring(L,"version_string");
	lua_pushstring(L, vers_string.c_str());
	lua_settable(L, table);

	lua_pushstring(L,"state");
	lua_pushstring(L,ClientInterface::state2Name(state).c_str());
	lua_settable(L, table);
#endif

#undef ERET
	return 1;
}