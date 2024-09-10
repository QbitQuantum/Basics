/* Attaches a signal handler for Ctrl+C or Ctrl+Break signals
 * Returns 1 if successful or -1 on error
 */
int cregtools_signal_attach(
     void (*signal_handler)( cregtools_signal_t ),
     libcerror_error_t **error )
{
	static char *function = "cregtools_signal_attach";

	if( signal_handler == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid signal handler.",
		 function );

		return( -1 );
	}
	cregtools_signal_signal_handler = signal_handler;

	if( SetConsoleCtrlHandler(
	     cregtools_signal_handler,
	     TRUE ) == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to attach signal handler.",
		 function );

		return( -1 );
	}
	if( SetConsoleCtrlHandler(
	     NULL,
	     FALSE ) == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to attach break signal.",
		 function );

		return( -1 );
	}
#if defined( _MSC_VER )
	cregtools_signal_initialize_memory_debug();
#endif

	SetErrorMode(
	 SEM_FAILCRITICALERRORS );

#if defined( LOCALE_SUPPORT )
	/* Allow subsequent threads to have their own locale.
	 * If the application is single threaded this call has
	 * no practical effect.
	 */
	_configthreadlocale(
	  _ENABLE_PER_THREAD_LOCALE );

	/* Set the current thread locale to the user default
	 * ANSI code page.
	 */
	setlocale(
	 LC_ALL,
	 "" );

	/* Set the the code page used by multibyte functions
	 * to use the same code page as the previous call to setlocale.
	 */
	_setmbcp(
	  _MB_CP_LOCALE );

#endif /* defined( LOCALE_SUPPORT ) */

	return( 1 );
}