void c_netuser::server_read(ip::tcp::socket socket_) {
	DBG_MTX(dbg_mtx, "START");
	assert(socket_.is_open());
    boost::system::error_code ec;
    DBG_MTX(dbg_mtx,"server read");
	while (!ec && !m_stop_flag) {
		char header[2] = {0, 0};
		socket_.read_some(buffer(header, 2), ec);
		if (header[0] == 'p' && header[1] == 'k') {
			send_public_key_resp(socket_);
		}
		else if (header[0] == '$' && header[1] == 't') {
			std::string coin_data = recv_coin(socket_);
			recieve_from_packet(coin_data);
		}
	}
	socket_.close();
}