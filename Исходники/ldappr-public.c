/*
* Function: prldap_import_connection().
* 
* Given the LDAP handle the connection parameters for the
* file descriptor are imported into NSPR layer.
* 
* Returns an LDAP API code (LDAP_SUCCESS) if all goes well.
*/
int LDAP_CALL
prldap_import_connection (LDAP *ld)
{
	int rc = LDAP_SUCCESS; /* optimistic */
	int shared = 1; /* Assume shared init */
	LBER_SOCKET orig_socket = -1;
	PRLDAPIOSessionArg *prsessp = NULL;
	PRLDAPIOSocketArg *prsockp = NULL;
	PRFileDesc *pr_socket = NULL;
	
	/* Check for invalid ld handle */
    	if ( ld == NULL) {
	    ldap_set_lderrno( ld, LDAP_PARAM_ERROR, NULL, NULL );
	    return( LDAP_PARAM_ERROR );
    	}
	
	/* Retrieve TCP socket's integer file descriptor */
    	if ( ldap_get_option( ld, LDAP_OPT_DESC, &orig_socket ) < 0 ) {
	    return( ldap_get_lderrno( ld, NULL, NULL ));
    	}
	
	/* Check for NSPR functions on ld */
   	if ( prldap_is_installed(ld)) {	/* Error : NSPR already Installed */
	    ldap_set_lderrno( ld, LDAP_LOCAL_ERROR, NULL, NULL );
	    return( LDAP_LOCAL_ERROR );
	}
	
    	if (LDAP_SUCCESS != (rc = prldap_install_routines(ld, shared))) {
	    return( rc );
    	}

	if (LDAP_SUCCESS != (rc = prldap_session_arg_from_ld( ld, &prsessp ))) {
	    return( rc );
	}
		
	/* Get NSPR Socket Arg  */
	if ( NULL == ( prsockp = prldap_socket_arg_alloc( prsessp ))) {
	    ldap_set_lderrno( ld, LDAP_NO_MEMORY, NULL, NULL );
	    return( LDAP_NO_MEMORY );
	}
	
	/* Import file descriptor of connection made via ldap_init() */
	if (NULL == (pr_socket = PR_ImportTCPSocket(orig_socket)) ) {
	    ldap_set_lderrno( ld, LDAP_LOCAL_ERROR, NULL, NULL );
	    return( LDAP_LOCAL_ERROR );
	}

	prsockp->prsock_prfd = pr_socket;

	/* Set Socket Arg in Extended I/O Layer */
	if ( ldap_set_option( ld, LDAP_X_OPT_SOCKETARG, prsockp) != 0 ) {
	    return( ldap_get_lderrno( ld, NULL, NULL ));
	}

	return( rc );
}