void BuyingStoreRecv::processBuyingStoreReport(Net::MessageIn &msg)
{
    UNIMPLEMENTEDPACKET;
    msg.readInt16("item id");
    msg.readInt16("amount");
    if (msg.getVersion() >= 20141016)
    {
        msg.readInt32("money");
        msg.readInt32("money limit");
        msg.readInt32("char id");
        msg.readInt32("date");
    }
    else
    {
        msg.readInt32("money limit");
    }
}