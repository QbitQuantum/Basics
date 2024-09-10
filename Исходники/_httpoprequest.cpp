char * os_strtok_r(char *str, const char *delim, char ** savestate)
{
#if LL_WINDOWS
	return strtok_s(str, delim, savestate);
#else
	return strtok_r(str, delim, savestate);
#endif
}