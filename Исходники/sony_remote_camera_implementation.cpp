void Sony_Remote_Camera_Implementation::Handle_Write_HTTP_Request(bool mode_liveview, bool event_thread, const system::error_code& err) {
	asio::ip::tcp::socket& s = mode_liveview ? socket_liveview : (event_thread ? socket_event_listener : socket_options);
	asio::streambuf& buf = mode_liveview ? tcp_response_liveview : (event_thread ? tcp_response_events : tcp_response_options);
	if (!err) {
		boost::asio::async_read_until(s, buf, "\r\n",
			boost::bind(&Sony_Remote_Camera_Implementation::Handle_Read_Status_Line, this, mode_liveview, event_thread,
			boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	} else {
		throw(ios_base::failure(err.message()));
	}
}