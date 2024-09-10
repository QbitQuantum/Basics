void ChatMessageLib::sendChatRoomMessage(Channel* channel, BString galaxy, BString sender, BString message) const
{
    ChatAvatarIdList::iterator iter = channel->getUserList()->begin();

#ifdef DISP_REAL_FIRST_NAME
#else
    sender.toLower();
#endif

    // Check ignore list.
    BString loweredName = sender;
    loweredName.toLower();
    uint32 loweredNameCrc = loweredName.getCrc();

    while (iter != channel->getUserList()->end())
    {
        // If sender present at recievers ignore list, don't send.
        if ((*iter)->getPlayer()->checkIgnore(loweredNameCrc))
        {
            // Ignore player
        }
        else
        {

            DispatchClient* client = (*iter)->getPlayer()->getClient();

            if (client == NULL)
            {
                LOG(warning) << "sendChatRoomMessage: Client not found for channel " <<  channel->getId();
            }
            else
            {
                gMessageFactory->StartMessage();
                gMessageFactory->addUint32(opChatRoomMessage);

                gMessageFactory->addString(SWG);
                gMessageFactory->addString(galaxy);
                gMessageFactory->addString(sender);

                gMessageFactory->addUint32(channel->getId());
                gMessageFactory->addString(message);
                gMessageFactory->addUint32(0);
                Message* response = gMessageFactory->EndMessage();
                client->SendChannelA(response, client->getAccountId(), CR_Client, 5);

            }
        }
        ++iter;
    }
}