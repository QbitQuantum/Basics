void Sys_Quit (qbool restart)
{
	if (restart)
	{
#ifndef __MINGW32__
		int maxfd = 131072; // well, should be enough for everyone...

		_set_invalid_parameter_handler(myInvalidParameterHandler); // so close() does not crash our program on invalid handle...

		// close all file descriptors even stdin stdout and stderr, seems that not hurt...
		for (; maxfd > -1; maxfd--)
		{
			close(maxfd);
			closesocket(maxfd); // yeah, windows separate sockets and files, so you can't close socket with close() like on *nix.
		}

		if (execv(argv[0], com_argv) == -1)
#endif
		{
#ifdef _CONSOLE
			if (!((int)sys_nostdout.value || isdaemon))
				printf("Restart failed: (%i): %s\n", qerrno, strerror(qerrno));
#else
			if (!(COM_CheckParm("-noerrormsgbox") || isdaemon))
				MessageBox(NULL, strerror(qerrno), "Restart failed", 0 /* MB_OK */ );
#endif
			Sys_Exit(1);
		}
	}
	Sys_Exit(0);
}