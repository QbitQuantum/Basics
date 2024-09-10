void BattleGroundRecv::processBattleUpdateHp(Net::MessageIn &msg)
{
    UNIMPLEMENTEDPACKET;
    msg.readBeingId("account id");
    if (msg.getVersion() >= 20140613)
    {
        msg.readInt32("hp");
        msg.readInt32("max hp");
    }
    else
    {
        msg.readString(24, "name");
        msg.readInt16("hp");
        msg.readInt16("max hp");
    }
}