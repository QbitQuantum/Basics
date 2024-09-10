std::vector<zmq::message_t> CentralProxy::receive_multipart(zmq::socket_t& socket_fe)
{
    std::vector<zmq::message_t> message;
    bool more = true;
    while (more)
    {
        message.push_back(zmq::message_t());
        zmq::message_t& msg = message.back();
        socket_fe.recv(&msg);
        more = msg.more();
    }
    return message;
}