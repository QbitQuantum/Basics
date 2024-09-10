static Bool get_default_install_path(char *file_path, u32 path_type)
{
	FILE *f;
	char *sep;
	char szPath[GF_MAX_PATH];


#ifdef _WIN32_WCE
	TCHAR w_szPath[GF_MAX_PATH];
	GetModuleFileName(NULL, w_szPath, GF_MAX_PATH);
	CE_WideToChar((u16 *) w_szPath, file_path);
#else
	GetModuleFileNameA(NULL, file_path, GF_MAX_PATH);
#endif

	/*remove exe name*/
	if (strstr(file_path, ".exe")) {
		sep = strrchr(file_path, '\\');
		if (sep) sep[0] = 0;
	}

	strcpy(szPath, file_path);
	strlwr(szPath);

	/*if this is run from a browser, we do not get our app path - fortunately on Windows, we always use 'GPAC' in the
	installation path*/
	if (!strstr(file_path, "gpac") && !strstr(file_path, "GPAC") ) {
		HKEY hKey = NULL;
		DWORD dwSize = GF_MAX_PATH;

		/*locate the key in current user, then in local machine*/
#ifdef _WIN32_WCE
		DWORD dwType = REG_SZ;
		u16 w_path[1024];
		RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\GPAC"), 0, KEY_READ, &hKey);
#ifdef _DEBUG
		if (RegQueryValueEx(hKey, TEXT("DebugDir"), 0, &dwType, (LPBYTE) w_path, &dwSize) != ERROR_SUCCESS)
#endif
			RegQueryValueEx(hKey, TEXT("InstallDir"), 0, &dwType, (LPBYTE) w_path, &dwSize);
		CE_WideToChar(w_path, (char *)file_path);
		RegCloseKey(hKey);
#else
		if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\GPAC", 0, KEY_READ, &hKey) != ERROR_SUCCESS)
			RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\GPAC", 0, KEY_READ, &hKey);

		dwSize = GF_MAX_PATH;

#ifdef _DEBUG
		if (RegQueryValueEx(hKey, "DebugDir", NULL, NULL,(unsigned char*) file_path, &dwSize) != ERROR_SUCCESS)
#endif
			RegQueryValueEx(hKey, "InstallDir", NULL, NULL,(unsigned char*) file_path, &dwSize);

		RegCloseKey(hKey);
#endif
	}


	if (path_type==GF_PATH_APP) return GF_TRUE;

	if (path_type==GF_PATH_GUI) {
		char *sep;
		strcat(file_path, "\\gui");
		if (check_file_exists("gui.bt", file_path, file_path)) return GF_TRUE;
		sep = strstr(file_path, "\\bin\\");
		if (sep) {
			sep[0] = 0;
			strcat(file_path, "\\gui");
			if (check_file_exists("gui.bt", file_path, file_path)) return GF_TRUE;
		}
		return GF_FALSE;
	}
	/*modules are stored in the GPAC directory (should be changed to GPAC/modules)*/
	if (path_type==GF_PATH_MODULES) return GF_TRUE;

	/*we are looking for the config file path - make sure it is writable*/
	assert(path_type == GF_PATH_CFG);

	strcpy(szPath, file_path);
	strcat(szPath, "\\gpaccfgtest.txt");
	//do not use gf_fopen here, we don't want to through any error if failure
	f = fopen(szPath, "wb");
	if (f != NULL) {
		fclose(f);
		gf_delete_file(szPath);
		return GF_TRUE;
	}
#ifdef _WIN32_WCE
	return 0;
#else
	/*no write access, get user home directory*/
	SHGetFolderPath(NULL, CSIDL_APPDATA | CSIDL_FLAG_CREATE, NULL, SHGFP_TYPE_CURRENT, file_path);
	if (file_path[strlen(file_path)-1] != '\\') strcat(file_path, "\\");
	strcat(file_path, "GPAC");
	/*create GPAC dir*/
	_mkdir(file_path);
	strcpy(szPath, file_path);
	strcat(szPath, "\\gpaccfgtest.txt");
	f = fopen(szPath, "wb");
	/*COMPLETE FAILURE*/
	if (!f) return GF_FALSE;

	fclose(f);
	gf_delete_file(szPath);
	return GF_TRUE;
#endif
}