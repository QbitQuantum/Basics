void ServerModule_Daytime::onTcpConnected(const TcpConnectionPtr& connection)
{
    logger().writeFmt("onTcpConnected (%s) (ConnCount: %d)",
                      connection->getPeerAddr().getDisplayStr().c_str(),
                      connection->getServerConnCount());

    string msg = DateTime::now().toDateTimeString() + "\n";
    connection->send(msg.c_str(), msg.length());
}