static char *
get_entry(const char *key)
{
	static char buf[256];

	entry = NULL;
	if (SQLGetPrivateProfileString(odbc_server, key, "", buf, sizeof(buf), "odbc.ini") > 0)
		entry = buf;

	return entry;
}