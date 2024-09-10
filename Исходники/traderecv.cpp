void TradeRecv::processTradeRequest(Net::MessageIn &msg)
{
    const std::string &partner = msg.readString(24, "name");
    if (msg.getVersion() >= 6)
    {
        msg.readInt32("char id");
        msg.readInt16("base level");
    }
    Ea::TradeRecv::processTradeRequestContinue(partner);
}