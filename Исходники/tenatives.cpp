static cell_t smn_TESend(IPluginContext *pContext, const cell_t *params)
{
	if (!g_TEManager.IsAvailable())
	{
		return pContext->ThrowNativeError("TempEntity System unsupported or not available, file a bug report");
	}
	if (!g_CurrentTE)
	{
		return pContext->ThrowNativeError("No TempEntity call is in progress");
	}

	cell_t *cl_array;
	unsigned int numClients;
	int client;
	IGamePlayer *pPlayer = NULL;

	pContext->LocalToPhysAddr(params[1], &cl_array);
	numClients = params[2];

	/* Client validation */
	for (unsigned int i = 0; i < numClients; i++)
	{
		client = cl_array[i];
		pPlayer = playerhelpers->GetGamePlayer(client);

		if (!pPlayer)
		{
			return pContext->ThrowNativeError("Client index %d is invalid", client);
		} else if (!pPlayer->IsInGame()) {
			return pContext->ThrowNativeError("Client %d is not connected", client);
		}
	}

	g_TERecFilter.Reset();
	g_TERecFilter.Initialize(cl_array, numClients);

	g_CurrentTE->Send(g_TERecFilter, sp_ctof(params[3]));
	g_CurrentTE = NULL;

	return 1;
}