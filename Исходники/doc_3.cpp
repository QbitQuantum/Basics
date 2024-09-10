	ShellWrapper()
	{
		int iReturn;
		iReturn = _pipe(iPipeIn_, 512, _O_TEXT | O_NOINHERIT);
		assert(iReturn != -1);
		iReturn = _pipe(iPipeOut_, 512, _O_TEXT | O_NOINHERIT);
		assert(iReturn != -1);

		//save old handle
		int iStdin = _dup(_fileno(stdin));
		int iStdout = _dup(_fileno(stdout));
		int iStderr = _dup(_fileno(stderr));

		iReturn = _dup2(iPipeOut_[0], _fileno(stdin));
		assert(iReturn == 0);
		iReturn = _dup2(iPipeIn_[1], _fileno(stdout));
		assert(iReturn == 0);
		iReturn = _dup2(iPipeIn_[1], _fileno(stderr));
		assert(iReturn == 0);

		char *arg[] = {"cmd.exe", "/Q", "/A", NULL};
		iSubProcess_ = spawnvp(P_NOWAIT, arg[0], arg);

		//restore old handle
		iReturn = _dup2(iStdin, _fileno(stdin));
		iReturn = _dup2(iStdout, _fileno(stdout));
		iReturn = _dup2(iStderr, _fileno(stderr));
	}