VOID PrintAvailableMemory()
{
	WCHAR sz[MAX_PATH] = { 0 };
	_i64tow_s(GetAvailableMemory(), sz, _countof(sz), 10);
	std::wstring s = AddComma(sz);
	logw(L"AvailableMemory: %s", s.c_str());
}