std::vector<unsigned char> GetTokenInfo(HANDLE hToken, TOKEN_INFORMATION_CLASS tokenClass)
{
	std::vector<unsigned char> ret;
	DWORD cbTokenInfo;	

	if (!GetTokenInformation(hToken, tokenClass, nullptr, 0, &cbTokenInfo))
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			ret.resize(cbTokenInfo);			

			if (!GetTokenInformation(hToken, tokenClass, &ret[0], (DWORD)ret.size(), &cbTokenInfo))
			{	
				ret.clear();
			}
		}
	}

	return ret;
}