void _cdecl __CxxRestoreUnhandledExceptionFilter(void)
{
	SetUnhandledExceptionFilter(pOldExceptFilter);
}