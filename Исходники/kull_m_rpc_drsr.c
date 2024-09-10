void RPC_ENTRY kull_m_rpc_drsr_RpcSecurityCallback(void *Context)
{
	RPC_STATUS rpcStatus;
	SECURITY_STATUS secStatus;
	PCtxtHandle data = NULL;

	rpcStatus = I_RpcBindingInqSecurityContext(Context, (LPVOID *) &data);
	if(rpcStatus == RPC_S_OK)
	{
		if(kull_m_rpc_drsr_g_sKey.SessionKey)
		{
			FreeContextBuffer(kull_m_rpc_drsr_g_sKey.SessionKey);
			kull_m_rpc_drsr_g_sKey.SessionKeyLength = 0;
			kull_m_rpc_drsr_g_sKey.SessionKey = NULL;
		}
		secStatus = QueryContextAttributes(data, SECPKG_ATTR_SESSION_KEY, (LPVOID) &kull_m_rpc_drsr_g_sKey);
		if(secStatus != SEC_E_OK)
			PRINT_ERROR(L"QueryContextAttributes %08x\n", secStatus);
	}
	else PRINT_ERROR(L"I_RpcBindingInqSecurityContext %08x\n", rpcStatus);
}