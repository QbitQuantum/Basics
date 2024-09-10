*/	int OS_Set_Env(REBCHR *expr, int mode)
/*
**		Set a value from the environment.
**		Returns 0 for success and <0 for errors.
**
***********************************************************************/
{
#ifdef UNICODE
	return _wputenv(expr);
#else
	return putenv(expr);
#endif
}