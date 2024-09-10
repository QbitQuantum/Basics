/**
 * Allow install using regsvr32
 */
HRESULT WINAPI
DllRegisterServer(void)
{
	TCHAR fn[MAX_PATH], full_fn[MAX_PATH];
	LPTSTR name;
	WORD len_out;
	DWORD cnt;
	char *desc = NULL;
	BOOL b_res;

	if (!GetModuleFileName(hinstFreeTDS, fn, TDS_VECTOR_SIZE(fn)))
		return SELFREG_E_CLASS;
	if (!GetFullPathName(fn, TDS_VECTOR_SIZE(full_fn), full_fn, &name) || !name || full_fn == name)
		return SELFREG_E_CLASS;

	if (asprintf(&desc, "FreeTDS%c"
		"APILevel=2%c"
		"ConnectFunctions=YYN%c"
		"DriverODBCVer=03.00%c"
		"FileUsage=0%c"
		"SQLLevel=2%c"
		"Setup=%s%c"
		"Driver=%s%c",
		0, 0, 0, 0, 0, 0,
		name, 0, name, 0
		) < 0)
		return SELFREG_E_CLASS;
	name[-1] = 0;

	b_res = SQLInstallDriverEx(desc, full_fn, fn, TDS_VECTOR_SIZE(fn), &len_out, ODBC_INSTALL_COMPLETE, &cnt);
	free(desc);
	if (!b_res)
		return SELFREG_E_CLASS;
	return S_OK;
}