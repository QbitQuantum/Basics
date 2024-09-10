char* RusW(const wchar_t* text) {
	CharToOemW(text, bufRus);
	return bufRus;
}