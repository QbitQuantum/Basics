bool InstallD3DFix(void)
{
	char FixHighRes[256];
	if(!GothicReadIniString("DEBUG", "FixHighRes", "1", FixHighRes, 256, "SystemPack.ini"))
		GothicWriteIniString("DEBUG", "FixHighRes", "1", "SystemPack.ini");

	char FixAppCompat[256];
	if(!GothicReadIniString("DEBUG", "FixAppCompat", "1", FixAppCompat, 256, "SystemPack.ini"))
		GothicWriteIniString("DEBUG", "FixAppCompat", "1", "SystemPack.ini");

	HMODULE hDDraw = GetModuleHandle(_T("ddraw.dll"));
	if(hDDraw)
	{
		if(IsWindowsXPOrGreater() && (atoi(FixHighRes) == 1))
		{
			DeleteFile(_T("D3DIM700.dll"));
			if(hD3Dim = LoadLibrary(_T("D3DIM700.dll")))
				PatchD3D((uChar*)hD3Dim);
		}

		if(IsWindows8OrGreater())
		{
			int AppCompatFix = atoi(FixAppCompat);
			switch(AppCompatFix)
			{
			case 1:
				{
					SetAppCompatDataFunc SetAppCompatData = (SetAppCompatDataFunc)GetProcAddress(hDDraw, "SetAppCompatData"); // DXPrimaryEmulation -DisableMaxWindowedMode
					if(SetAppCompatData)
						SetAppCompatData(12, 0);
				}
				break;
			case 2:
				{
					uChar* codeBase = (uChar*)GetModuleHandle(NULL);
					PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "USER32.dll");
					if(importDesc)
						PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "CreateWindowExA", (FARPROC)MyCreateWindowExA);
				}
				break;
			}
		}
	}
	return true;
}