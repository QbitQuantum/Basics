BOOL IsWordDiv(int c)
{
	return (wmemchr(Opt.WordDiv, c, Opt.WordDivLen)!=NULL);
}