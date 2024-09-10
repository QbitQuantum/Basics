static HMODULE DelayLoadLibraryW(LPCWSTR dllname)
{
	WCHAR curfile[_MAX_PATH];
	GetModuleFileNameW(hInstance, curfile, MAX_PATH);
	PathRemoveFileSpecW(curfile);
	PathAppendW(curfile, dllname);
	HMODULE hdll = LoadLibraryW(curfile);
	if (hdll == nullptr)
		return LoadLibraryW(dllname);
	return hdll;
}