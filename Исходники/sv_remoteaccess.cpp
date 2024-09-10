bool CServerRemoteAccess::LookupValue(const char *variable, CUtlBuffer &value)
{
	const char* strval = LookupStringValue(variable);
	if (strval)
	{
		value.PutString(strval);
		value.PutChar(0);
		return true;
	}

	if (!Q_stricmp(variable, "stats"))
	{
		char stats[512];
		GetStatsString(stats, sizeof(stats));
		value.PutString(stats);
		value.PutChar(0);
		return true;
	}

	if (!Q_stricmp(variable, "banlist"))
	{
		GetUserBanList(value);
		return true;
	}

	if (!Q_stricmp(variable, "playerlist"))
	{
		GetPlayerList(value);
		return true;
	}

	if (!Q_stricmp(variable, "maplist"))
	{
		GetMapList(value);
		return true;
	}

	if (!Q_stricmp(variable, "uptime"))
	{
		value.PutInt(int(Sys_FloatTime() - Host_GetStartTime()));
		value.PutChar(0);
		return true;
	}

	if (!Q_stricmp(variable, "ipaddress"))
	{
		value.PutString(NET_AdrToString(net_local_adr));
		value.PutChar(0);
		return true;
	}

	if (!Q_stricmp(variable, "mapcycle"))
	{
		int len;
		void* mapcyclelist = COM_LoadFileForMe(mapcyclefile.string, &len);
		if (mapcyclelist && len)
		{
			value.PutString((char*)mapcyclelist);
			value.PutChar(0);
			COM_FreeFile(mapcyclelist);
		}
		return true;
	}

	value.PutChar(0);
	return false;
}