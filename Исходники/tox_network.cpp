void CToxProto::BootstrapNodesFromIni(bool isIPv6)
{
	if (IsFileExists((TCHAR*)VARST(_T(TOX_INI_PATH))))
	{
		char fileName[MAX_PATH];
		mir_strcpy(fileName, VARS(TOX_INI_PATH));

		char *section, sections[MAX_PATH], value[MAX_PATH];
		GetPrivateProfileSectionNamesA(sections, _countof(sections), fileName);
		section = sections;
		while (*section != NULL)
		{
			if (strstr(section, TOX_SETTINGS_NODE_PREFIX) == section)
			{
				GetPrivateProfileStringA(section, "IPv4", NULL, value, _countof(value), fileName);
				ptrA address(mir_strdup(value));
				int port = GetPrivateProfileIntA(section, "Port", 33445, fileName);
				GetPrivateProfileStringA(section, "PubKey", NULL, value, _countof(value), fileName);
				ptrA pubKey(mir_strdup(value));
				BootstrapNode(address, port, pubKey);
				if (isIPv6)
				{
					GetPrivateProfileStringA(section, "IPv6", NULL, value, _countof(value), fileName);
					address = mir_strdup(value);
					BootstrapNode(address, port, pubKey);
				}
			}
			section += mir_strlen(section) + 1;
		}
	}
}