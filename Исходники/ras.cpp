void parseCmd(const char **strptr)
{
	// Parse Executable Filename
	char exe[MAX_CMD_SIZE + 1] = "";
	char path[MAX_CMD_SIZE + 1] = "";
	bool exeValid;

	PARSE_ASSERT(getToken(exe, strptr) == IDENTIFIER);
	exeValid = getPath(path, exe);
	if (!exeValid) {
		char msg[MAX_CMD_SIZE + 30];

		sprintf(msg, "Unknown command: [%s].", exe);
		throw std::string(msg);
	}
	

	// Parse Arguments
	int num_arg = 0;
	char *arg[16];
	while (peekToken(*strptr) == IDENTIFIER) {
		arg[num_arg] = new char[MAX_CMD_SIZE + 1];
		getToken(arg[num_arg++], strptr);
	}

	// Parse Pipe to File
	bool pipeToFile = false;
	char file[MAX_CMD_SIZE + 1];
	if (peekToken(*strptr) == OUT) {
		pipeToFile = true;
		getToken(NULL, strptr);	// '>'
		PARSE_ASSERT(getToken(file, strptr) == IDENTIFIER);
	}

	// Parse Pipe
	bool pipe = false;
	bool pipenum = false;
	int pipenumCount;
	if (peekToken(*strptr) == PIPE) {
		getToken(NULL, strptr); // '|'
		
		/*
		// Test whether this is the last process
		char nextCmdName[MAX_CMD_SIZE + 1];
		Token token;
		char temp[MAX_CMD_SIZE + 1];
		token = peekToken(*strptr, nextCmdName);
		if (token == END || 
			token == IDENTIFIER && !getPath(temp, nextCmdName))
		{
			// Consider '|' as '|1'
			pipenum = true;
			pipenumCount = 1;
		}
		else {
		*/
			pipe = true;
		//}
	}

	// Parse Pipenum 
	if (peekToken(*strptr) == PIPENUM) {
		char temp[MAX_CMD_SIZE + 1];
		pipenum = true;
		getToken(temp, strptr); // '|?'
		pipenumCount = atoi(temp + 1);
	}

	// Parse Pipeerrnum
	bool pipeerrnum = false;
	int pipeerrnumCount;
	if (peekToken(*strptr) == PIPEERRNUM) {
		char temp[MAX_CMD_SIZE + 1];
		pipeerrnum = true;
		getToken(temp, strptr); // '!?'
		pipeerrnumCount = atoi(temp + 1);	
	}

	// Parse Pipenum again if !? exists
	if (!pipenum && pipeerrnum) {
		if (peekToken(*strptr) == PIPENUM) {
			char temp[MAX_CMD_SIZE + 1];
			pipenum = true;
			getToken(temp, strptr); // '|?'
			pipeerrnumCount = atoi(temp + 1);
		}
	}

	// Some assertions
	PARSE_ASSERT(pipeToFile + pipe + pipenum <= 1); // No multiple outputs

	// Execute
	executeCmd(exe, path, num_arg, (const char **)arg, pipeToFile, file, pipe, 
		pipenum, pipenumCount, pipeerrnum, pipeerrnumCount);

	// Release Argument List
	for (int i = 0; i < num_arg; i++) {
		delete [] arg[i];
	}
}