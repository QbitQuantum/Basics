void AppBusiness::onTcpRecvComplete(const TcpConnectionPtr& connection, void *packetBuffer,
    int packetSize, const Context& context)
{
    string msg((const char*)packetBuffer, packetSize);

    logger().writeFmt("[%s] Discarded %u bytes.",
        connection->getConnectionName().c_str(), packetSize);

    std::cout << msg;

    connection->recv();
}