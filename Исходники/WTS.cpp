void WTS::EnumerateServers()
{
	//PWTS_SERVER_INFO serverInfo;
	PSERVER_INFO_100 serverInfo;
	DWORD entriesRead;
	DWORD totalEntries;
	DWORD i;
	DWORD ret;
	/*wprintf(L"domain: %s\n", Util::DomainFromIP(Config::machine));
	if(WTSEnumerateServers(Util::DomainFromIP(Config::machine), 0, 1, &serverInfo, &totalEntries) != 0)
	{
		Util::Error(GetLastError(), L"WTSEnumerateServers()");
	}*/
	if((ret = NetServerEnum(NULL, 100, (LPBYTE *)&serverInfo, MAX_PREFERRED_LENGTH, &entriesRead, &totalEntries, SV_TYPE_TERMINALSERVER, Util::DomainFromIP(Config::machine), NULL)) != NERR_Success)
	{
		Util::Error(ret, L"NetServerEnum()");
	}

	for(i = 0; i < totalEntries; i++)
	{
		wprintf(L"Entry: %s\n", serverInfo[i].sv100_name);
	}
	wprintf(L"Total entries: %d\n", totalEntries);
}