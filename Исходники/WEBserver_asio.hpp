	inline server::server(const std::string& address, 
			      const std::string& port,
			      std::size_t thread_pool_size, 
			      request_handler& request_handler_)
	    : thread_pool_size_(thread_pool_size),
	      acceptor_(io_service_),
	      new_connection_(new connection(io_service_, request_handler_)),
	      request_handler_(request_handler_)
	{
	    // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
	    boost::asio::ip::tcp::resolver resolver(io_service_);
	    boost::asio::ip::tcp::resolver::query query(address, port);
	    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	    acceptor_.open(endpoint.protocol());
	    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	    acceptor_.bind(endpoint);
	    acceptor_.listen();
	    acceptor_.async_accept(new_connection_->socket(),
				   boost::bind(&server::handle_accept, this,
					       boost::asio::placeholders::error));
	}