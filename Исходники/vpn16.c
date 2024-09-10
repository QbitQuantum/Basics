BOOL IsFile(char *name)
{
	HFILE h;
	if (name == NULL)
	{
		return FALSE;
	}

	h = _lopen(name, OF_READ);
	if (h == HFILE_ERROR)
	{
		return FALSE;
	}
	_lclose(h);

	return TRUE;
}