void GameRecv::processMapLogin(Net::MessageIn &msg)
{
    unsigned char direction;
    uint16_t x;
    uint16_t y;
    msg.readInt32("start time");
    msg.readCoordinates(x, y, direction, "position");
    msg.readInt8("x size");
    msg.readInt8("y size");
    logger->log("Protocol: Player start position: "
        "(%d, %d), Direction: %d",
        x, y, direction);
    if (msg.getVersion() >= 20080102)
        msg.readInt16("font");
    if (msg.getVersion() >= 20141022 && msg.getVersion() < 20160330)
        msg.readUInt8("sex");

    mLastHost &= 0xffffff;

    Network *const network = Network::mInstance;
    if (network != nullptr)
        network->pauseDispatch();

    // Switch now or we'll have problems
    client->setState(State::GAME);
    if (localPlayer != nullptr)
        localPlayer->setTileCoords(x, y);
}