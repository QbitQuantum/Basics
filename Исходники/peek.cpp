static bool parse_integer(const char * str, T& val)
{
	char * p;
	long long ll;
#ifdef WIN32
	ll = _strtoi64(str, &p, 10);
#else
	ll = strtol(str, &p, 10);
#endif
	if (p == str || (*p && ! isspace((unsigned char)*p)))
		return false;
	val = static_cast<T>(ll);
	return true;
}