AUTHADMIN_API
BOOL CUGP(char * userin,char *password,char *machine,char *groupin,int locdom)
{
	DWORD dwLogonType;
	DWORD dwLogonProvider;
	HANDLE hToken;
	bool returnvalue=false;
	dwLogonType     = LOGON32_LOGON_INTERACTIVE;
	dwLogonProvider = LOGON32_PROVIDER_DEFAULT;

	byte *buf = 0;
	byte *buf2 = 0;
	char domain[MAXLEN * sizeof(wchar_t)];
	DWORD rcdomain = NetGetDCName( 0, 0, &buf );
	NetApiBufferFree( buf );
	printf("Logonuser: % s %s \n", userin, ".");
			if (LogonUser(userin, ".", password, dwLogonType, dwLogonProvider, &hToken))
					if (ImpersonateLoggedOnUser(hToken))
				{
					returnvalue=IsAdmin();
					RevertToSelf();
					CloseHandle(hToken);
				}
	if (returnvalue==true) return returnvalue;
	if (!rcdomain)
		{
			DWORD result=NetWkstaGetInfo( 0 , 100 , &buf2 ) ;
				if (!result)
				{
					wcstombs( domain, ((WKSTA_INFO_100_NT *) buf2)->wki100_langroup, MAXLEN );
					NetApiBufferFree( buf2 );
					printf("Logonuser: % s %s \n", userin, domain);
					if (LogonUser(userin, domain, password, dwLogonType, dwLogonProvider, &hToken))
						if (ImpersonateLoggedOnUser(hToken))
							{
								returnvalue=IsAdmin();
								RevertToSelf();
								CloseHandle(hToken);
							}
				}

		}
	
	return returnvalue;
	
}