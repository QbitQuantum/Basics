int _flush_uart(int out, int in)
{
	DWORD dw;

	if(out=FDISCARD) PurgeComm(port, PURGE_TXCLEAR);
	else if(out) WaitCommEvent(port, &dw, NULL);
	if(in) PurgeComm(port, PURGE_RXCLEAR);

	return 0;
}