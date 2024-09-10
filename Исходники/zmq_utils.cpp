bool send (zmq::socket_t & socket, std::string const& string) 
{
    zmq::message_t message(string.size());
    std::memcpy(message.data(), string.data(), string.size());
    bool rc = socket.send(message);
    return (rc);
}