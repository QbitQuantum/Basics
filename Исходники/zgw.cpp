void ZGWServer::onClientConnection(const TcpConnectionPtr& conn)
{
    LOG_INFO << "Client " << conn->peerAddress().toIpPort() << " -> "
        << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");

    if( conn->connected() )
    {
        int id = -1;
        if( !idQueue_.empty() )
        {
            id = idQueue_.front();
            idQueue_.pop();
            id2conn_[id] = conn;
        }

        if( -1 == id )
        {
            LOG_ERROR << "[过载保护]系统到达最大连接数，拒绝连接";
            conn->shutdown();
        }
        else
        {
            conn->setContext(id);
            LOG_INFO << "新连接[" << conn->peerAddress().toIpPort() << "]流水ID: " << id;
        }
    }
    else
    {
        if(!conn->getContext().empty())
        {
            int id = boost::any_cast<int>(conn->getContext());
            assert(id > 0 && id <= static_cast<int>(kMaxConns));

            // 回收连接的key
            idQueue_.push(id);
            id2conn_.erase(id);
        }
    }
}