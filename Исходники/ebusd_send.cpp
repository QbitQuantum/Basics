int main(int argc, char* argv[])
{
	// define Arguments and Application variables
	define_args();

	// parse Arguments
	if (A.parseArgs(argc, argv) == false) {
		A.printArgs();
		exit(EXIT_FAILURE);
	}

	// print Help
	if (A.getParam<bool>("p_help") == true) {
		A.printArgs();
		exit(EXIT_SUCCESS);
	}

	TCPClient* client = new TCPClient();
	TCPSocket* socket = client->connect(A.getParam<const char*>("p_server"), A.getParam<int>("p_port"));

	if (socket != NULL) {
		// build message
		std::string message(A.getArg(0));
		for (size_t i = 1; i < A.numArg(); i++) {
			message += " ";
			message += A.getArg(i);
		}

		socket->send(message.c_str(), message.size());

		char data[1024];
		size_t datalen;

		datalen = socket->recv(data, sizeof(data)-1);
		data[datalen] = '\0';

		std::cout << data;

		delete socket;
	}

	delete client;

	return 0;

}