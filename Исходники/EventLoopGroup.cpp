std::shared_ptr<UdpSocket>
EventLoopGroup::creatUdpServer(const std::string &host,
                               const std::string &service) {
    auto eps = Resolver::resolve(host, service);
    if (eps.empty()) {
        error("host or service unavaiable");
        return nullptr;
    }

    SockPtr sockPtr = std::make_shared<Socket>(eps.front(), true);
    sockPtr->listen();

    std::shared_ptr<UdpSocket> udpSocket =
        std::make_shared<UdpSocket>(ploops_[0], sockPtr);
    udpSocket->start();

    return udpSocket;
}