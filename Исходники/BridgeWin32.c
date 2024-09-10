// Initialize WP structure with DLL
bool InitWpWithLoadLibrary(WP *wp, HINSTANCE h)
{
	TOKEN_LIST *o;
	UINT total_num = 0;
	// Validate arguments
	if (wp == NULL || h == NULL)
	{
		return false;
	}
	wp->Inited = true;
	wp->hPacketDll = h;

	LOAD_DLL_ADDR(PacketGetVersion);
	LOAD_DLL_ADDR(PacketGetDriverVersion);
	LOAD_DLL_ADDR(PacketSetMinToCopy);
	LOAD_DLL_ADDR(PacketSetNumWrites);
	LOAD_DLL_ADDR(PacketSetMode);
	LOAD_DLL_ADDR(PacketSetReadTimeout);
	LOAD_DLL_ADDR(PacketSetBpf);
	LOAD_DLL_ADDR(PacketSetSnapLen);
	LOAD_DLL_ADDR(PacketGetStats);
	LOAD_DLL_ADDR(PacketGetStatsEx);
	LOAD_DLL_ADDR(PacketSetBuff);
	LOAD_DLL_ADDR(PacketGetNetType);
	LOAD_DLL_ADDR(PacketOpenAdapter);
	LOAD_DLL_ADDR(PacketSendPacket);
	LOAD_DLL_ADDR(PacketSendPackets);
	LOAD_DLL_ADDR(PacketAllocatePacket);
	LOAD_DLL_ADDR(PacketInitPacket);
	LOAD_DLL_ADDR(PacketFreePacket);
	LOAD_DLL_ADDR(PacketReceivePacket);
	LOAD_DLL_ADDR(PacketSetHwFilter);
	LOAD_DLL_ADDR(PacketGetAdapterNames);
	LOAD_DLL_ADDR(PacketGetNetInfoEx);
	LOAD_DLL_ADDR(PacketRequest);
	LOAD_DLL_ADDR(PacketGetReadEvent);
	LOAD_DLL_ADDR(PacketSetDumpName);
	LOAD_DLL_ADDR(PacketSetDumpLimits);
	LOAD_DLL_ADDR(PacketSetDumpLimits);
	LOAD_DLL_ADDR(PacketIsDumpEnded);
	LOAD_DLL_ADDR(PacketStopDriver);
	LOAD_DLL_ADDR(PacketCloseAdapter);
	LOAD_DLL_ADDR(PacketSetLoopbackBehavior);

	if (wp->PacketSetMinToCopy == NULL ||
		wp->PacketSetNumWrites == NULL ||
		wp->PacketSetMode == NULL ||
		wp->PacketSetReadTimeout == NULL ||
		wp->PacketSetBuff == NULL ||
		wp->PacketGetNetType == NULL ||
		wp->PacketOpenAdapter == NULL ||
		wp->PacketSendPacket == NULL ||
		wp->PacketSendPackets == NULL ||
		wp->PacketAllocatePacket == NULL ||
		wp->PacketInitPacket == NULL ||
		wp->PacketFreePacket == NULL ||
		wp->PacketReceivePacket == NULL ||
		wp->PacketSetHwFilter == NULL ||
		wp->PacketGetAdapterNames == NULL ||
		wp->PacketGetNetInfoEx == NULL ||
		wp->PacketCloseAdapter == NULL)
	{
RELEASE:
		wp->Inited = false;
		wp->hPacketDll = NULL;

		return false;
	}

	o = GetEthListEx(&total_num);
	if (o == NULL || total_num == 0)
	{
		FreeToken(o);
		goto RELEASE;
	}

	FreeToken(o);

	return true;
}