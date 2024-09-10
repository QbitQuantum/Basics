char *StrTok_us( char *str, const char *delim )
{
	static char *last=NULL;
	char* found;
	
	if( str == NULL )
	{
		str = last;
	}
	
	found = StrPBrk( str, delim );

	if( found == NULL )
	{
		last = NULL;
		return NULL;
	}
	else
	{
		last = found + 1;
		*found = STREND;
		return str;
	}
}