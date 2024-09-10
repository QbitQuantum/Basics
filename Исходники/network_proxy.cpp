void NetworkProxy::close_connection(const TcpConnectionPtr& connection)
{
    connection->shutdown();
    connection->close();
}