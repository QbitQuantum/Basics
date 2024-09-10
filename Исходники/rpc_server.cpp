DWORD WINAPI start_gdipp_rpc_server(LPVOID lpParameter)
{
	if (process_heap == NULL)
		return 1;

	//bool b_ret;
	RPC_STATUS rpc_status;

	scoped_rw_lock::initialize();
	server_cache_size = min(config_instance.get_number(L"/gdipp/server/cache_size/text()", server_config::CACHE_SIZE), 24);
	glyph_cache_instance.initialize();
	initialize_freetype();

	//b_ret = rpc_index_initialize();
	//if (!b_ret)
	//	return 1;

	rpc_status = RpcServerUseProtseqEpW(reinterpret_cast<RPC_WSTR>(L"ncalrpc"), RPC_C_PROTSEQ_MAX_REQS_DEFAULT, reinterpret_cast<RPC_WSTR>(L"gdipp"), NULL);
	if (rpc_status != RPC_S_OK)
		return 1;

	rpc_status = RpcServerRegisterIf(gdipp_rpc_v1_0_s_ifspec, NULL, NULL);
	if (rpc_status != RPC_S_OK)
		return 1;

	rpc_status = RpcServerListen(1, RPC_C_LISTEN_MAX_CALLS_DEFAULT, TRUE);
	if (rpc_status != RPC_S_OK)
		return 1;

	rpc_status = RpcMgmtWaitServerListen();
	if (rpc_status != RPC_S_OK)
		return 1;

	return 0;
}