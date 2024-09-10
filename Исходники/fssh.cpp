	bool Parse(const char* commandLine)
	{
		_Cleanup();

		// init temporary arg/argv storage
		std::string currentArg;
		std::vector<std::string> argVector;

		fCurrentArg = &currentArg;
		fCurrentArgStarted = false;
		fArgVector = &argVector;

		for (; *commandLine; commandLine++) {
			char c = *commandLine;

			// whitespace delimits args and is otherwise ignored
			if (isspace(c)) {
				_PushCurrentArg();
				continue;
			}

			switch (c) {
				case '\'':
					// quoted string -- no quoting
					while (*++commandLine != '\'') {
						c = *commandLine;
						if (c == '\0') {
							fprintf(stderr, "Error: Unterminated quoted "
								"string.\n");
							return false;
						}
						_PushCharacter(c);
					}
					break;

				case '"':
					// quoted string -- some quoting
					while (*++commandLine != '"') {
						c = *commandLine;
						if (c == '\0') {
							fprintf(stderr, "Error: Unterminated quoted "
								"string.\n");
							return false;
						}

						if (c == '\\') {
							c = *++commandLine;
							if (c == '\0') {
								fprintf(stderr, "Error: Unterminated quoted "
									"string.\n");
								return false;
							}

							// only '\' and '"' can be quoted, otherwise the
							// the '\' is treated as a normal char
							if (c != '\\' && c != '"')
								_PushCharacter('\\');
						}

						_PushCharacter(c);
					}
					break;

				case '\\':
					// quoted char
					c = *++commandLine;
					if (c == '\0') {
						fprintf(stderr, "Error: Command line ends with "
							"'\\'.\n");
						return false;
					}
					_PushCharacter(c);
					break;

				default:
					// normal char
					_PushCharacter(c);
					break;
			}
		}

		// commit last arg
		_PushCurrentArg();

		// build arg vector
		fArgc = argVector.size();
		fArgv = new char*[fArgc + 1];
		for (int i = 0; i < fArgc; i++) {
			int len = argVector[i].length();
			fArgv[i] = new char[len + 1];
			memcpy(fArgv[i], argVector[i].c_str(), len + 1);
		}
		fArgv[fArgc] = NULL;

		return true;
	}