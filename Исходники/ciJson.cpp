		// POST JSON to URL
		string saveUrl(const Value & value, const string & url)
		{

			// Tokenize URL
			vector<string> tokens;
			boost::split(tokens, url, boost::is_any_of("/"));
			if (tokens.size() < 3)
				return "Invalid URL. Please include protocol.";

			// Get server portion of URL
			string server = tokens[2];

			// Remove server portion of URL
			for (int32_t i = 0; i < 3; i++)
				tokens.erase(tokens.begin());

			// Get action portion of URL
			string action = "";
			for (vector<string>::const_iterator tokenIt = tokens.begin(); tokenIt != tokens.end(); ++tokenIt)
				action += "/" + * tokenIt;

			// Serialize data
			string data = serialize(value);

			// Open Internet connection
			HINTERNET session = InternetOpenA("WinInetConnection", INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);
			if (session == NULL)
				return "Unable to establish Internet session.";

			// Open server
			HINTERNET connection = InternetConnectA(session, server.c_str(), INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
			if (connection == NULL)
				return "Unable to establish Internet connection.";

			// Open request flags
			DWORD mOpenRequestFlags = INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
				INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS |
				INTERNET_FLAG_KEEP_CONNECTION |
				INTERNET_FLAG_NO_AUTO_REDIRECT |
				INTERNET_FLAG_NO_COOKIES |
				INTERNET_FLAG_NO_CACHE_WRITE |
				INTERNET_FLAG_NO_UI |
				INTERNET_FLAG_RELOAD;

			// Open request
			HINTERNET request = HttpOpenRequestA(connection, "POST", action.c_str(), "HTTP/1.0", NULL, NULL, mOpenRequestFlags, 0);
			if (request == NULL)
				return "Unable to create request.";

			// Send request
			int_fast8_t buffer;
			DWORD size;
			string headers = "Content-Type: application/x-www-form-urlencoded";
			string response = "";
			if (HttpSendRequestA(request, headers.c_str(), headers.length(), (LPVOID)(data.c_str()), data.length()))
			{

				// Read request into buffer
				while (InternetReadFile(request, &buffer, 1, &size))
				{
					if (size != 1)
						break;
					response += buffer;
				}

			}

			// Close Internet handles
			InternetCloseHandle(request);
			InternetCloseHandle(connection);
			InternetCloseHandle(session);

			// Return response
			return response;

		}