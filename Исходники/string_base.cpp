uint32_t charLower(uint32_t param)
{
	if (param<128) {
		return ascii_tolower_table[param];
	}
#ifdef PFC_WINDOWS_DESKTOP_APP
	else if (param<0x10000) {
		return (unsigned)CharLowerW((WCHAR*)param);
	}
#endif
	else return param;
}