size_t spawnClient()
{	
	intptr_t ptr = _spawnl(_P_NOWAITO, "TiGaClient.exe", ".\\TiGaClient.exe", "127.0.0.1", "15600" );
	if( ptr != -1 )
	{
		size_t id = ++lastClientId;
		clients[id] = ptr;
		return id;
	}
	else 
		printf("Error: %s\n", processError());
	return 0;
}