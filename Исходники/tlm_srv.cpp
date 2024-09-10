int main(int argc, char *argv[]) {
	// TCP server
	TCPStream *stream = NULL;
	TCPAcceptor *acceptor = NULL;

	if (argc != 1) {
		usage(argv);
		return -1;
	}

	initCommandMap();

	acceptor = new TCPAcceptor(TCP_PORT);
	if (acceptor->start() != 0) {
		cerr << LOG_PREFIX "Could not start TCPAcceptor" << endl;
		return -1;
	}

	cout << LOG_PREFIX "Initialized TLM Server" << endl;
	while(1) {
		cout << LOG_PREFIX "Waiting for connection." << endl;
		stream = acceptor->accept();
		cout << LOG_PREFIX "Connection Accepted, sending telemetry. " << endl;
			if (stream != NULL) {
				ssize_t len;
				char line[256];
				string retval;
				const char *txstr;
				while ((len = stream->receive(line, sizeof(line))) > 0) {
					line[len] = 0;
					retval = parse(line);
					txstr = retval.c_str();
					stream->send(txstr, retval.length());
				}
			delete stream;
			cout << LOG_PREFIX "Connection closed." << endl;
		}
	}
	delete acceptor;

	return 0;
}