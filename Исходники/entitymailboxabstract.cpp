//-------------------------------------------------------------------------------------
bool EntityMailboxAbstract::postMail(Network::Bundle* pBundle)
{
    KBE_ASSERT(Components::getSingleton().pNetworkInterface() != NULL);
    Network::Channel* pChannel = getChannel();

    if(pChannel && !pChannel->isDead())
    {
        pChannel->send(pBundle);
        return true;
    }
    else
    {
        ERROR_MSG(fmt::format("EntityMailboxAbstract::postMail: invalid channel({})!\n",
                              addr_.c_str()));
    }

    Network::Bundle::ObjPool().reclaimObject(pBundle);
    return false;
}