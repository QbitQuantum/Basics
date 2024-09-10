static int path_wstat(const wstring& path_wc, path_stat_t *st)
{
#if defined(_MSC_VER) || defined(__MINGW64__)
	return _wstat64(path_wc.c_str(), st);
#elif defined(__MINGW32__)
	return _wstati64(path_wc.c_str(), st);
#else
	return _wstat(path_wc.c_str(), st);
#endif
}