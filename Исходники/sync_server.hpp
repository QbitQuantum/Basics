 void start_listening() {
   using boost::asio::ip::tcp;
   system::error_code error;
   tcp::resolver resolver(service_);
   tcp::resolver::query query(address_, port_);
   tcp::resolver::iterator endpoint_iterator = resolver.resolve(query, error);
   if (error) {
     BOOST_NETWORK_MESSAGE("Error resolving address: " << address_ << ':'
                                                       << port_);
     boost::throw_exception(std::runtime_error("Error resolving address."));
   }
   tcp::endpoint endpoint = *endpoint_iterator;
   acceptor_.open(endpoint.protocol(), error);
   if (error) {
     BOOST_NETWORK_MESSAGE("Error opening socket: " << address_ << ':' << port_
                                                    << " -- reason: '" << error
                                                    << '\'');
     boost::throw_exception(std::runtime_error("Error opening socket."));
   }
   socket_options_base::acceptor_options(acceptor_);
   acceptor_.bind(endpoint, error);
   if (error) {
     BOOST_NETWORK_MESSAGE("Error binding to socket: "
                           << address_ << ':' << port_ << " -- reason: '"
                           << error << '\'');
     boost::throw_exception(std::runtime_error("Error binding to socket."));
   }
   acceptor_.listen(tcp::socket::max_connections, error);
   if (error) {
     BOOST_NETWORK_MESSAGE("Error listening on socket: "
                           << address_ << ':' << port_ << " -- reason: '"
                           << error << '\'');
     boost::throw_exception(std::runtime_error("Error listening on socket."));
   }
   new_connection.reset(new sync_connection<Tag, Handler>(service_, handler_));
   auto self = this->shared_from_this();
   acceptor_.async_accept(
       new_connection->socket(),
       [=] (boost::system::error_code const &ec) { self->handle_accept(ec); });
   listening_ = true;
 }