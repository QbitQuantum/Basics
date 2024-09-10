void connect_handler(const boost::system::error_code &ec)
{
    if (!ec)
    {
        std::string r =
            "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
        write(tcp_socket, buffer(r));
        tcp_socket.async_read_some(buffer(bytes), read_handler);
    }
}