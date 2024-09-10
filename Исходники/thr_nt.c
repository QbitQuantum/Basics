int 
ldap_pvt_thread_cond_wait( ldap_pvt_thread_cond_t *cond, 
	ldap_pvt_thread_mutex_t *mutex )
{
	SignalObjectAndWait( *mutex, *cond, INFINITE, FALSE );
	WaitForSingleObject( *mutex, INFINITE );
	return( 0 );
}