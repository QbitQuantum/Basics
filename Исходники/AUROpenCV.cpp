// windows has renamed the setenv func to _putenv_s
int setenv(const char *name, const char *value, int overwrite)
{
	if (!overwrite) 
	{
		// see if env var already exists
		size_t envsize = 0;
		int ret = getenv_s(&envsize, NULL, 0, name);
		// if exists, don't overwrite
		if (ret || envsize)
		{
			return ret;
		}
	}

	// set env var
	return _putenv_s(name, value);
}