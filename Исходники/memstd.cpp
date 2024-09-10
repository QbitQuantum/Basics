void *CStdMemAlloc::Expand( void *pMem, size_t nSize )
{
#ifdef _WIN32
	return _expand( pMem, nSize );
#elif _LINUX
	return realloc( pMem, nSize );
#endif
}