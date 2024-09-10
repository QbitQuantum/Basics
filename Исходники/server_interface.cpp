void ServerInterface::ConnectToStateServer(zmq::socket_t& stateSocket) const {
    std::cout << "Connecting to state server " << m_stateServer << std::endl;
    stateSocket.connect(m_stateServer.c_str());
    stateSocket.setsockopt(ZMQ_SUBSCRIBE, m_matchToken.c_str(), m_matchToken.size());
}