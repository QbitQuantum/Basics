int
setenv(const char *name, const char *value, int overwrite)
{
    int errcode = 0;

    if (!overwrite) {
	size_t envsize = 0;

#ifdef HAVE_GETENV_S
	errcode = getenv_s(&envsize, NULL, 0, name);
#else
	if (getenv(name) == NULL)
	    errcode = EINVAL;
#endif
	if (errcode || envsize)
	    return errcode;
    }
#ifdef HAVE__PUTENV_S
    return _putenv_s(name, value);
#else
    {
	size_t maxlen = strlen(name)+strlen(value)+2;
	char *keyval = (char *)malloc(maxlen);
	if (!keyval)
	    return ENOMEM;
	snprintf(keyval, maxlen, "%s=%s", name, value);
	return putenv(keyval);
    }
#endif
}