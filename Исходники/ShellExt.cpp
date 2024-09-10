HRESULT CShellExt::Initialize(LPCITEMIDLIST pidlFolder, LPDATAOBJECT pDataObj, HKEY hProgID)
{
	memset(_vc_path, 0, MAX_PATH*2);
	char inifile[MAX_PATH] = {0};
	char drive[_MAX_DRIVE*2] = {0};
	char dir[_MAX_DIR*2] = {0};


	GetModuleFileNameA(g_hInstance, inifile, MAX_PATH);
	//MessageBoxA(NULL, inifile, "", MB_OK);

	errno_t err;
	err = _splitpath_s(inifile, 
		drive,
		_MAX_DRIVE,
		dir,
		_MAX_DIR,
		NULL, 0, 
		NULL, 0);
	err = _makepath_s(inifile, _MAX_PATH, drive, dir, "zShellExt", "ini");

	GetPrivateProfileStringA("VS2008", "path", "", _vc_path, MAX_PATH*2, inifile);
	//MessageBoxA(NULL, _vc_path, "", MB_OK);
	return S_OK;
}