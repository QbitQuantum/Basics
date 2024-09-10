	// Conexion al servidor
	void handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator){
		debugOUT("handle_connect");
		if (!error){
			connected = true;
			debugOUT("Connected");

			boost::asio::async_read(socket_,
									boost::asio::buffer(receiveBuffer, transferAtLeast),
									boost::asio::transfer_at_least(transferAtLeast),
									boost::bind(&TCPClient::handle_read, this,
									boost::asio::placeholders::error,
									boost::asio::placeholders::bytes_transferred));

			debugOUT("async_read dispatched");
		}
		else if (endpoint_iterator != tcp::resolver::iterator()){
			debugOUT("Next Endpoint");
			// Conexion fallida, intentemos con el siguiente endpoint
			socket_.close();
			tcp::endpoint endpoint = *endpoint_iterator;
			
			socket_.async_connect(	endpoint,
									boost::bind(&TCPClient::handle_connect, this,
									boost::asio::placeholders::error, ++endpoint_iterator));
		}
		else{
			debugOUT("Error: " << error.message());
		}
	}