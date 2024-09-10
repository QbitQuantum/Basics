/*
	GetPlatformInfo()
*/
void CWindowsVersion::GetPlatformInfo(LPSTR pBuffer,int cbBuffer)
{
	CRegKey regkey;
	char key[REGKEY_MAX_KEY_NAME+1];
	char value[REGKEY_MAX_KEY_VALUE+1];
	int n = 0;

	n += _snprintf(pBuffer+n,cbBuffer-1-n,"%s - %s\r\n",m_szWindowsPlatform,m_szOsType);
	
	// NT
	if(m_OsVersionType==WINDOWS_NT || m_OsVersionType==WINDOWS_2000 || m_OsVersionType==WINDOWS_XP || m_OsVersionType==WINDOWS_VISTA || m_OsVersionType==WINDOWS_SEVEN)
	{
		regkey.Attach(HKEY_LOCAL_MACHINE);
		
		strcpyn(key,"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",sizeof(key));
		if(regkey.Open(HKEY_LOCAL_MACHINE,key)==ERROR_SUCCESS)
		{
			DWORD dwSize;

			dwSize = sizeof(value);
			memset(value,'\0',sizeof(value));
			if(regkey.QueryValue(value,"CurrentBuildNumber",&dwSize)==ERROR_SUCCESS)
				n += _snprintf(pBuffer+n,cbBuffer-1-n,"build: %s\r\n",value);

			dwSize = sizeof(value);
			memset(value,'\0',sizeof(value));
			if(regkey.QueryValue(value,"CurrentType",&dwSize)==ERROR_SUCCESS)
				n += _snprintf(pBuffer+n,cbBuffer-1-n,"type: %s\r\n",value);

			dwSize = sizeof(value);
			memset(value,'\0',sizeof(value));
			if(regkey.QueryValue(value,"ProductId",&dwSize)==ERROR_SUCCESS)
				n += _snprintf(pBuffer+n,cbBuffer-1-n,"product id: %s\r\n",value);

			dwSize = sizeof(value);
			memset(value,'\0',sizeof(value));
			if(regkey.QueryValue(value,"RegisteredOrganization",&dwSize)==ERROR_SUCCESS)
				if(value[0]!='\0')
					n += _snprintf(pBuffer+n,cbBuffer-1-n,"registered to: %s\r\n",value);

			regkey.Close();
		}
		
		regkey.Detach();

		regkey.Attach(HKEY_LOCAL_MACHINE);
		
		strcpyn(key,"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",sizeof(key));
		if(regkey.Open(HKEY_LOCAL_MACHINE,key)==ERROR_SUCCESS)
		{
			DWORD dwSize;

			dwSize = sizeof(value);
			memset(value,'\0',sizeof(value));
			if(regkey.QueryValue(value,"VendorIdentifier",&dwSize)==ERROR_SUCCESS)
				n += _snprintf(pBuffer+n,cbBuffer-1-n,"\r\nMain CPU:\r\n%s\r\n",value);

			dwSize = sizeof(value);
			memset(value,'\0',sizeof(value));
			if(regkey.QueryValue(value,"Identifier",&dwSize)==ERROR_SUCCESS)
				n += _snprintf(pBuffer+n,cbBuffer-1-n,"%s\r\n",value);

			DWORD dwValue = 0L;
			if(regkey.QueryValue(dwValue,"~MHz")==ERROR_SUCCESS)
				n += _snprintf(pBuffer+n,cbBuffer-1-n,"%ld Mhz\r\n",dwValue);

			regkey.Close();
		}
		
		regkey.Detach();
	}
	else // Cartoons
	{
		regkey.Attach(HKEY_LOCAL_MACHINE);
		
		strcpyn(key,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion",sizeof(key));
		if(regkey.Open(HKEY_LOCAL_MACHINE,key)==ERROR_SUCCESS)
		{
			DWORD dwSize;

			dwSize = sizeof(value);
			memset(value,'\0',sizeof(value));
			if(regkey.QueryValue(value,"VersionNumber",&dwSize)==ERROR_SUCCESS)
				n += _snprintf(pBuffer+n,cbBuffer-1-n,"version number: %s\r\n",value);

			dwSize = sizeof(value);
			memset(value,'\0',sizeof(value));
			if(regkey.QueryValue(value,"ProductId",&dwSize)==ERROR_SUCCESS)
				n += _snprintf(pBuffer+n,cbBuffer-1-n,"product id: %s\r\n",value);

			dwSize = sizeof(value);
			memset(value,'\0',sizeof(value));
			if(regkey.QueryValue(value,"RegisteredOrganization",&dwSize)==ERROR_SUCCESS)
				if(value[0]!='\0')
					n += _snprintf(pBuffer+n,cbBuffer-1-n,"registered to: %s\r\n",value);

			regkey.Close();
		}
		
		regkey.Detach();
	}
}