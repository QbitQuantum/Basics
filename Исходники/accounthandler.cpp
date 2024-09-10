void AccountHandler::handleLoginMessage(AccountClient &client, MessageIn &msg)
{
    MessageOut reply(APMSG_LOGIN_RESPONSE);

    if (client.status != CLIENT_LOGIN)
    {
        reply.writeInt8(ERRMSG_FAILURE);
        client.send(reply);
        return;
    }

    const int clientVersion = msg.readInt32();

    if (clientVersion < PROTOCOL_VERSION)
    {
        reply.writeInt8(LOGIN_INVALID_VERSION);
        client.send(reply);
        return;
    }

    // Check whether the last login attempt for this IP is still too fresh
    const int address = client.getIP();
    const time_t now = time(NULL);
    IPsToTime::const_iterator it = mLastLoginAttemptForIP.find(address);
    if (it != mLastLoginAttemptForIP.end())
    {
        const time_t lastAttempt = it->second;
        if (now < lastAttempt + 1)
        {
            reply.writeInt8(LOGIN_INVALID_TIME);
            client.send(reply);
            return;
        }
    }
    mLastLoginAttemptForIP[address] = now;

    const std::string username = msg.readString();
    const std::string password = msg.readString();

    if (stringFilter->findDoubleQuotes(username))
    {
        reply.writeInt8(ERRMSG_INVALID_ARGUMENT);
        client.send(reply);
        return;
    }

    const unsigned maxClients =
            (unsigned) Configuration::getValue("net_maxClients", 1000);

    if (getClientCount() >= maxClients)
    {
        reply.writeInt8(ERRMSG_SERVER_FULL);
        client.send(reply);
        return;
    }

    // Check if the account exists
    Account *acc = 0;
    std::list<Account*>::iterator ita;
    for ( ita = mPendingAccounts.begin() ; ita != mPendingAccounts.end(); ita++ )
        if ((*ita)->getName() == username)
            acc = *ita;
    mPendingAccounts.remove(acc);

    if (!acc || sha256(acc->getPassword() + acc->getRandomSalt()) != password)
    {
        reply.writeInt8(ERRMSG_INVALID_ARGUMENT);
        client.send(reply);
        delete acc;
        return;
    }

    if (acc->getLevel() == AL_BANNED)
    {
        reply.writeInt8(LOGIN_BANNED);
        client.send(reply);
        delete acc;
        return;
    }

    // The client successfully logged in...

    // Set lastLogin date of the account.
    time_t login;
    time(&login);
    acc->setLastLogin(login);
    storage->updateLastLogin(acc);

    // Associate account with connection.
    client.setAccount(acc);
    client.status = CLIENT_CONNECTED;

    reply.writeInt8(ERRMSG_OK);
    addServerInfo(&reply);
    client.send(reply); // Acknowledge login

    // Return information about available characters
    Characters &chars = acc->getCharacters();

    // Send characters list
    for (Characters::const_iterator i = chars.begin(), i_end = chars.end();
         i != i_end; ++i)
        sendCharacterData(client, *(*i).second);
}