void receiving()
{

	mi_socket_server.async_receive_from(
	        boost::asio::buffer(recv_buffer), remote_endpoint,
	        boost::bind(&mi_udp_server::handler, this,
	        boost::asio::placeholders::error,
	        boost::asio::placeholders::bytes_transferred));

}