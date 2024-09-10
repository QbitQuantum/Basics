extern "C" BOOL RegisterComServers (char *modulePath)
{
	BOOL ret = FALSE;
	wchar_t mainModule[1024], formatModule[1024];
	CComPtr<ITypeLib> tl, tl2;

	wsprintfW (mainModule, L"%hsTrueCrypt.exe", modulePath);
	wsprintfW (formatModule, L"%hsTrueCrypt Format.exe", modulePath);

	UnRegisterTypeLib (LIBID_TrueCryptMainCom, 1, 0, 0, SYS_WIN32);
	UnRegisterTypeLib (LIBID_TrueCryptFormatCom, 1, 0, 0, SYS_WIN32);

	CRegObject ro;
	ro.FinalConstruct ();

	ro.AddReplacement (L"MAIN_MODULE", mainModule);
	ro.AddReplacement (L"FORMAT_MODULE", formatModule);

	wchar_t setupModule[MAX_PATH];
	GetModuleFileNameW (NULL, setupModule, sizeof (setupModule) / sizeof (setupModule[0]));
	if (ro.ResourceRegister (setupModule, IDR_COMREG, L"REGISTRY") != S_OK)
		goto error;

	if (LoadTypeLib (mainModule, &tl) != S_OK
		|| RegisterTypeLib (tl, mainModule, 0) != S_OK)
		goto error;

	if (LoadTypeLib (formatModule, &tl2) != S_OK
		|| RegisterTypeLib (tl2, formatModule, 0) != S_OK)
		goto error;

	ret = TRUE;
error:
	ro.FinalRelease ();
	return ret;
}