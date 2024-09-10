static int rt_rename(EIF_FILENAME from, EIF_FILENAME to)
{
#ifdef EIF_WINDOWS
	return _wrename(from, to);
#else
	return rename(from, to);
#endif
}