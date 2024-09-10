void PartyRecv::processPartySettings(Net::MessageIn &msg)
{
    if (partyTab == nullptr)
    {
        if (chatWindow == nullptr)
            return;

        Ea::PartyRecv::createTab();
    }

    const PartyShareT exp = static_cast<PartyShareT>(
        msg.readInt32("party exp"));
    Ea::PartyRecv::processPartyExpSettingsContinue(msg, exp);
    if (msg.getVersion() >= 20090603)
    {
        const PartyShareT item = static_cast<PartyShareT>(
            msg.readInt8("pickup item share (&1)"));
        Ea::PartyRecv::processPartyItemSettingsContinue(msg, item);
        const PartyShareT autoItem = static_cast<PartyShareT>(
            msg.readInt8("get auto item share (&2)"));
        processPartyAutoItemSettingsContinue(msg, autoItem);
    }
}