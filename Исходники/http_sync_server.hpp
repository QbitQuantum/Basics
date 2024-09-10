 http_sync_server(endpoint_type const& ep,
         std::string const& root)
     : sock_(ios_)
     , acceptor_(ios_)
     , root_(root)
 {
     acceptor_.open(ep.protocol());
     acceptor_.bind(ep);
     acceptor_.listen(
         boost::asio::socket_base::max_connections);
     acceptor_.async_accept(sock_,
         std::bind(&http_sync_server::on_accept, this,
             beast::asio::placeholders::error));
     thread_ = std::thread{[&]{ ios_.run(); }};
 }