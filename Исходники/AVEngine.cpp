//------------------------------------------------------------------
DWORD WINAPI AVEngine::SetupRPCServer(void* lpParam)
{
	RPC_STATUS status;
	PutLog(CALLING_RPCSERVERLISTEN);
	status = RpcMgmtWaitServerListen();  // wait operation
	if (status != RPC_S_OK)
	{
		PutLog(RPCMGMTWAITSERVERLISTEN_FAILD);
		return FALSE;
	}
	return TRUE;		
}