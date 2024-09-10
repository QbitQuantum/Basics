void BGBCC_DieFatal()
{
//#ifdef WIN32
#if 0
	ULONG_PTR args[8];
	RaiseException(BGBCC_EXCEPTION, EXCEPTION_NONCONTINUABLE,
		1, args);
#else
	*(int *)-1=-1;
#endif
}