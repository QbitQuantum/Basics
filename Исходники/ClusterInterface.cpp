void ClusterInterface::HandlePlayerLogin(WorldPacket & pck)
{
	/* player x logging into instance y */
	uint32 guid, instance, mapid;
	uint32 accountid, accountflags, sessionid;
	string gmpermissions, accountname;
	pck >> guid >> mapid >> instance >> accountid >> accountflags >> sessionid >> gmpermissions >> accountname;

	/* find the instance */
	Map * ma = sWorldCreator.GetMap(mapid);
	ASSERT(ma);
	MapMgr * mm = ma->GetInstance(instance);
	ASSERT(mm);

	/* create the session */
	WorldSession * s = sWorld.FindSession(accountid);
	ASSERT(!s);

	/* create the socket */
	WorldSocket * so = new WorldSocket(sessionid);
	s = new WorldSession(accountid, accountname, so);
	_sessions[sessionid] = s;
	sWorld.AddSession(s);

	bool login_result = s->PlayerLogin(guid, mapid, instance);
	if(login_result)
	{
		/* login was ok. send a message to the realm server telling him to distribute our info to all other realm server */
		WorldPacket data(ICMSG_PLAYER_LOGIN_RESULT, 5);
		data << guid << sessionid <<  uint8(1);
		SendPacket(&data);
	}
	else
	{
		/* for some reason the login failed */
		WorldPacket data(ICMSG_PLAYER_LOGIN_RESULT, 5);
		data << guid << sessionid << uint8(0);
		SendPacket(&data);

		/* tell the client his login failed before deleting the session */
		data.Initialize(SMSG_CHARACTER_LOGIN_FAILED);
		data << uint8(62);
		so->SendPacket(&data);

		/* destroy the session */
		DestroySession(sessionid);
	}
}