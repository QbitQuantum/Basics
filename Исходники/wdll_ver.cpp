static Status ReadVersionString(const OsPath& modulePathname, wchar_t* out_ver, size_t out_ver_len)
{
	WinScopedPreserveLastError s;	// GetFileVersion*, Ver*

	// determine size of and allocate memory for version information.
	DWORD unused;
	const DWORD ver_size = GetFileVersionInfoSizeW(OsString(modulePathname).c_str(), &unused);	// [bytes]
	if(!ver_size)
	{
		// check if the failure is due to not finding modulePathname
		// (necessary since GetFileVersionInfoSize doesn't SetLastError)
		HMODULE hModule = LoadLibraryExW(OsString(modulePathname).c_str(), 0, LOAD_LIBRARY_AS_DATAFILE);
		if(!hModule)
			return ERR::FAIL;	// NOWARN (file not found - due to FS redirection?)
		FreeLibrary(hModule);
		return ERR::NOT_SUPPORTED;	// NOWARN (module apparently lacks version information)
	}

	shared_ptr<u8> mem = Allocate(ver_size);
	if(!GetFileVersionInfoW(OsString(modulePathname).c_str(), 0, ver_size, mem.get()))
		WARN_RETURN(ERR::_3);

	u16* lang;	// -> 16 bit language ID, 16 bit codepage
	UINT lang_len;
	const BOOL ok = VerQueryValueW(mem.get(), L"\\VarFileInfo\\Translation", (void**)&lang, &lang_len);
	if(!ok || !lang || lang_len != 4)
		WARN_RETURN(ERR::_4);

	wchar_t subblock[64];
	swprintf_s(subblock, ARRAY_SIZE(subblock), L"\\StringFileInfo\\%04X%04X\\FileVersion", lang[0], lang[1]);
	const wchar_t* in_ver;
	UINT in_ver_len;
	if(!VerQueryValueW(mem.get(), subblock, (void**)&in_ver, &in_ver_len))
		WARN_RETURN(ERR::_5);

	wcscpy_s(out_ver, out_ver_len, in_ver);
	return INFO::OK;
}