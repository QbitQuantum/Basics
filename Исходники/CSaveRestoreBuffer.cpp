unsigned int CSaveRestoreBuffer::HashString( const char *pszToken )
{
	unsigned int	hash = 0;

	while( *pszToken )
		hash = _rotr( hash, 4 ) ^ *pszToken++;

	return hash;
}