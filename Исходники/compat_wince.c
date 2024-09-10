FILE *fdopen(int handle, const char *mode)
{
	WCHAR *wmode = to_wide_string(mode);
	FILE *result;

	if(wmode != NULL)
		result = _wfdopen((void *)handle, wmode);
	else
		result = NULL;
	free(wmode);
	return result;
}