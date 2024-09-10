bool Lounge::sendRoomlist(std::shared_ptr<
                          TBSystem::network::sockets::ITcpSocket>& socket,
                          std::string params) const
{
    std::string ret;

    ret  = "rep roomlist start\r\n";
    for (auto& r : _rooms) {
        if (!r.isInGame()) {
            ret += "rep roomlist room " + r.toString() + "\r\n";
        }
    }
    ret += "rep roomlist end\r\n";
    socket->send(ret.c_str(), ret.size());
    return true;
}