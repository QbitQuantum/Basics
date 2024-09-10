void MOInit(const char* appname)
{
	strcpy(g_AppName, appname);

	DWORD dwVersion = GetVersion();
	DWORD dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
	DWORD dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
	DWORD dwBuild = 0;
	if(dwVersion<0x80000000) dwBuild = (DWORD)(HIWORD(dwVersion));
	sprintf(g_OSName, "windows0%d0%d0%d", dwMajorVersion, dwMinorVersion, dwBuild);
	GetModuleFileNameA(NULL, g_ResourcePath, sizeof(g_ResourcePath));
	*(strrchr(g_ResourcePath, '\\')) = '\0';
	*(strrchr(g_ResourcePath, '\\')) = '\0';
	*(strrchr(g_ResourcePath, '\\')) = '\0';

	LPITEMIDLIST pidl=NULL;
	char szDocument[MAX_PATH];
	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &pidl);   
	SHGetPathFromIDListA(pidl, szDocument);
	strcat(szDocument, "\\MO_DEVICE_ID.txt");
	FILE* fp;
	fp = fopen(szDocument, "rt");
	if(fp)
	{
		if(fgets(g_UDID, sizeof(g_UDID), fp)==NULL) g_UDID[0] = '\0';
		fclose(fp);
	}
	if(g_UDID[0]=='\0')
	{
		UUID uuid;
		UuidCreate(&uuid);
		RPC_CSTR val;
		UuidToStringA((UUID*)&uuid, &val);
		strcpy(g_UDID, (const char*)val);
		RpcStringFreeA(&val);
		fp = fopen(szDocument, "wt");
		if(fp)
		{
			fputs(g_UDID, fp);
			fclose(fp);
		}
	}
}