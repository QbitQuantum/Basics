void AuthenticationServer::HandleAuthent(MsgEntry *me, Client *notused)
{
    csTicks start = csGetTicks();

    psAuthenticationMessage msg(me); // This cracks message into members.

    if (!msg.valid)
    {
        Debug1(LOG_NET,me->clientnum,"Mangled psAuthenticationMessage received.\n");
        return;
    }

    if (!CheckAuthenticationPreCondition(me->clientnum, msg.NetVersionOk(),msg.sUser))
        return;

    csString status;
    status.Format("%s, %u, Received Authentication Message", (const char *) msg.sUser, me->clientnum);
    psserver->GetLogCSV()->Write(CSV_AUTHENT, status);

    if ( msg.sUser.Length() == 0 || msg.sPassword.Length() == 0)
    {
        psserver->RemovePlayer(me->clientnum,"No username or password entered");

        Notify2(LOG_CONNECTIONS,"User '%s' authentication request rejected: No username or password.\n",
                (const char *)msg.sUser);            
        return;                
    }
    
    // Check if login was correct
    Notify2(LOG_CONNECTIONS,"Check Login for: '%s'\n", (const char*)msg.sUser);
    psAccountInfo *acctinfo=CacheManager::GetSingleton().GetAccountInfoByUsername((const char *)msg.sUser);

    if ( !acctinfo )
    {
        // invalid
        psserver->RemovePlayer(me->clientnum,"Incorrect password or username.");

        Notify2(LOG_CONNECTIONS,"User '%s' authentication request rejected: No account found with that name.\n",
                (const char *)msg.sUser);            
        return;                
    }

    // Add account to cache to optimize repeated login attempts
    CacheManager::GetSingleton().AddToCache(acctinfo,msg.sUser,120);
    
    // Check if password was correct
    csString passwordhashandclientnum (acctinfo->password);
    passwordhashandclientnum.Append(":");
    passwordhashandclientnum.Append(me->clientnum);
    
    csString encoded_hash = csMD5::Encode(passwordhashandclientnum).HexString();
    if (strcmp( encoded_hash.GetData() , msg.sPassword.GetData())) // authentication error
    {
        psserver->RemovePlayer(me->clientnum, "Incorrect password or username.");
        Notify2(LOG_CONNECTIONS,"User '%s' authentication request rejected (Bad password).",(const char *)msg.sUser);
        // No delete necessary because AddToCache will auto-delete
        // delete acctinfo;
        return;
    }
    
    /**
     * Check if the client is already logged in
     */
    Client* existingClient = clients->FindAccount(acctinfo->accountid, me->clientnum);
    if (existingClient)  // account already logged in
    {
        // invalid authent message from a different client
        csString reason;
        if(existingClient->IsZombie())
        {
            reason.Format("Your character(%s) was still in combat or casting a spell when you disconnected. "
                          "This connection is being overridden by a new login.", existingClient->GetName());
        }
        else
        {
            reason.Format("You are already logged on to this server as %s. "
                          "This connection is being overridden by a new login..", existingClient->GetName());
        }

        psserver->RemovePlayer(existingClient->GetClientNum(), reason);
        Notify2(LOG_CONNECTIONS,"User '%s' authentication request overrides an existing logged in user.\n",
            (const char *)msg.sUser);

        // No delete necessary because AddToCache will auto-delete
        // delete acctinfo;
    }


    if(csGetTicks() - start > 500)
    {
        csString status;
        status.Format("Warning: Spent %u time authenticating account ID %u, After password check", 
            csGetTicks() - start, acctinfo->accountid);
        psserver->GetLogCSV()->Write(CSV_STATUS, status);
    }


    Client *client = clients->FindAny(me->clientnum);
    if (!client)
    {
        Bug2("Couldn't find client %d?!?",me->clientnum);
        // No delete necessary because AddToCache will auto-delete
        // delete acctinfo;
        return;
    }

    client->SetName(msg.sUser);
    client->SetAccountID( acctinfo->accountid );
    

    // Check to see if the client is banned
    time_t now = time(0);
    BanEntry* ban = banmanager.GetBanByAccount(acctinfo->accountid);
    if (ban == NULL)
    {
        // Account not banned; try IP range
        ban = banmanager.GetBanByIPRange(client->GetIPRange());
        // 2 day IP ban limit removed
        //if (ban && ban->end && now > ban->start + IP_RANGE_BAN_TIME)
        //{  
        //    // Only ban by IP range for the first 2 days
        //    ban = NULL;
        //}
    }
    if (ban)
    {
        if (now > ban->end)  // Time served
        {
            banmanager.RemoveBan(acctinfo->accountid);
        }
        else  // Notify and block
        {
            tm* timeinfo = gmtime(&(ban->end));
            csString banmsg;
            banmsg.Format("You are banned until %d-%d-%d %d:%d GMT.  Reason: %s",
                          timeinfo->tm_year+1900,
                          timeinfo->tm_mon+1,
                          timeinfo->tm_mday,
                          timeinfo->tm_hour,
                          timeinfo->tm_min,
                          ban->reason.GetData() );
    
            psserver->RemovePlayer(me->clientnum, banmsg);
    
            Notify2(LOG_CONNECTIONS,"User '%s' authentication request rejected (Banned).",(const char *)msg.sUser);
            // No delete necessary because AddToCache will auto-delete
            // delete acctinfo;
            return;
        }
    }

    if(csGetTicks() - start > 500)
    {
        csString status;
        status.Format("Warning: Spent %u time authenticating account ID %u, After ban check", 
            csGetTicks() - start, acctinfo->accountid);
        psserver->GetLogCSV()->Write(CSV_STATUS, status);
    }

    /** Check to see if there are any players on that account.  All accounts should have
    *    at least one player in this function.
    */
    psCharacterList *charlist = psserver->CharacterLoader.LoadCharacterList(acctinfo->accountid);

    if (!charlist)
    {
        Error2("Could not load Character List for account! Rejecting client %s!\n",(const char *)msg.sUser);
        psserver->RemovePlayer( me->clientnum, "Could not load the list of characters for your account.  Please contact a PS Admin for help.");
        delete acctinfo;
        return;
    }

    // cache will auto-delete this ptr if it times out
    CacheManager::GetSingleton().AddToCache(charlist, CacheManager::GetSingleton().MakeCacheName("list", client->GetAccountID().Unbox()),120);

    
     /**
     * CHECK 6: Connection limit
     * 
     * We check against number of concurrent connections, but players with
     * security rank of GameMaster or higher are not subject to this limit.
     */
    if (psserver->IsFull(clients->Count(),client)) 
    {
        // invalid
        psserver->RemovePlayer(me->clientnum, "The server is full right now.  Please try again in a few minutes.");

        Notify2(LOG_CONNECTIONS, "User '%s' authentication request rejected: Too many connections.\n", (const char *)msg.sUser );
        // No delete necessary because AddToCache will auto-delete
        // delete acctinfo;
        status = "User limit hit!";
        psserver->GetLogCSV()->Write(CSV_STATUS, status);
        return;
    }

    Notify3(LOG_CONNECTIONS,"User '%s' (%d) added to active client list\n",(const char*) msg.sUser, me->clientnum);

    // Get the struct to refresh
    // Update last login ip and time
    char addr[20];
    client->GetIPAddress(addr);
    acctinfo->lastloginip = addr;

    tm* gmtm = gmtime(&now);
    csString timeStr;
    timeStr.Format("%d-%02d-%02d %02d:%02d:%02d",
        gmtm->tm_year+1900,
        gmtm->tm_mon+1,
        gmtm->tm_mday,
        gmtm->tm_hour,
        gmtm->tm_min,
        gmtm->tm_sec);

    acctinfo->lastlogintime = timeStr;
    acctinfo->os = msg.os_;
    acctinfo->gfxcard = msg.gfxcard_;
    acctinfo->gfxversion = msg.gfxversion_;
    CacheManager::GetSingleton().UpdateAccountInfo(acctinfo);

    iCachedObject *obj = CacheManager::GetSingleton().RemoveFromCache(CacheManager::GetSingleton().MakeCacheName("auth",acctinfo->accountid));
    CachedAuthMessage *cam;

    if (!obj)
    {
        // Send approval message
        psAuthApprovedMessage *message = new psAuthApprovedMessage(me->clientnum,client->GetPID(), charlist->GetValidCount() );    

        if(csGetTicks() - start > 500)
        {
            csString status;
            status.Format("Warning: Spent %u time authenticating account ID %u, After approval", 
                csGetTicks() - start, acctinfo->accountid);
            psserver->GetLogCSV()->Write(CSV_STATUS, status);
        }

        // Send out the character list to the auth'd player    
        for (int i=0; i<MAX_CHARACTERS_IN_LIST; i++)
        {
            if (charlist->GetEntryValid(i))
            {
                // Quick load the characters to get enough info to send to the client
                psCharacter* character = psserver->CharacterLoader.QuickLoadCharacterData( charlist->GetCharacterID(i), false );
                if (character == NULL)
                {
                    Error2("QuickLoadCharacterData failed for character '%s'", charlist->GetCharacterName(i));
                    continue;
                }

                Notify3(LOG_CHARACTER, "Sending %s to client %d\n", character->name.GetData(), me->clientnum );
                character->AppendCharacterSelectData(*message);

                delete character;
            }
        }
        message->ConstructMsg();
        cam = new CachedAuthMessage(message);
    }
    else
    {
        // recover underlying object
        cam = (CachedAuthMessage *)obj->RecoverObject();
        // update client id since new connection here
        cam->msg->msg->clientnum = me->clientnum;
    }
    // Send auth approved and char list in one message now
    cam->msg->SendMessage();
    CacheManager::GetSingleton().AddToCache(cam, CacheManager::GetSingleton().MakeCacheName("auth",acctinfo->accountid), 10);

    SendMsgStrings(me->clientnum, true); 
    
    client->SetSpamPoints(acctinfo->spamPoints);
    client->SetAdvisorPoints(acctinfo->advisorPoints);
    client->SetSecurityLevel(acctinfo->securitylevel);

    if (acctinfo->securitylevel >= GM_TESTER)
    {
        psserver->GetAdminManager()->Admin(me->clientnum, client);
    }
    
    if (CacheManager::GetSingletonPtr()->GetCommandManager()->Validate(client->GetSecurityLevel(), "default advisor"))
        psserver->GetAdviceManager()->AddAdvisor(client);

    if (CacheManager::GetSingletonPtr()->GetCommandManager()->Validate(client->GetSecurityLevel(), "default buddylisthide"))
        client->SetBuddyListHide(true);

    psserver->GetWeatherManager()->SendClientGameTime(me->clientnum);

    if(csGetTicks() - start > 500)
    {
        csString status;
        status.Format("Warning: Spent %u time authenticating account ID %u, After load", 
            csGetTicks() - start, acctinfo->accountid);
        psserver->GetLogCSV()->Write(CSV_STATUS, status);
    }

    status.Format("%s - %s, %u, Logged in", addr, (const char*) msg.sUser, me->clientnum);
    psserver->GetLogCSV()->Write(CSV_AUTHENT, status);
}