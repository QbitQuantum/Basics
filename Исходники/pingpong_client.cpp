void Session::onConnection(const TcpConnectionPtr& conn)
{
    if(conn->connected())
    {
        conn->setNoDelay(true);
        conn->send(owner_->message());
        owner_->onConnect();
    }
    else
    {
        owner_->onDisconnect(conn);
    }
}