DumpReturn PlayerDumpReader::LoadDump(const std::string& file, uint32 account, std::string name, uint32 guid)
{
    // check character count
    uint32 charcount = sAccountMgr->GetCharactersCount(account);
    if (charcount >= 10)
        return DUMP_TOO_MANY_CHARS;

    FILE *fin = fopen(file.c_str(), "r");
    if (!fin)
        return DUMP_FILE_OPEN_ERROR;

    QueryResult_AutoPtr result = QueryResult_AutoPtr(NULL);
    char newguid[20], chraccount[20], newpetid[20], currpetid[20], lastpetid[20];

    // make sure the same guid doesn't already exist and is safe to use
    bool incHighest = true;
    if (guid != 0 && guid < objmgr.m_hiCharGuid)
    {
        result = CharacterDatabase.PQuery("SELECT 1 FROM characters WHERE guid = '%d'", guid);
        if (result)
            guid = objmgr.m_hiCharGuid;                     // use first free if exists
        else incHighest = false;
    }
    else
        guid = objmgr.m_hiCharGuid;

    // normalize the name if specified and check if it exists
    if (!normalizePlayerName(name))
        name = "";

    if (ObjectMgr::IsValidName(name,true))
    {
        CharacterDatabase.escape_string(name);              // for safe, we use name only for sql quearies anyway
        result = CharacterDatabase.PQuery("SELECT 1 FROM characters WHERE name = '%s'", name.c_str());
        if (result)
            name = "";                                      // use the one from the dump
    }
    else
        name = "";

    // name encoded or empty

    snprintf(newguid, 20, "%d", guid);
    snprintf(chraccount, 20, "%d", account);
    snprintf(newpetid, 20, "%d", objmgr.GeneratePetNumber());
    snprintf(lastpetid, 20, "%s", "");

    std::map<uint32,uint32> items;
    std::map<uint32,uint32> mails;
    char buf[32000] = "";

    typedef std::map<uint32, uint32> PetIds;                // old->new petid relation
    typedef PetIds::value_type PetIdsPair;
    PetIds petids;

    CharacterDatabase.BeginTransaction();
    while (!feof(fin))
    {
        if (!fgets(buf, 32000, fin))
        {
            if (feof(fin)) break;
            ROLLBACK(DUMP_FILE_BROKEN);
        }

        std::string line; line.assign(buf);

        // skip empty strings
        size_t nw_pos = line.find_first_not_of(" \t\n\r\7");
        if (nw_pos == std::string::npos)
            continue;

        // skip NOTE
        if (line.substr(nw_pos,15) == "IMPORTANT NOTE:")
            continue;

        // determine table name and load type
        std::string tn = gettablename(line);
        if (tn.empty())
        {
            sLog.outError("LoadPlayerDump: Can't extract table name from line: '%s'!", line.c_str());
            ROLLBACK(DUMP_FILE_BROKEN);
        }

        DumpTableType type;
        uint8 i;
        for (i = 0; i < DUMP_TABLE_COUNT; ++i)
        {
            if (tn == dumpTables[i].name)
            {
                type = dumpTables[i].type;
                break;
            }
        }

        if (i == DUMP_TABLE_COUNT)
        {
            sLog.outError("LoadPlayerDump: Unknown table: '%s'!", tn.c_str());
            ROLLBACK(DUMP_FILE_BROKEN);
        }

        // change the data to server values
        switch(type)
        {
            case DTT_CHAR_TABLE:
                if (!changenth(line, 1, newguid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                break;

            case DTT_CHARACTER:                             // character t.
            {
                if (!changenth(line, 1, newguid))
                    ROLLBACK(DUMP_FILE_BROKEN);

                // guid, data field:guid, items
                if (!changenth(line, 2, chraccount))
                    ROLLBACK(DUMP_FILE_BROKEN);
                std::string vals = getnth(line, 3);
                if (!changetoknth(vals, OBJECT_FIELD_GUID+1, newguid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                for (uint16 field = PLAYER_FIELD_INV_SLOT_HEAD; field < PLAYER_FARSIGHT; field++)
                    if (!changetokGuid(vals, field+1, items, objmgr.m_hiItemGuid, true))
                        ROLLBACK(DUMP_FILE_BROKEN);
                if (!changenth(line, 3, vals.c_str()))
                    ROLLBACK(DUMP_FILE_BROKEN);
                if (name == "")
                {
                    // check if the original name already exists
                    name = getnth(line, 4);
                    CharacterDatabase.escape_string(name);

                    result = CharacterDatabase.PQuery("SELECT 1 FROM characters WHERE name = '%s'", name.c_str());
                    if (result)
                    {
                        if (!changenth(line, 30, "1"))       // rename on login: `at_login` field 30 in raw field list
                            ROLLBACK(DUMP_FILE_BROKEN);
                    }
                }
                else if (!changenth(line, 4, name.c_str()))
                    ROLLBACK(DUMP_FILE_BROKEN);

                break;
            }
            case DTT_INVENTORY:                             // character_inventory t.
            {
                if (!changenth(line, 1, newguid))
                    ROLLBACK(DUMP_FILE_BROKEN);

                // bag, item
                if (!changeGuid(line, 2, items, objmgr.m_hiItemGuid, true))
                    ROLLBACK(DUMP_FILE_BROKEN);
                if (!changeGuid(line, 4, items, objmgr.m_hiItemGuid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                break;
            }
            case DTT_ITEM:                                  // item_instance t.
            {
                // item, owner, data field:item, owner guid
                if (!changeGuid(line, 1, items, objmgr.m_hiItemGuid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                if (!changenth(line, 2, newguid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                std::string vals = getnth(line,3);
                if (!changetokGuid(vals, OBJECT_FIELD_GUID+1, items, objmgr.m_hiItemGuid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                if (!changetoknth(vals, ITEM_FIELD_OWNER+1, newguid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                if (!changenth(line, 3, vals.c_str()))
                    ROLLBACK(DUMP_FILE_BROKEN);
                break;
            }
            case DTT_ITEM_GIFT:                             // character_gift
            {
                // guid,item_guid,
                if (!changenth(line, 1, newguid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                if (!changeGuid(line, 2, items, objmgr.m_hiItemGuid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                break;
            }
            case DTT_PET:                                   // character_pet t
            {
                //store a map of old pet id to new inserted pet id for use by type 5 tables
                snprintf(currpetid, 20, "%s", getnth(line, 1).c_str());
                if (strlen(lastpetid) == 0) snprintf(lastpetid, 20, "%s", currpetid);
                if (strcmp(lastpetid,currpetid) != 0)
                {
                    snprintf(newpetid, 20, "%d", objmgr.GeneratePetNumber());
                    snprintf(lastpetid, 20, "%s", currpetid);
                }

                std::map<uint32, uint32> :: const_iterator petids_iter = petids.find(atoi(currpetid));

                if (petids_iter == petids.end())
                {
                    petids.insert(PetIdsPair(atoi(currpetid), atoi(newpetid)));
                }

                // item, entry, owner, ...
                if (!changenth(line, 1, newpetid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                if (!changenth(line, 3, newguid))
                    ROLLBACK(DUMP_FILE_BROKEN);

                break;
            }
            case DTT_PET_TABLE:                             // pet_aura, pet_spell, pet_spell_cooldown t
            {
                snprintf(currpetid, 20, "%s", getnth(line, 1).c_str());

                // lookup currpetid and match to new inserted pet id
                std::map<uint32, uint32> :: const_iterator petids_iter = petids.find(atoi(currpetid));
                if (petids_iter == petids.end())             // couldn't find new inserted id
                    ROLLBACK(DUMP_FILE_BROKEN);

                snprintf(newpetid, 20, "%d", petids_iter->second);

                if (!changenth(line, 1, newpetid))
                    ROLLBACK(DUMP_FILE_BROKEN);

                break;
            }
            case DTT_MAIL:                                  // mail
            {
                // id,messageType,stationery,sender,receiver
                if (!changeGuid(line, 1, mails, objmgr.m_mailid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                if (!changenth(line, 5, newguid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                break;
            }
            case DTT_MAIL_ITEM:                             // mail_items
            {
                // mail_id,item_guid,item_template,receiver
                if (!changeGuid(line, 1, mails, objmgr.m_mailid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                if (!changeGuid(line, 2, items, objmgr.m_hiItemGuid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                if (!changenth(line, 4, newguid))
                    ROLLBACK(DUMP_FILE_BROKEN);
                break;
            }
            default:
                sLog.outError("Unknown dump table type: %u",type);
                break;
        }

        if (!CharacterDatabase.Execute(line.c_str()))
            ROLLBACK(DUMP_FILE_BROKEN);
    }

    CharacterDatabase.CommitTransaction();

    objmgr.m_hiItemGuid += items.size();
    objmgr.m_mailid     += mails.size();

    if (incHighest)
        ++objmgr.m_hiCharGuid;

    fclose(fin);

    return DUMP_SUCCESS;
}