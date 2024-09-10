UINT MeasureNet::GetBestInterfaceOrByName(const WCHAR* iface)
{
	if (c_Table == nullptr) return 0;

	if (_wcsicmp(iface, L"BEST") == 0)
	{
		DWORD dwBestIndex;
		if (NO_ERROR == GetBestInterface(INADDR_ANY, &dwBestIndex))
		{
			if (c_GetIfTable2)
			{
				MIB_IF_ROW2* table = (MIB_IF_ROW2*)((MIB_IF_TABLE2*)c_Table)->Table;
				for (size_t i = 0; i < c_NumOfTables; ++i)
				{
					if (table[i].InterfaceIndex == (NET_IFINDEX)dwBestIndex)
					{
						if (GetRainmeter().GetDebug())
						{
							LogDebugF(this, L"Using network interface: Number=(%i), Name=\"%s\"", i + 1, table[i].Description);
						}

						return (i + 1);
					}
				}
			}
			else
			{
				MIB_IFROW* table = (MIB_IFROW*)((MIB_IFTABLE*)c_Table)->table;
				for (size_t i = 0; i < c_NumOfTables; ++i)
				{
					if (table[i].dwIndex == (NET_IFINDEX)dwBestIndex)
					{
						if (GetRainmeter().GetDebug())
						{
							LogDebugF(this, L"Using network interface: Number=(%i), Name=\"%.*S\"", (int)i + 1, table[i].dwDescrLen, (char*)table[i].bDescr);
						}

						return (i + 1);
					}
				}
			}
		}
	}
	else
	{
		if (c_GetIfTable2)
		{
			MIB_IF_ROW2* table = (MIB_IF_ROW2*)((MIB_IF_TABLE2*)c_Table)->Table;
			for (size_t i = 0; i < c_NumOfTables; ++i)
			{
				if (_wcsicmp(iface, table[i].Description) == 0)
				{
					return (i + 1);
				}
			}
		}
		else
		{
			MIB_IFROW* table = (MIB_IFROW*)((MIB_IFTABLE*)c_Table)->table;
			for (size_t i = 0; i < c_NumOfTables; ++i)
			{
				if (_wcsicmp(iface, StringUtil::Widen((char*)table[i].bDescr).c_str()) == 0)
				{
					return (i + 1);
				}
			}
		}
	}

	LogErrorF(this, L"Cannot find interface: \"%s\"", iface);
	return 0;
}