void fileXio_Thread(void* param)
{
	int OldState;

	printf("fileXio: fileXio RPC Server v1.00\nCopyright (c) 2003 adresd\n");
	#ifdef DEBUG
		printf("fileXio: RPC Initialize\n");
	#endif

	SifInitRpc(0);

	RWBufferSize=DEFAULT_RWSIZE;
	CpuSuspendIntr(&OldState);
	rwbuf = AllocSysMemory(ALLOC_FIRST, RWBufferSize, NULL);
	CpuResumeIntr(OldState);
	if (rwbuf == NULL)
	{
		#ifdef DEBUG
  			printf("Failed to allocate memory for RW buffer!\n");
		#endif

		SleepThread();
	}

	SifSetRpcQueue(&qd, GetThreadId());
	SifRegisterRpc(&sd0, FILEXIO_IRX, &fileXio_rpc_server, fileXio_rpc_buffer, NULL, NULL, &qd);
	SifRpcLoop(&qd);
}