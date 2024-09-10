void FF_tolower(FF_T_WCHAR *string, FF_T_UINT32 strLen) {
	FF_T_UINT32 i;
	for(i = 0; i < strLen; i++) {
		string[i] = towlower(string[i]);
	}
}