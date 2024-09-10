// TODO: Put in common file
static
std::tuple<Socket, SocketError> getAcceptingSocket(const SockAddr& sockAddr) {
    Socket socket;
    SocketError err = socket.init(sockAddr.getFamily());
    if (err != SocketError::Ok) {
        return std::make_tuple(Socket(), err);
    }

    err = socket.bind(sockAddr);
    if (err != SocketError::Ok) {
        return std::make_tuple(Socket(), err);
    }

    err = socket.listen();
    if (err != SocketError::Ok) {
        return std::make_tuple(Socket(), err);
    }

    return std::make_tuple(std::move(socket), SocketError::Ok);
}