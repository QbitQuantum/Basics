static void FAIL( char const* funcname, int rc)
{
	fprintf( stderr, "%s() failed! (%d)\n", funcname, rc );
#ifdef _MSC_VER
    __debugbreak(); // give a chance to the debugger!
#endif // _MSC_VER
    abort();
}