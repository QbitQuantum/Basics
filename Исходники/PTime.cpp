char *ptime::print()
{
	snprintf(__dupa, 256, "%lu %lu", tv.tv_sec, tv.tv_usec);
	return __dupa;
}