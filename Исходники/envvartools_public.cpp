bool SetEnvironmentVariable( const char *pchVarName, const char *pchVarValue )
{
#if defined(_WIN32)
	return 0 != SetEnvironmentVariableA( pchVarName, pchVarValue );
#elif defined(POSIX)
	if( pchVarValue == NULL )
		return 0 == unsetenv( pchVarName );
	else
		return 0 == setenv( pchVarName, pchVarValue, 1 );
#else
#error "Unsupported Platform"
#endif
}