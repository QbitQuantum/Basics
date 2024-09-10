void ServerModule_Chargen::onTcpConnected(const TcpConnectionPtr& connection)
{
    logger().writeFmt("onTcpConnected (%s) (ConnCount: %d)",
        connection->getPeerAddr().getDisplayStr().c_str(),
        connection->getServerConnCount());

    connection->setNoDelay(true);

    connection->recv();
    connection->send(message_.c_str(), message_.length());
}