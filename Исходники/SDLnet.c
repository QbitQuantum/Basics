void SDLNet_Quit(void)
{
	if ( SDLNet_started == 0 ) {
		return;
	}
	if ( --SDLNet_started == 0 ) {
#ifdef __USE_W32_SOCKETS
		/* Clean up windows networking */
		if ( WSACleanup() == SOCKET_ERROR ) {
			if ( WSAGetLastError() == WSAEINPROGRESS ) {
				WSACancelBlockingCall();
				WSACleanup();
			}
		}
#else
#ifdef __CELLOS_LV2__ /* kill the stack */
		sys_net_finalize_network();
	        cellSysmoduleUnloadModule(CELL_SYSMODULE_NET);
#endif
#ifndef __CELLOS_LV2__ /* No signals on cell */
		/* Restore the SIGPIPE handler */
		void (*handler)(int);
		handler = signal(SIGPIPE, SIG_DFL);
		if ( handler != SIG_IGN ) {
			signal(SIGPIPE, handler);
		}
#endif
#endif
	}
}