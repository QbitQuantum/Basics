bool PreGame::read(
		std::shared_ptr<TBSystem::network::sockets::ITcpSocket> &socket)
{
	char msg[155];
	int ret;

	try {
		ret = socket->recv(msg, 154);
	} catch (std::runtime_error &e) {
		TBSystem::log::err << e.what() << TBSystem::log::endl;
		return (false);
	}
	if (!ret) {
		return (false);
	}
	handleMsg(std::string(msg));
	return (true);
}