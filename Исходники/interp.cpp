	int32 Interp::runScript(char* script, uint32 size, void* context)
	{
		char* buf = script, * line = NULL;
		char* token = NULL, * param_string = NULL;
		int32 out = 0, current_line = 0, ret = 0, k = 0;

		while (1) {
			line = Utils::getToken(&buf, CRLF, size, 2);
			if (!line)
				break;

			/* remove '\n' and blanks */
			out = (int32) strlen(line);
			while (--out && isspace(toascii(line[out])))
				line[out] = 0;

			/* remove blanks */
			k = (int32) strlen(line);
			while (k && isspace(toascii(*line))) {
				k--; line++;
			}

			/* remove empty lines and comments */
			if (line[0] == '#' || line[0] == '\0') {
				current_line++; continue;
			}

			/* execute instruction */
			param_string = line;
			token = Utils::getToken(&param_string, " \t");
			if (token)
				ret = run(token, param_string, context);
			else {
				current_line++; continue;
			}

			/* get return value */
			switch (ret) {
			case Interp::BADCOMMAND:
			case Interp::PARAMPARSINGERROR:
			case Interp::WRONGPARAMCOUNT:
			case Interp::PERMISSIONDENIED:
				sysHandler(token, current_line, ret, context);
				return FAILURE;
			default:
				usrHandler(token, current_line, ret, context);
			}

			current_line++;
		}

		return SUCCESS;
	}