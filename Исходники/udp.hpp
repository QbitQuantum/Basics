 ssize_t write(const std::string& message) {
     return m_socket->send(boost::asio::buffer(message.data(), message.size()));
 }