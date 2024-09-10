void ChatHandler::handleGuildCreate(ChatClient &client, MessageIn &msg)
{
    MessageOut reply(CPMSG_GUILD_CREATE_RESPONSE);

    // Check if guild already exists and if so, return error
    std::string guildName = msg.readString();
    if (!guildManager->doesExist(guildName))
    {
        if ((int)client.guilds.size() >=
                Configuration::getValue("account_maxGuildsPerCharacter", 1))
        {
            reply.writeInt8(ERRMSG_LIMIT_REACHED);
        }
        else
        {
            // Guild doesnt already exist so create it
            Guild *guild = guildManager->createGuild(guildName, client.characterId);
            reply.writeInt8(ERRMSG_OK);
            reply.writeString(guildName);
            reply.writeInt16(guild->getId());
            reply.writeInt16(guild->getUserPermissions(client.characterId));

            client.guilds.push_back(guild);

            // Send autocreated channel id
            ChatChannel* channel = joinGuildChannel(guildName, client);
            reply.writeInt16(channel->getId());
        }
    }
    else
    {
        reply.writeInt8(ERRMSG_ALREADY_TAKEN);
    }

    client.send(reply);
}