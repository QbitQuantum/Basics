void	 InitNodeId(Skype_Inst *pInst)
{
	DWORD BufSz = sizeof(pInst->NodeID);
	HKEY hKey;

	if (QueryRegValue(HKEY_LOCAL_MACHINE, 
		"SOFTWARE\\FakeSkype\\NodeId",
		(LPBYTE)&pInst->NodeID, &BufSz)) return;
	*(int64_t *)&pInst->NodeID = BytesRandomI64();
	if (RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\FakeSkype", &hKey) == ERROR_SUCCESS)
	{
		RegSetValueExA(hKey, "NodeId", 0, REG_BINARY, (LPBYTE)&pInst->NodeID, sizeof(pInst->NodeID));
		RegCloseKey(hKey);
	}
	
	//FIXED NODEID
	//memcpy_s(NodeID, NODEID_SZ, "\x49\x63\xff\xee\xe0\x5c\x9d\xf8", NODEID_SZ);
	//memcpy_s(NodeID, NODEID_SZ, "\x97\xca\xb1\x72\x06\xf6\x72\xb4", NODEID_SZ);
}