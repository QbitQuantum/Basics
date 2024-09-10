int SV_AddTestClient() {
	char buffer[1024];
	int botport = 1;
	int protocolVersion = ((int(*)())&ParseAddr(0x28FE40))(); //GetProtocolVersion
	int checksum = ((int(*)())&ParseAddr(0x2093C))(); //BG_NetDataChecksum
	int PersistentDataDefVersion = ((int(*)())&ParseAddr(0x1EA710))(); //LiveStorage_GetPersistentDataDefVersion
	unsigned int PersistentDataDefVersionChecksum = ((int(*)())&ParseAddr(0x1EA740))(); //LiveStorage_GetPersistentDataDefFormatChecksum

	//0x236084 - client->dropReason, causing issue, source: unknown. (SV_SendMessageToClient)
	uint32_t patchData[] = { 0x38800005 };
	write_process(0x22E55C, &patchData, 4);
	Sprintf(buffer, "connect bot%d \"\\cg_predictItems\\1\\cl_anonymous\\0\\color\\4\\head\\default\\model\\multi\\snaps\\20\\rate\\5000\\name\\bot%d\\protocol\\%d\\checksum\\%d\\statver\\%d %u\\qport\\%d\"", botport, botport, protocolVersion, checksum, PersistentDataDefVersion, PersistentDataDefVersionChecksum, botport);
	Memset((void*)ThreadStorage_a, 0, sizeof(netadr_s));
	netadr_s* newConnection = (netadr_s*)(ThreadStorage_a);
	newConnection->port = botport;

	((void(*)(const char*))&ParseAddr(0x1DBA20))(buffer); //SV_CmdTokenizeString(const char* string)
	((void(*)(netadr_s*))&ParseAddr(0x226074))(newConnection); //SV_DirectConnect(netadr_s* connectionInfo)
	((void(*)())&ParseAddr(0x1DB524))(); //SV_CmdEndTokenizeString()

	*(short*)(getClient_t(botport) + 0x352EA) = 0x3FF; //Set Stat Flags
	*(short*)(getClient_t(botport) + 0x30) = botport; //botPort

	((void(*)(int client))&ParseAddr(0x2284F8))(getClient_t(botport)); //SV_SendClientGameState(client_t* client)
	((void(*)(int client, int usercmd))&ParseAddr(0x2272DC))(getClient_t(botport), ThreadStorage_a); //SV_ClientEnterWorld(client_t* client, usercmd_s* lastUserCmd)
}