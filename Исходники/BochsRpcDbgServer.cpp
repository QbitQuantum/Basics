void _BochsRpcServer::Stop()
{
	if (!server_shutdown.exchange(true))
	{
		RpcMgmtStopServerListening(NULL);
		RpcServerUnregisterIf(NULL, NULL, FALSE);
		SetEvent(WorkingItemReadyEvent.get());
		//break the request processing wait
	}
}