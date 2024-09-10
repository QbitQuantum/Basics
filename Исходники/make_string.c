Array make_string(const char* s) {
	size_t len = strlen(s);
	wchar_t ws[len + 2];
	
	mbstate_t mbs;
	bzero(&mbs, sizeof(mbs));
	
	if(mbsrtowcs(ws, &s, len + 1, &mbs) == (size_t)-1)
		error(L"Wide-string encoding error");
	
	return make_wstring(ws);
}