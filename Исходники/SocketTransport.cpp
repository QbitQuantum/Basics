void SocketConnector::connect(
    boost::shared_ptr<Poller> poller,
    const std::string& name,
    const std::string& host, const std::string& port,
    ConnectionCodec::Factory* fact,
    ConnectFailedCallback failed)
{
    // Note that the following logic does not cause a memory leak.
    // The allocated Socket is freed either by the AsynchConnector
    // upon connection failure or by the AsynchIO upon connection
    // shutdown.  The allocated AsynchConnector frees itself when it
    // is no longer needed.
    Socket* socket = factory();
    try {
        AsynchConnector* c = AsynchConnector::create(
            *socket,
            host,
            port,
            boost::bind(&establishedOutgoing, poller, options, &timer, _1, fact, name),
            boost::bind(&connectFailed, _1, _2, _3, failed));
        c->start(poller);
    } catch (std::exception&) {
        // TODO: Design question - should we do the error callback and also throw?
        int errCode = socket->getError();
        connectFailed(*socket, errCode, strError(errCode), failed);
        throw;
    }
}