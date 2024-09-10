void peerListener::listen(){
    int timer = 0;
    messageReader* mr = new messageReader(peer, "");
    TCPAcceptor* acceptor = new TCPAcceptor(peer->port, peer->address.c_str(), false, false, true);
    if (acceptor->start() == 0) {
        while (timer < mainTimer) {
            TCPStream* stream = acceptor->accept();
            if (stream != NULL) {
                mr->readMsg(stream);
                PeerHandler* ph = new PeerHandler(peer, stream, peer->tmpPeerName);
                ph->start();
                peer->peerHandlers[peer->tmpPeerName]= ph;
            }
            sleep(1);
            timer += 1;
        }
    }
    delete mr;
    delete acceptor;
}