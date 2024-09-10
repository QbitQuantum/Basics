void lutil_ReportShutdownComplete(  )
{
	if ( is_NT_Service )
	{
		/* stop sending SERVICE_STOP_PENDING messages to the Service Control Manager */
		ldap_pvt_thread_cond_signal( &stopped_event );
		ldap_pvt_thread_cond_destroy( &stopped_event );

		/* wait for the thread sending the SERVICE_STOP_PENDING messages to the Service Control Manager to die.
		 * if the wait fails then put ourselves to sleep for half the Service Control Manager update interval */
		if (ldap_pvt_thread_join( stop_status_tid, (void *) NULL ) == -1)
			ldap_pvt_thread_sleep( SCM_NOTIFICATION_INTERVAL / 2 );

		lutil_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		lutil_ServiceStatus.dwCheckPoint++;
		lutil_ServiceStatus.dwWaitHint = SCM_NOTIFICATION_INTERVAL;
		SetServiceStatus(hlutil_ServiceStatus, &lutil_ServiceStatus);
	}
}