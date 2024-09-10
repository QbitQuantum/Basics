bool CMacFetcher::GetMACbyNetBiosRedir(MACAddress& addr)
{
	WKSTA_TRANSPORT_INFO_0 *pwkti = NULL; 
	DWORD dwEntriesRead;
	DWORD dwTotalEntries;
	BYTE *pbBuffer = NULL;
	
	// 通过 NetBIOS的枚举函数获取MAC地址
	NET_API_STATUS dwStatus = NetWkstaTransportEnum(
		NULL,
		0,
		&pbBuffer,
		MAX_PREFERRED_LENGTH,
		&dwEntriesRead,
		&dwTotalEntries,
		NULL);
	if (dwStatus != NERR_Success)
	{
		return false;
	}

	if (pbBuffer == NULL || dwEntriesRead == 0)
	{
		return false;
	}
	
	pwkti = (WKSTA_TRANSPORT_INFO_0 *)pbBuffer; // 指针类型转换
	
	for(DWORD i = 0; i < dwEntriesRead && pwkti; ++i)
	{ 
		short usMac[6] = { 0 };
		// 读取并打印MAC地址
#if _MSC_VER <= 1200
		if (swscanf((wchar_t *)pwkti[i].wkti0_transport_address,
			L"%2hx%2hx%2hx%2hx%2hx%2hx",
			&usMac[0],
			&usMac[1],
			&usMac[2], 
			&usMac[3],
			&usMac[4],
			&usMac[5]) == 6)
#else
		if (swscanf_s((wchar_t *)pwkti[i].wkti0_transport_address,
			L"%2hx%2hx%2hx%2hx%2hx%2hx",
			&usMac[0],
			&usMac[1],
			&usMac[2], 
			&usMac[3],
			&usMac[4],
			&usMac[5]) == 6)
#endif
		{
			for (int j = 0; j < 6; ++j)
			{
				addr.v[j] = (unsigned char)(usMac[j] & 0x00ff);
			}
			if (addr != MACAddress())
			{
				break;
			}
		}
	}

	NetApiBufferFree(pbBuffer);
	return true;
}