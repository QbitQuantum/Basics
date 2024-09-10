static void installsighandler()
{
	#ifndef _WIN32
		signal(SIGHUP,sighandler);
		signal(SIGUSR1,sighandler);
		signal(SIGPIPE,sighandler);
	#endif
	signal(SIGINT,sighandler);
	#ifdef _WIN32
		SetConsoleCtrlHandler(ConsoleCtrlHandler,true);
		HANDLE hs=GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		if (GetConsoleMode(hs,&mode)) {
			mode|=ENABLE_PROCESSED_INPUT;
			SetConsoleMode(hs,mode);
		};
	#endif
}