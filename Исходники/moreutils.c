//===========================================================================
// helpers to remove excess info
int trim_address(char q[MAX_PATH], int is, int js)
{
	char *p; 
	p = (strchr(q, is));
	if (p != NULL)
	{
		p = _strrev(strrchr(_strrev(q), js));
		strcpy(q, (const char *)(p));
		return 1;
	}
	return 0;
}