// Release the DHCP addresses of all virtual LAN cards
void Win32ReleaseAllDhcp9x(bool wait)
{
	TOKEN_LIST *t;
	UINT i;

	t = MsEnumNetworkAdapters(VLAN_ADAPTER_NAME, VLAN_ADAPTER_NAME_OLD);
	if (t == NULL)
	{
		return;
	}

	for (i = 0;i < t->NumTokens;i++)
	{
		char *name = t->Token[i];
		UINT id = GetInstanceId(name);
		if (id != 0)
		{
			Win32ReleaseDhcp9x(id, wait);
		}
	}

	FreeToken(t);
}