int cb_ping_farm(cb_backend_instance *cb, cb_outgoing_conn * cnx,time_t end_time) {

	char 			*attrs[]	={"1.1",NULL};
	int 			rc;
    struct timeval          timeout;
	LDAP 			*ld;
	LDAPMessage		*result;
	time_t 			now;
	int 			secure;
	if (cb->max_idle_time <=0)	/* Heart-beat disabled */
		return LDAP_SUCCESS;

	if (cnx && (cnx->status != CB_CONNSTATUS_OK ))	/* Known problem */
		return LDAP_SERVER_DOWN;

	now = current_time();
	if (end_time && ((now <= end_time) || (end_time <0))) return LDAP_SUCCESS;

	secure = cb->pool->secure;
	if (cb->pool->starttls) {
		secure = 2;
	}
	ld=slapi_ldap_init(cb->pool->hostname,cb->pool->port,secure,0); 
	if (NULL == ld) {
		cb_update_failed_conn_cpt( cb );
		return LDAP_SERVER_DOWN;
	}

	timeout.tv_sec=cb->max_test_time;
	timeout.tv_usec=0;
	
	/* NOTE: This will fail if we implement the ability to disable
	   anonymous bind */
 	rc=ldap_search_ext_s(ld ,NULL,LDAP_SCOPE_BASE,"objectclass=*",attrs,1,NULL, 
		NULL, &timeout, 1,&result);
	if ( LDAP_SUCCESS != rc ) {
		slapi_ldap_unbind( ld );
		cb_update_failed_conn_cpt( cb );
		return LDAP_SERVER_DOWN; 
	}
	
	ldap_msgfree(result);
	slapi_ldap_unbind( ld );
	cb_reset_conn_cpt( cb );
	return LDAP_SUCCESS;
}