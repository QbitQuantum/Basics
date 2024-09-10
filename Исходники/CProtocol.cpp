void CProtocol::on_receive_reply(const system::error_code& error, std::size_t bytes) {
	cmd_response_[bytes] = 0;
	std::string reply(cmd_response_);

	std::cout << "<- " << reply << std::endl;
	if (bytes != active_command_.expected_sizeof_reply())
		return;
	if(running_)
		active_command_.handle_reply(reply);
//		signal command finished
	command_ready_ = true;
	if(error != 0)
		std::cout << "on_receive_reply error: " << error << " message: "<< error.message() << " bytes: " << bytes << std::endl;
}