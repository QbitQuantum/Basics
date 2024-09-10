void RS232Interface::WaitForTxEmpty()
{
#ifdef	_WINDOWS
	DWORD evento;

	if ( hCom != INVALID_HANDLE_VALUE)
	{
		do {
			WaitCommEvent(hCom, &evento, NULL);
		} while ( !(evento & EV_TXEMPTY) );
	}
#endif
#ifdef	_LINUX_
	if ( fd != INVALID_HANDLE_VALUE )
		tcdrain(fd);
#endif
}