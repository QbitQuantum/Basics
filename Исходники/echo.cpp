void EchoServer::onConnection(const TcpConnectionPtr& conn){
    LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");

    if(conn->connected()){
        ++numConnected_;
        if(numConnected_ > kMaxConnections_){
            conn->shutdown();
            conn->forceCloseWithDelay(3.0); // > round trip of the whole Internet.
        }
    }else{
        --numConnected_;
    }
    LOG_INFO << "numConnected = " << numConnected_;
}