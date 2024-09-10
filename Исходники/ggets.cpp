// Same with strchr
char *FindCharInString( const char *string, int c )
{	
	// This *should* work OK even with UTF-8, since we're only searching for
	// '\n' in practice. Careful if you try to use this for anything other
	// than ASCII characters. 
	return (char*)_mbschr( (const unsigned char *)string, c );
}