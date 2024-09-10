// Hash the list of current Ethernet devices
UINT GetEthDeviceHash()
{
#ifdef	OS_UNIX
	// UNIX
	UINT num;
	UINT i;
	char tmp[4096];
	UCHAR hash[SHA1_SIZE];
	TOKEN_LIST *t = GetEthList();

	num = t->NumTokens;
	tmp[0] = 0;
	for (i = 0;i < t->NumTokens;i++)
	{
		StrCat(tmp, sizeof(tmp), t->Token[i]);
	}
	FreeToken(t);

	Hash(hash, tmp, StrLen(tmp), true);

	Copy(&num, hash, sizeof(UINT));

	return num;
#else	// OS_UNIX
	// Win32
	UINT ret = 0;
	MS_ADAPTER_LIST *a = MsCreateAdapterListEx(true);
	UINT num;
	UINT i;
	char tmp[4096];
	UCHAR hash[SHA1_SIZE];

	tmp[0] = 0;
	if (a != NULL)
	{
		for (i = 0;i < a->Num;i++)
		{
			StrCat(tmp, sizeof(tmp), a->Adapters[i]->Title);
		}
	}
	MsFreeAdapterList(a);

	Hash(hash, tmp, StrLen(tmp), true);

	Copy(&num, hash, sizeof(UINT));

	return num;
#endif	// OS_UNIX
}