/*!
  Listen a port for connections on a socket.
  This function must be called in a tfmanager process.
 */
int TApplicationServerBase::nativeListen(const QHostAddress &address, quint16 port, OpenFlag flag)
{
    int sd = 0;
    QTcpServer server;

    if (!server.listen(address, port)) {
        tSystemError("Listen failed  port:%d", port);
        return sd;
    }

    sd = duplicateSocket(server.socketDescriptor()); // duplicate

    if (flag == CloseOnExec) {
        ::fcntl(sd, F_SETFD, ::fcntl(sd, F_GETFD) | FD_CLOEXEC);
    } else {
        ::fcntl(sd, F_SETFD, 0);  // clear
    }
    ::fcntl(sd, F_SETFL, ::fcntl(sd, F_GETFL) | O_NONBLOCK);  // non-block

    server.close();
    return sd;
}