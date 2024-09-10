void LoginRecv::processLoginData(Net::MessageIn &msg)
{
    msg.readInt16("len");

    loginHandler->clearWorlds();

    int offset = 0;
    int serverLen = 0;
    if (msg.getVersion() >= 20170315)
    {
        offset = 47 + 17;
        serverLen = 32 + 128;
    }
    else
    {
        offset = 47;
        serverLen = 32;
    }

    const int worldCount = (msg.getLength() - offset) / serverLen;

    Ea::LoginRecv::mToken.session_ID1 = msg.readInt32("session id1");
    Ea::LoginRecv::mToken.account_ID = msg.readBeingId("accound id");
    Ea::LoginRecv::mToken.session_ID2 = msg.readInt32("session id2");
    msg.readInt32("old ip");
    loginData.lastLogin = msg.readString(24, "last login");
    msg.readInt16("unused");

    // reserve bits for future usage
    Ea::LoginRecv::mToken.sex = Being::intToGender(CAST_U8(
        msg.readUInt8("gender") & 3U));

    if (msg.getVersion() >= 20170315)
    {
        msg.readString(16, "twitter auth token");
        msg.readUInt8("twitter flag");
    }

    for (int i = 0; i < worldCount; i++)
    {
        WorldInfo *const world = new WorldInfo;

        world->address = msg.readInt32("ip address");
        world->port = msg.readInt16("port");
        world->name = msg.readString(20, "name");
        world->online_users = msg.readInt16("online number");
        config.setValue("updatehost", Ea::LoginRecv::mUpdateHost);
        world->updateHost = Ea::LoginRecv::mUpdateHost;
        msg.readInt16("maintenance");
        msg.readInt16("new");
        if (msg.getVersion() >= 20170315)
        {
            for (int f = 0; f < 32; f ++)
                msg.readInt32("unused2");
        }

        logger->log("Network: Server: %s (%s:%d)", world->name.c_str(),
            ipToString(world->address), world->port);

        Ea::LoginRecv::mWorlds.push_back(world);
    }
    client->setState(State::WORLD_SELECT);
}