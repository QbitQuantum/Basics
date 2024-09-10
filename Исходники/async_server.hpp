  void start_listening() {
    using boost::asio::ip::tcp;
    system::error_code error;
    service_.reset();  // this allows repeated cycles of run -> stop ->
                       // run
    tcp::resolver resolver(service_);
    tcp::resolver::query query(address_, port_);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query, error);
    if (error) {
      BOOST_NETWORK_MESSAGE("Error resolving '" << address_ << ':' << port_);
      return;
    }
    tcp::endpoint endpoint = *endpoint_iterator;
    acceptor.open(endpoint.protocol(), error);
    if (error) {
      BOOST_NETWORK_MESSAGE("Error opening socket: " << address_ << ":"
                                                     << port_);
      return;
    }
    socket_options_base::acceptor_options(acceptor);
    acceptor.bind(endpoint, error);
    if (error) {
      BOOST_NETWORK_MESSAGE("Error binding socket: " << address_ << ":"
                                                     << port_);
      return;
    }
    acceptor.listen(asio::socket_base::max_connections, error);
    if (error) {
      BOOST_NETWORK_MESSAGE("Error listening on socket: '"
                            << error << "' on " << address_ << ":" << port_);
      return;
    }
    new_connection.reset(new connection(service_, handler, *thread_pool, ctx_));
    acceptor.async_accept(
#ifdef BOOST_NETWORK_ENABLE_HTTPS
        new_connection->socket().next_layer(),
#else
        new_connection->socket(),
#endif
        boost::bind(&async_server_base<Tag, Handler>::handle_accept, this,
                    boost::asio::placeholders::error));
    listening = true;
    scoped_mutex_lock stopping_lock(stopping_mutex_);
    stopping = false;  // if we were in the process of stopping, we revoke
                       // that command and continue listening
    BOOST_NETWORK_MESSAGE("Now listening on socket: '" << address_ << ":"
                                                       << port_ << "'");
  }