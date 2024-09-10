void WorldSession::HandleTurnInPetitionOpcode(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Received opcode CMSG_TURN_IN_PETITION"); // ok
    //recv_data.hexlike();

    WorldPacket data;
    uint64 petitionguid;

    uint32 ownerguidlo;
    uint32 type;
    std::string name;

    recv_data >> petitionguid;

    sLog->outDebug(LOG_FILTER_NETWORKIO, "Petition %u turned in by %u", GUID_LOPART(petitionguid), _player->GetGUIDLow());

    // data
    QueryResult result = CharacterDatabase.PQuery("SELECT ownerguid, name, type FROM petition WHERE petitionguid = '%u'", GUID_LOPART(petitionguid));
    if (result)
    {
        Field *fields = result->Fetch();
        ownerguidlo = fields[0].GetUInt32();
        name = fields[1].GetString();
        type = fields[2].GetUInt8();
    }
    else
    {
        sLog->outError("petition table has broken data!");
        return;
    }

    if (type == GUILD_CHARTER_TYPE)
    {
        if (_player->GetGuildId())
        {
            data.Initialize(SMSG_TURN_IN_PETITION_RESULTS, 4);
            data << (uint32)PETITION_TURN_ALREADY_IN_GUILD; // already in guild
            _player->GetSession()->SendPacket(&data);
            return;
        }
    }
    else
    {
        uint8 slot = ArenaTeam::GetSlotByType(type);
        if (slot >= MAX_ARENA_SLOT)
            return;

        if (_player->GetArenaTeamId(slot))
        {
            //data.Initialize(SMSG_TURN_IN_PETITION_RESULTS, 4);
            //data << (uint32)PETITION_TURN_ALREADY_IN_GUILD;                          // already in guild
            //_player->GetSession()->SendPacket(&data);
            SendArenaTeamCommandResult(ERR_ARENA_TEAM_CREATE_S, name, "", ERR_ALREADY_IN_ARENA_TEAM);
            return;
        }
    }

    if (_player->GetGUIDLow() != ownerguidlo)
        return;

    // signs
    uint8 signs;
    result = CharacterDatabase.PQuery("SELECT playerguid FROM petition_sign WHERE petitionguid = '%u'", GUID_LOPART(petitionguid));
    if (result)
        signs = uint8(result->GetRowCount());
    else
        signs = 0;

    uint32 count;
    //if (signs < sWorld->getIntConfig(CONFIG_MIN_PETITION_SIGNS))
    if (type == GUILD_CHARTER_TYPE)
        count = sWorld->getIntConfig(CONFIG_MIN_PETITION_SIGNS);
    else
        count = type-1;
    if (signs < count)
    {
        data.Initialize(SMSG_TURN_IN_PETITION_RESULTS, 4);
        data << (uint32)PETITION_TURN_NEED_MORE_SIGNATURES; // need more signatures...
        SendPacket(&data);
        return;
    }

    if (type == GUILD_CHARTER_TYPE)
    {
        if (sObjectMgr->GetGuildByName(name))
        {
            Guild::SendCommandResult(this, GUILD_CREATE_S, ERR_GUILD_NAME_EXISTS_S, name);
            return;
        }
    }
    else
    {
        if (sObjectMgr->GetArenaTeamByName(name))
        {
            SendArenaTeamCommandResult(ERR_ARENA_TEAM_CREATE_S, name, "", ERR_ARENA_TEAM_NAME_EXISTS_S);
            return;
        }
    }

    // and at last charter item check
    Item *item = _player->GetItemByGuid(petitionguid);
    if (!item)
        return;

    // OK!

    // delete charter item
    _player->DestroyItem(item->GetBagSlot(),item->GetSlot(), true);

    if (type == GUILD_CHARTER_TYPE)                         // create guild
    {
        Guild* guild = new Guild;
        if (!guild->Create(_player, name))
        {
            delete guild;
            return;
        }

        // register guild and add guildmaster
        sObjectMgr->AddGuild(guild);

        // add members
        for (uint8 i = 0; i < signs; ++i)
        {
            Field* fields = result->Fetch();
            guild->AddMember(fields[0].GetUInt64());
            result->NextRow();
        }
    }
    else                                                    // or arena team
    {
        ArenaTeam* at = new ArenaTeam;
        if (!at->Create(_player->GetGUID(), type, name))
        {
            sLog->outError("PetitionsHandler: arena team create failed.");
            delete at;
            return;
        }

        uint32 icon, iconcolor, border, bordercolor, backgroud;
        recv_data >> backgroud >> icon >> iconcolor >> border >> bordercolor;

        at->SetEmblem(backgroud, icon, iconcolor, border, bordercolor);

        // register team and add captain
        sObjectMgr->AddArenaTeam(at);
        sLog->outDebug(LOG_FILTER_NETWORKIO, "PetitonsHandler: arena team added to objmrg");

        // add members
        for (uint8 i = 0; i < signs; ++i)
        {
            Field* fields = result->Fetch();
            uint64 memberGUID = fields[0].GetUInt64();
            sLog->outDebug(LOG_FILTER_NETWORKIO, "PetitionsHandler: adding arena member %u", GUID_LOPART(memberGUID));
            at->AddMember(memberGUID);
            result->NextRow();
        }
    }

    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    trans->PAppend("DELETE FROM petition WHERE petitionguid = '%u'", GUID_LOPART(petitionguid));
    trans->PAppend("DELETE FROM petition_sign WHERE petitionguid = '%u'", GUID_LOPART(petitionguid));
    CharacterDatabase.CommitTransaction(trans);

    // created
    sLog->outDebug(LOG_FILTER_NETWORKIO, "TURN IN PETITION GUID %u", GUID_LOPART(petitionguid));

    data.Initialize(SMSG_TURN_IN_PETITION_RESULTS, 4);
    data << (uint32)PETITION_TURN_OK;
    SendPacket(&data);
}