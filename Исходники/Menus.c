BOOL myAppendMenu(HMENU h, UINT flags, UINT_PTR id, LPCTSTR name)
{
    if(localeCP > 0 && (localeCP != GetACP())) {
	wchar_t wc[100];
	mbstowcs(wc, name, 100);
	return AppendMenuW(h, flags, id, wc);
    } else
	return AppendMenuA(h, flags, id, name);
}