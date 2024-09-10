void do_write(boost::asio::ip::tcp::socket& socket, boost::asio::yield_context yield)
{
    using namespace boost::asio::ip;

    std::time_t now = std::time(0);
    std::string data = std::ctime(&now);
    boost::asio::async_write(socket, boost::asio::buffer(data), yield);
    socket.shutdown(tcp::socket::shutdown_send);
}