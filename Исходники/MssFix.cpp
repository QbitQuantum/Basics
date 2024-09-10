bool InstallMssFix(void)
{
	char FixMss[256];
	if(!GothicReadIniString("DEBUG", "FixMss", "1", FixMss, 256, "SystemPack.ini"))
		GothicWriteIniString("DEBUG", "FixMss", "1", "SystemPack.ini");

	if(IsWindowsVistaOrGreater() && (atoi(FixMss) == 1))
	{
		uChar* codeBase = (uChar*)GetModuleHandle(_T("Mss32.dll"));
		if(codeBase)
		{
			PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "KERNEL32.dll");
			if(!importDesc)
				return false;
			return PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "LoadLibraryA", (FARPROC)MyLoadLibraryA);
		}
	}
	return true;
}