string::string(const uint64_t & ui64Number) {
	char tmp[32];
#ifdef _WIN32
	_ui64toa(ui64Number, tmp, 10);
	stralloc(tmp, strlen(tmp));
#else
	int iLen = sprintf(tmp, "%" PRIu64, ui64Number);
	stralloc(tmp, iLen);
#endif
}