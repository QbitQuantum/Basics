iocp::error_code socket_ops::recv(iocp::socket &socket,
                                  char *buffer, unsigned int &len)
{
    iocp::service &service = socket.service();
    return service.recv(socket.socket_, buffer, len);
}