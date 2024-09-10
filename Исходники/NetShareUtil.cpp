PCBYTE
CNetShare::GetInfo(
	PCWSTR pszServer, 
	PCWSTR pszShare, 
	ULONG ulLevel
)
{
	if(!pszShare)
	{	
		wprintf(L"Не заданно имя общедоступного ресурса");
		return NULL;
	}
	
	PBYTE pData = NULL;
	ULONG ulResult = NetShareGetInfo(const_cast<PWSTR>(pszServer), const_cast<PWSTR>(pszShare), ulLevel, reinterpret_cast<LPBYTE *>(&pData));
	if(NERR_Success != ulResult)
	{
		wprintf(L"Error: NetShareGetInfo() 0X%08x\n", ulResult);
		return NULL;
	}
	
	return pData;
}