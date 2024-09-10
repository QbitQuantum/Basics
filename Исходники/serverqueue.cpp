Protocol::Packet *ServerQueue::getNextPacket() {
    static int sentCt = 0;
    if(sentCt == 0) {
        updateWindow();
        std::cout << "refreshing output packet window!" << std::endl;
    }

    Protocol::Packet *rtnPacket = NULL;
    if(window.size() > sentCt) {
        rtnPacket = window.at(sentCt++)->packet;
        sentCt = sentCt%window.size();
    }

    return rtnPacket;
}