void connect(const char* host, uint16_t port, char* const *args, int argCount)
{

	TCPClient* client = new TCPClient();
	TCPSocket* socket = client->connect(host, port);

	bool once = args != NULL && argCount > 0;
	if (socket != NULL) {
		do {
			string message;
			bool listening = false;

			if (!once) {
				cout << host << ": ";
				getline(cin, message);
			}
			else {
				for (int i = 0; i < argCount; i++) {
					if (i > 0)
						message += " ";
					bool quote = strchr(args[i], ' ') != NULL && strchr(args[i], '"') == NULL;
					if (quote)
						message += "\"";
					message += args[i];
					if (quote)
						message += "\"";
				}
			}

			message += '\n';
			socket->send(message.c_str(), message.size());

			if (strcasecmp(message.c_str(), "Q") == 0
			|| strcasecmp(message.c_str(), "QUIT") == 0
			|| strcasecmp(message.c_str(), "STOP") == 0)
				break;

			if (message.length() > 0) {
				if (strcasecmp(message.c_str(), "L") == 0
				|| strcasecmp(message.c_str(), "LISTEN") == 0) {
					listening = true;
					while (listening && !cin.eof()) {
						string result(fetchData(socket, listening));
						cout << result;
						if (strcasecmp(result.c_str(), "LISTEN STOPPED") == 0)
							break;
					}
				}
				else
					cout << fetchData(socket, listening);
			}

		} while (!once && !cin.eof());

		delete socket;

	}
	else
		cout << "error connecting to " << host << ":" << port << endl;

	delete client;
}