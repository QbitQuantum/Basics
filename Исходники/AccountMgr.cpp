int AccountMgr::DeleteAccount(uint32 accid)
{
    QueryResult *result = loginDatabase.PQuery("SELECT 1 FROM account WHERE id='%d'", accid);
    if(!result)
        return 1;                                           // account doesn't exist
    delete result;

    result = CharacterDatabase.PQuery("SELECT guid FROM characters WHERE account='%d'",accid);
    if (result)
    {
        do
        {
            Field *fields = result->Fetch();
            uint32 guidlo = fields[0].GetUInt32();
            uint64 guid = MAKE_GUID(guidlo, HIGHGUID_PLAYER);

            // kick if player currently
            if(Player* p = objmgr.GetPlayer(guid))
            {
                WorldSession* s = p->GetSession();
                s->KickPlayer();                            // mark session to remove at next session list update
                s->LogoutPlayer(false);                     // logout player without waiting next session list update
            }

            Player::DeleteFromDB(guid, accid, false);       // no need to update realm characters
        } while (result->NextRow());

        delete result;
    }

    loginDatabase.BeginTransaction();

    bool res =  loginDatabase.PExecute("DELETE FROM account WHERE id='%d'", accid) &&
        loginDatabase.PExecute("DELETE FROM realmcharacters WHERE acctid='%d'", accid);

    loginDatabase.CommitTransaction();

    if(!res)
        return -1;                                          // unexpected error;

    return 0;
}