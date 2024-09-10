//-----------------------------------------------------------------------------
// 描述: 接受了一个新的TCP连接
//-----------------------------------------------------------------------------
void AppBusiness::onTcpConnected(const TcpConnectionPtr& connection)
{
    logger().writeFmt("onTcpConnected (%s) (ConnCount: %d)",
        connection->getPeerAddr().getDisplayStr().c_str(),
        connection->getServerConnCount());

    //string msg = "Welcome to the simple echo server, type 'quit' to exit.\r\n";

	//ConnetManager::instance().add(connection);

    connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT);
}