uint64 Str2UInt64(const char* str)
{
#ifdef __WINDOWS
	return str != NULL ? _strtoui64(str, NULL, 10) : 0;
#else
	return str != NULL ? strtol(str, NULL, 10) : 0;
#endif
}