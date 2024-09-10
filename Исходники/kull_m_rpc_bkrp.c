BOOL kull_m_rpc_bkrp_generic(LPCWSTR NetworkAddr, const GUID * pGuid, PVOID DataIn, DWORD dwDataIn, PVOID *pDataOut, DWORD *pdwDataOut)
{
	BOOL status = FALSE;
	RPC_BINDING_HANDLE hBinding;
	NET_API_STATUS netStatus;
	PBYTE out = NULL;
	*pDataOut = NULL;
	*pdwDataOut = 0;
	if(kull_m_rpc_bkrp_createBinding(NetworkAddr, &hBinding))
	{
		RpcTryExcept
		{
			netStatus = BackuprKey(hBinding, (GUID *) pGuid, (PBYTE) DataIn, dwDataIn, &out, pdwDataOut, 0);
			if(status = (netStatus == 0))
			{
				if(*pDataOut = LocalAlloc(LPTR, *pdwDataOut))
					RtlCopyMemory(*pDataOut, out, *pdwDataOut);
				MIDL_user_free(out);
			}
			else PRINT_ERROR(L"BackuprKey: 0x%08x (%u)\n", netStatus, netStatus);
		}
		RpcExcept(RPC_EXCEPTION)
			PRINT_ERROR(L"RPC Exception: 0x%08x (%u)\n", RpcExceptionCode(), RpcExceptionCode());
		RpcEndExcept
			kull_m_rpc_deleteBinding(&hBinding);
	}