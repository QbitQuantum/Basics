static int tp_npipe_open(pbRPCTransportContext* context, int timeout)
{
	HANDLE hNamedPipe = 0;
	char pipeName[] = "\\\\.\\pipe\\FreeRDS_SessionManager";
	NpTransportContext *np = (NpTransportContext *) context;

	if (!WaitNamedPipeA(pipeName, timeout))
	{
		return -1;
	}
	hNamedPipe = CreateFileA(pipeName,
			GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if ((!hNamedPipe) || (hNamedPipe == INVALID_HANDLE_VALUE))
	{
		return -1;
	}
	np->handle = hNamedPipe;
	return 0;
}