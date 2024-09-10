void GuildRecv::processGuildMemberList(Net::MessageIn &msg)
{
    if (actorManager == nullptr)
        return;

    const int length = msg.readInt16("len");
    if (length < 4)
        return;
    int guildSize = 0;
    if (msg.getVersion() >= 20161026)
    {
        guildSize = 34;
    }
    else
    {
        guildSize = 104;
    }

    const int count = (length - 4) / guildSize;
    if (taGuild == nullptr)
    {
        logger->log1("!taGuild");
        return;
    }

    taGuild->clearMembers();

    int onlineNum = 0;
    int totalNum = 0;
    for (int i = 0; i < count; i++)
    {
        const BeingId id = msg.readBeingId("account id");
        const int charId = msg.readInt32("char id");
        msg.readInt16("hair");
        msg.readInt16("hair color");
        const int gender = msg.readInt16("gender");
        const int race = msg.readInt16("class");
        const int level = msg.readInt16("level");
        const int exp = msg.readInt32("exp");
        const int online = msg.readInt32("online");
        const int pos = msg.readInt32("position");
        std::string name;
        if (msg.getVersion() < 20161026)
        {
            msg.skip(50, "unused");
            name = msg.readString(24, "name");
        }
        else
        {
            msg.readInt32("last login");  // for now unused
            name = actorManager->findCharById(charId);
            if (name.empty())
            {
                beingHandler->requestNameByCharId(charId);
            }
        }

        GuildMember *const m = taGuild->addMember(id, charId, name);
        if (m != nullptr)
        {
            m->setOnline(online != 0);
            m->setID(id);
            m->setCharId(charId);
            m->setGender(Being::intToGender(CAST_U8(gender)));
            m->setLevel(level);
            m->setExp(exp);
            m->setPos(pos);
            m->setRace(race);
            Being *const being = actorManager->findBeingByName(
                name, ActorType::Player);
            if (being != nullptr)
            {
                being->setGuildName(taGuild->getName());
                if (being->getLevel() != level)
                {
                    being->setLevel(level);
                    being->updateName();
                }
            }
            if (online != 0)
                onlineNum ++;
            totalNum ++;
        }
    }
    taGuild->sort();
    actorManager->updatePlayerGuild();
    actorManager->updatePlayerColors();
    if (socialWindow != nullptr)
        socialWindow->updateGuildCounter(onlineNum, totalNum);
}