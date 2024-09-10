unsigned int __stdcall CUDA_WRAPPER::WinThreadListener(void * wrapper)
{
	CUDA_WRAPPER * cu = (CUDA_WRAPPER *) wrapper;

	for (;;)
	{
		RPC_STATUS status;

		// Uses the protocol combined with the endpoint for receiving
		// remote procedure calls.
		status = RpcServerUseProtseqEp(
			(RPC_WSTR)_T("ncacn_ip_tcp"),// Use TCP/IP protocol
			RPC_C_PROTSEQ_MAX_REQS_DEFAULT,    // Backlog q length for TCP/IP.
			(RPC_WSTR)_T("9191"),    // TCP/IP port to use.
			NULL);       // No security.

		if(status)
		{
			_endthreadex(status);
			return status;
		}

		// Registers the DoRPC interface.
		status = RpcServerRegisterIf(
			DoRPC_v1_0_s_ifspec, // Interface to register.
			NULL,   // Use the MIDL generated entry-point vector.
			NULL);   // Use the MIDL generated entry-point vector.

		if(status)
		{
			_endthreadex(status);
			return status;
		}

		// Start to listen for remote procedure calls for all registered interfaces.
		// This call will not return until RpcMgmtStopServerListening is called.
		status = RpcServerListen(
			1,       // Recommended minimum number of threads.
			RPC_C_LISTEN_MAX_CALLS_DEFAULT,  // Recommended maximum number of threads.
			FALSE);              // Start listening now.

		if(status)
		{
			_endthreadex(status);
			return status;
		}
	}

	return 0;
}