		void EthernetRelayDriver::configure(std::string host, int port){

			tcp::endpoint endpoint(boost::asio::ip::address::from_string(host.c_str()), port);
			socket.connect(endpoint);

			if(socket.is_open()){
				ROS_INFO("TCP/IP socket opened.");
			}
		}