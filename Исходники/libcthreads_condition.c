/* Broadcasts a condition
 * The of this function must be locked by the same mutex as used to wait
 * This is necessary for the WINAPI pre Vista (0x0600) implementation
 * Returns 1 if successful or -1 on error
 */
int libcthreads_condition_broadcast(
     libcthreads_condition_t *condition,
     libcerror_error_t **error )
{
	libcthreads_internal_condition_t *internal_condition = NULL;
	static char *function                                = "libcthreads_condition_broadcast";

#if defined( WINAPI ) && ( WINVER < 0x0600 )
	DWORD error_code                                     = 0;
	DWORD wait_status                                    = 0;
	BOOL result                                          = 1;
	int number_of_waiting_threads                        = 0;

#elif defined( HAVE_PTHREAD_H ) && !defined( WINAPI )
	int pthread_result                                   = 0;
#endif

	if( condition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid condition.",
		 function );

		return( -1 );
	}
	internal_condition = (libcthreads_internal_condition_t *) condition;

#if defined( WINAPI ) && ( WINVER >= 0x0600 )
	WakeAllConditionVariable(
	 &( internal_condition->condition_variable ) );

#elif defined( WINAPI )
	EnterCriticalSection(
	 &( internal_condition->wait_critical_section ) );

	number_of_waiting_threads = internal_condition->number_of_waiting_threads;

	if( number_of_waiting_threads > 0 )
	{
		internal_condition->signal_is_broadcast = 1;

		result = ReleaseSemaphore(
		          internal_condition->signal_semaphore_handle,
		          number_of_waiting_threads,
		          0 );

		if( result == 0 )
		{
			error_code = GetLastError();

			internal_condition->signal_is_broadcast = 0;
		}
	}
	LeaveCriticalSection(
	 &( internal_condition->wait_critical_section ) );

	if( result == 0 )
	{
		libcerror_system_set_error(
		 error,
		 error_code,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release signal semaphore handle.",
		 function );

		return( -1 );
	}
	if( number_of_waiting_threads > 0 )
	{
		wait_status = WaitForSingleObject(
		               internal_condition->signal_event_handle,
		               INFINITE );

		if( wait_status == WAIT_FAILED )
		{
			error_code = GetLastError();

			internal_condition->signal_is_broadcast = 0;

			libcerror_system_set_error(
			 error,
			 error_code,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: wait for no read event handle failed.",
			 function );

			return( -1 );
		}
		internal_condition->signal_is_broadcast = 0;
	}

#elif defined( HAVE_PTHREAD_H )
	pthread_result = pthread_cond_broadcast(
	                  &( internal_condition->condition ) );

	if( pthread_result != 0 )
	{
		libcerror_system_set_error(
		 error,
		 pthread_result,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to broadcast condition.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}