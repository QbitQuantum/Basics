void ASIOConnectAndHandshake::connect(const ASIOConnectAndHandshakePtr &thus,
				      const std::tr1::shared_ptr<MultiplexedSocket>&connection,
                                      const Address&address,
                                      bool no_delay){
    tcp::resolver::query query(tcp::v4(), address.getHostName(), address.getService(), Network::TCPResolver::query::all_matching);
    thus->mResolver.async_resolve(
        query,
        connection->getStrand()->wrap(
            boost::bind(&ASIOConnectAndHandshake::handleResolve,
                thus,
                connection,
                address,
                no_delay,
                boost::asio::placeholders::error,
                boost::asio::placeholders::iterator)
        )
    );

}