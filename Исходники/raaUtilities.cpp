std::string raaUtilities::regReadEntry(std::string sKey, std::string sEntry)
{
	std::string sStr;
	HKEY hKey;
	DWORD dwType=REG_SZ, dwSize=8192*sizeof(char);

	if(RegOpenKeyExA(HKEY_LOCAL_MACHINE, sKey.c_str(),0,KEY_ALL_ACCESS,&hKey)==ERROR_SUCCESS)
	{
		if(hKey)
		{
			char c[8192];
			int i=RegQueryValueExA(hKey, sEntry.c_str(), 0, &dwType, (PBYTE)c, &dwSize);

			
			RegCloseKey(hKey);
			
			if(!i)
			{
				sStr=c;
			}
		}
	}
	return sStr;
}