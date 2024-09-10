void DDEPoke(DWORD idInst, HCONV hConv, char* szItem, char* szData)
{
    HSZ hszItem = DdeCreateStringHandle(idInst, szItem, 0);
	DdeClientTransaction((LPBYTE)szData, (DWORD)(lstrlen(szData)+1),
                          hConv, hszItem, CF_TEXT,
                          XTYP_POKE, 3000, NULL);
    DdeFreeStringHandle(idInst, hszItem);
}