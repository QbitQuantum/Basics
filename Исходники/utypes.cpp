unsigned __int64  __stdcall Str264(LPSTR pszString, int base){
	//supports - but doesnt seem to work with 0x prefix? so had to include base arg..
	unsigned __int64 ret = _strtoui64(pszString, NULL, base);
	return ret;
}