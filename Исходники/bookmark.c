static int GetBothPath(char *Str, char **Path1, char **Path2)
{
	char *Pos;
	int Ret;

	Ret = 1;
	*Path1 = Str + BMARK_MARK_LEN;

	Pos = _mbsstr(Str, BMARK_SEP);
	if(Pos != NULL)
	{
		Ret = 2;
		*Pos = NUL;
		*Path2 = Pos + BMARK_SEP_LEN;
	}
	return(Ret);
}