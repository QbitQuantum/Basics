// Get the proxy server settings from the registry string of IE
bool GetProxyServerNameAndPortFromIeProxyRegStr(char *name, UINT name_size, UINT *port, char *str, char *server_type)
{
#ifdef	OS_WIN32
	TOKEN_LIST *t;
	UINT i;
	bool ret = false;
	// Validate arguments
	if (name == NULL || port == NULL || str == NULL || server_type == NULL)
	{
		return false;
	}

	t = ParseToken(str, ";");

	for (i = 0;i < t->NumTokens;i++)
	{
		char *s = t->Token[i];
		UINT i;

		Trim(s);

		i = SearchStrEx(s, "=", 0, false);
		if (i != INFINITE)
		{
			char tmp[MAX_PATH];

			StrCpy(name, name_size, s);
			name[i] = 0;

			if (StrCmpi(name, server_type) == 0)
			{
				char *host;
				StrCpy(tmp, sizeof(tmp), s + i + 1);

				if (ParseHostPort(tmp, &host, port, 0))
				{
					StrCpy(name, name_size, host);
					Free(host);

					if (*port != 0)
					{
						ret = true;
					}
					break;
				}
			}
		}
	}

	FreeToken(t);

	return ret;
#else	// OS_WIN32
	return true;
#endif	// OS_WIN32
}