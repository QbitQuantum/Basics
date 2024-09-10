	bool IsAdmin()
	{
		DWORD dwSize = 0;
		HANDLE hToken;
		PTOKEN_GROUPS pGroupInfo;
		BYTE sidBuffer[100];
		PSID pSID = (PSID)&sidBuffer;
		SID_IDENTIFIER_AUTHORITY SIDAuth = SECURITY_NT_AUTHORITY;

		// Open a handle to the access token for the calling process.
		if (!OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &hToken )) 
		{
			LogTheError(_T("OpenProcessToken Error"));
			return false;
		}

		// Call GetTokenInformation to get the buffer size.
		if(!GetTokenInformation(hToken, TokenGroups, NULL, dwSize, &dwSize)) 
		{
			if( GetLastError() != ERROR_INSUFFICIENT_BUFFER ) 
			{
				LogTheError(_T("GetTokenInformation Error"));
				return false;
			}
		}

		// Call GetTokenInformation again to get the group information.
		pGroupInfo = (PTOKEN_GROUPS) GlobalAlloc( GPTR, dwSize );
		if(! GetTokenInformation(hToken, TokenGroups, pGroupInfo, dwSize, &dwSize ) )
		{
			LogTheError(_T("GetTokenInformation Error"));
			if ( pGroupInfo )
				GlobalFree( pGroupInfo );
			return false;
		}

		// Create a SID for the BUILTIN\Administrators group.
		if(! AllocateAndInitializeSid( &SIDAuth, 2, 
			SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0, &pSID) )
		{
			LogTheError(_T("AllocateAndInitializeSid Error"));
			if (pSID)
				FreeSid(pSID);
			if ( pGroupInfo )
				GlobalFree( pGroupInfo );
			return false;
		}

		// Loop through the group SIDs looking for the administrator SID.
		bool bFound = false;
		for(DWORD i=0; i<pGroupInfo->GroupCount; i++) 
		{
			if ( EqualSid(pSID, pGroupInfo->Groups[i].Sid) ) 
				bFound = true;
		}

		if (pSID)
			FreeSid(pSID);
		if ( pGroupInfo )
			GlobalFree( pGroupInfo );
		return bFound;
	}