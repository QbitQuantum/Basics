BOOL kull_m_token_getNameDomainFromToken(HANDLE hToken, PWSTR * pName, PWSTR * pDomain, PWSTR * pSid, PSID_NAME_USE pSidNameUse)
{
	BOOL result = FALSE;
	PTOKEN_USER pTokenUser;
	DWORD szNeeded;

	if(!GetTokenInformation(hToken, TokenUser, NULL, 0, &szNeeded) && (GetLastError() == ERROR_INSUFFICIENT_BUFFER))
	{
		if(pTokenUser = (PTOKEN_USER) LocalAlloc(LPTR, szNeeded))
		{
			if(GetTokenInformation(hToken, TokenUser, pTokenUser, szNeeded, &szNeeded))
			{
				if((result = kull_m_token_getNameDomainFromSID(pTokenUser->User.Sid, pName, pDomain, pSidNameUse, NULL)) && pSid)
					result = ConvertSidToStringSid(pTokenUser->User.Sid, pSid);
			}
			LocalFree(pTokenUser);
		}
	}
	return result;
}