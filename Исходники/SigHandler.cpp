static FILE * OpenStackFile ()
{
	static char filename[ 1024 ];
	memset ( filename, 0, 1024 );
	char * it ( filename );
#ifdef WIN32
	static HMODULE module;
	GetModuleHandleExA ( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast< LPSTR >( filename ), &module );
	GetModuleFileNameA ( module, filename, 1023 );
#else
	static Dl_info info;
	dladdr ( reinterpret_cast<void*>( filename ), &info );
	memcpy ( filename, info.dli_fname, 1023 );
#endif
	it += strlen( filename );
	while( *it != '\\' && *it != '/' ) --it;
	memcpy ( ++it, "!stacktrace.txt", 16 );
	
	printf("Opening %s\n", filename );

	return fopen ( filename, "a" );
}