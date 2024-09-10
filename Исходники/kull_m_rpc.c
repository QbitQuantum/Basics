BOOL kull_m_rpc_Generic_Decode(PVOID data, DWORD size, PVOID pObject, PGENERIC_RPC_DECODE fDecode)
{
	BOOL status = FALSE;
	RPC_STATUS rpcStatus;
	PVOID buffer;
	KULL_M_RPC_FCNSTRUCT UserState ;
	handle_t pHandle;

	if(buffer = UserState.addr = LocalAlloc(LPTR, size))
	{
		UserState.size = size;
		RtlCopyMemory(UserState.addr, data, size); // avoid data alteration
		rpcStatus = MesDecodeIncrementalHandleCreate(&UserState, ReadFcn, &pHandle);
		if(NT_SUCCESS(rpcStatus))
		{
			rpcStatus = MesIncrementalHandleReset(pHandle, NULL, NULL, NULL, NULL, MES_DECODE);
			if(NT_SUCCESS(rpcStatus))
			{
				RpcTryExcept
				{
					fDecode(pHandle, pObject);
					status = TRUE;
				}
				RpcExcept(EXCEPTION_EXECUTE_HANDLER)
					PRINT_ERROR(L"RPC Exception: 0x%08x (%u)\n", RpcExceptionCode(), RpcExceptionCode());
				RpcEndExcept
			}
			else PRINT_ERROR(L"MesIncrementalHandleReset: %08x\n", rpcStatus);
			MesHandleFree(pHandle);
		}