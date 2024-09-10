FILE * _Xfsopen(_In_z_ const wchar_t *filename, _In_ int mode, _In_ int prot)
	{
	static const wchar_t * const mods[] =
		{	// fopen mode strings corresponding to valid[i]
		L"r", L"w", L"w", L"a",
		L"rb", L"wb", L"wb", L"ab",
		L"r+", L"w+", L"a+",
		L"r+b", L"w+b", L"a+b",
		0};

	return _wfsopen(filename, mods[mode], prot);
	}