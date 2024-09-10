void geAssertDefault( void *exp, void *file, unsigned line )
{
#ifdef _DEBUG
	#if _MSC_VER > 1200
		_wassert(exp, file, line);
	#else
		_assert(exp, file, line);
	#endif
#endif
}