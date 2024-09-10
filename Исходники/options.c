int
ldap_set_option(
	LDAP	*ld,
	int		option,
	LDAP_CONST void	*invalue)
{
	struct ldapoptions *lo;
	int *dbglvl = NULL;
	int rc = LDAP_OPT_ERROR;

	/* Get pointer to global option structure */
	lo = LDAP_INT_GLOBAL_OPT();
	if (lo == NULL)	{
		return LDAP_NO_MEMORY;
	}

	/*
	 * The architecture to turn on debugging has a chicken and egg
	 * problem. Thus, we introduce a fix here.
	 */

	if (option == LDAP_OPT_DEBUG_LEVEL) {
		dbglvl = (int *) invalue;
	}

	if( lo->ldo_valid != LDAP_INITIALIZED ) {
		ldap_int_initialize(lo, dbglvl);
		if ( lo->ldo_valid != LDAP_INITIALIZED )
			return LDAP_LOCAL_ERROR;
	}

	if(ld != NULL) {
		assert( LDAP_VALID( ld ) );

		if( !LDAP_VALID( ld ) ) {
			return LDAP_OPT_ERROR;
		}

		lo = &ld->ld_options;
	}

	LDAP_MUTEX_LOCK( &lo->ldo_mutex );

	switch ( option ) {

	/* options with boolean values */
	case LDAP_OPT_REFERRALS:
		if(invalue == LDAP_OPT_OFF) {
			LDAP_BOOL_CLR(lo, LDAP_BOOL_REFERRALS);
		} else {
			LDAP_BOOL_SET(lo, LDAP_BOOL_REFERRALS);
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_RESTART:
		if(invalue == LDAP_OPT_OFF) {
			LDAP_BOOL_CLR(lo, LDAP_BOOL_RESTART);
		} else {
			LDAP_BOOL_SET(lo, LDAP_BOOL_RESTART);
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_CONNECT_ASYNC:
		if(invalue == LDAP_OPT_OFF) {
			LDAP_BOOL_CLR(lo, LDAP_BOOL_CONNECT_ASYNC);
		} else {
			LDAP_BOOL_SET(lo, LDAP_BOOL_CONNECT_ASYNC);
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	/* options which can withstand invalue == NULL */
	case LDAP_OPT_SERVER_CONTROLS: {
			LDAPControl *const *controls =
				(LDAPControl *const *) invalue;

			if( lo->ldo_sctrls )
				ldap_controls_free( lo->ldo_sctrls );

			if( controls == NULL || *controls == NULL ) {
				lo->ldo_sctrls = NULL;
				rc = LDAP_OPT_SUCCESS;
				break;
			}
				
			lo->ldo_sctrls = ldap_controls_dup( controls );

			if(lo->ldo_sctrls == NULL) {
				/* memory allocation error ? */
				break;	/* LDAP_OPT_ERROR */
			}
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_CLIENT_CONTROLS: {
			LDAPControl *const *controls =
				(LDAPControl *const *) invalue;

			if( lo->ldo_cctrls )
				ldap_controls_free( lo->ldo_cctrls );

			if( controls == NULL || *controls == NULL ) {
				lo->ldo_cctrls = NULL;
				rc = LDAP_OPT_SUCCESS;
				break;
			}
				
			lo->ldo_cctrls = ldap_controls_dup( controls );

			if(lo->ldo_cctrls == NULL) {
				/* memory allocation error ? */
				break;	/* LDAP_OPT_ERROR */
			}
		}
		rc = LDAP_OPT_SUCCESS;
		break;


	case LDAP_OPT_HOST_NAME: {
			const char *host = (const char *) invalue;
			LDAPURLDesc *ludlist = NULL;
			rc = LDAP_OPT_SUCCESS;

			if(host != NULL) {
				rc = ldap_url_parsehosts( &ludlist, host,
					lo->ldo_defport ? lo->ldo_defport : LDAP_PORT );

			} else if(ld == NULL) {
				/*
				 * must want global default returned
				 * to initial condition.
				 */
				rc = ldap_url_parselist_ext(&ludlist, "ldap://localhost/", NULL,
					LDAP_PVT_URL_PARSE_NOEMPTY_HOST
					| LDAP_PVT_URL_PARSE_DEF_PORT );

			} else {
				/*
				 * must want the session default
				 *   updated to the current global default
				 */
				ludlist = ldap_url_duplist(
					ldap_int_global_options.ldo_defludp);
				if (ludlist == NULL)
					rc = LDAP_NO_MEMORY;
			}

			if (rc == LDAP_OPT_SUCCESS) {
				if (lo->ldo_defludp != NULL)
					ldap_free_urllist(lo->ldo_defludp);
				lo->ldo_defludp = ludlist;
			}
			break;
		}

	case LDAP_OPT_URI: {
			const char *urls = (const char *) invalue;
			LDAPURLDesc *ludlist = NULL;
			rc = LDAP_OPT_SUCCESS;

			if(urls != NULL) {
				rc = ldap_url_parselist_ext(&ludlist, urls, NULL,
					LDAP_PVT_URL_PARSE_NOEMPTY_HOST
					| LDAP_PVT_URL_PARSE_DEF_PORT );
			} else if(ld == NULL) {
				/*
				 * must want global default returned
				 * to initial condition.
				 */
				rc = ldap_url_parselist_ext(&ludlist, "ldap://localhost/", NULL,
					LDAP_PVT_URL_PARSE_NOEMPTY_HOST
					| LDAP_PVT_URL_PARSE_DEF_PORT );

			} else {
				/*
				 * must want the session default
				 *   updated to the current global default
				 */
				ludlist = ldap_url_duplist(
					ldap_int_global_options.ldo_defludp);
				if (ludlist == NULL)
					rc = LDAP_URL_ERR_MEM;
			}

			switch (rc) {
			case LDAP_URL_SUCCESS:		/* Success */
				rc = LDAP_SUCCESS;
				break;

			case LDAP_URL_ERR_MEM:		/* can't allocate memory space */
				rc = LDAP_NO_MEMORY;
				break;

			case LDAP_URL_ERR_PARAM:	/* parameter is bad */
			case LDAP_URL_ERR_BADSCHEME:	/* URL doesn't begin with "ldap[si]://" */
			case LDAP_URL_ERR_BADENCLOSURE:	/* URL is missing trailing ">" */
			case LDAP_URL_ERR_BADURL:	/* URL is bad */
			case LDAP_URL_ERR_BADHOST:	/* host port is bad */
			case LDAP_URL_ERR_BADATTRS:	/* bad (or missing) attributes */
			case LDAP_URL_ERR_BADSCOPE:	/* scope string is invalid (or missing) */
			case LDAP_URL_ERR_BADFILTER:	/* bad or missing filter */
			case LDAP_URL_ERR_BADEXTS:	/* bad or missing extensions */
				rc = LDAP_PARAM_ERROR;
				break;
			}

			if (rc == LDAP_SUCCESS) {
				if (lo->ldo_defludp != NULL)
					ldap_free_urllist(lo->ldo_defludp);
				lo->ldo_defludp = ludlist;
			}
			break;
		}

	case LDAP_OPT_DEFBASE: {
			const char *newbase = (const char *) invalue;
			char *defbase = NULL;

			if ( newbase != NULL ) {
				defbase = LDAP_STRDUP( newbase );
				if ( defbase == NULL ) {
					rc = LDAP_NO_MEMORY;
					break;
				}

			} else if ( ld != NULL ) {
				defbase = LDAP_STRDUP( ldap_int_global_options.ldo_defbase );
				if ( defbase == NULL ) {
					rc = LDAP_NO_MEMORY;
					break;
				}
			}
			
			if ( lo->ldo_defbase != NULL )
				LDAP_FREE( lo->ldo_defbase );
			lo->ldo_defbase = defbase;
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_DIAGNOSTIC_MESSAGE: {
			const char *err = (const char *) invalue;

			if(ld == NULL) {
				/* need a struct ldap */
				break;	/* LDAP_OPT_ERROR */
			}

			if( ld->ld_error ) {
				LDAP_FREE(ld->ld_error);
				ld->ld_error = NULL;
			}

			if ( err ) {
				ld->ld_error = LDAP_STRDUP(err);
			}
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_MATCHED_DN: {
			const char *matched = (const char *) invalue;

			if (ld == NULL) {
				/* need a struct ldap */
				break;	/* LDAP_OPT_ERROR */
			}

			if( ld->ld_matched ) {
				LDAP_FREE(ld->ld_matched);
				ld->ld_matched = NULL;
			}

			if ( matched ) {
				ld->ld_matched = LDAP_STRDUP( matched );
			}
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_REFERRAL_URLS: {
			char *const *referrals = (char *const *) invalue;
			
			if(ld == NULL) {
				/* need a struct ldap */
				break;	/* LDAP_OPT_ERROR */
			}

			if( ld->ld_referrals ) {
				LDAP_VFREE(ld->ld_referrals);
			}

			if ( referrals ) {
				ld->ld_referrals = ldap_value_dup(referrals);
			}
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	/* Only accessed from inside this function by ldap_set_rebind_proc() */
	case LDAP_OPT_REBIND_PROC: {
			lo->ldo_rebind_proc = (LDAP_REBIND_PROC *)invalue;		
		}
		rc = LDAP_OPT_SUCCESS;
		break;
	case LDAP_OPT_REBIND_PARAMS: {
			lo->ldo_rebind_params = (void *)invalue;		
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	/* Only accessed from inside this function by ldap_set_nextref_proc() */
	case LDAP_OPT_NEXTREF_PROC: {
			lo->ldo_nextref_proc = (LDAP_NEXTREF_PROC *)invalue;		
		}
		rc = LDAP_OPT_SUCCESS;
		break;
	case LDAP_OPT_NEXTREF_PARAMS: {
			lo->ldo_nextref_params = (void *)invalue;		
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	/* Only accessed from inside this function by ldap_set_urllist_proc() */
	case LDAP_OPT_URLLIST_PROC: {
			lo->ldo_urllist_proc = (LDAP_URLLIST_PROC *)invalue;		
		}
		rc = LDAP_OPT_SUCCESS;
		break;
	case LDAP_OPT_URLLIST_PARAMS: {
			lo->ldo_urllist_params = (void *)invalue;		
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	/* read-only options */
	case LDAP_OPT_API_INFO:
	case LDAP_OPT_DESC:
	case LDAP_OPT_SOCKBUF:
	case LDAP_OPT_API_FEATURE_INFO:
		break;	/* LDAP_OPT_ERROR */

	/* options which cannot withstand invalue == NULL */
	case LDAP_OPT_DEREF:
	case LDAP_OPT_SIZELIMIT:
	case LDAP_OPT_TIMELIMIT:
	case LDAP_OPT_PROTOCOL_VERSION:
	case LDAP_OPT_RESULT_CODE:
	case LDAP_OPT_DEBUG_LEVEL:
	case LDAP_OPT_TIMEOUT:
	case LDAP_OPT_NETWORK_TIMEOUT:
	case LDAP_OPT_CONNECT_CB:
	case LDAP_OPT_X_KEEPALIVE_IDLE:
	case LDAP_OPT_X_KEEPALIVE_PROBES :
	case LDAP_OPT_X_KEEPALIVE_INTERVAL :
		if(invalue == NULL) {
			/* no place to set from */
			LDAP_MUTEX_UNLOCK( &lo->ldo_mutex );
			return ( LDAP_OPT_ERROR );
		}
		break;

	default:
#ifdef HAVE_TLS
		if ( ldap_pvt_tls_set_option( ld, option, (void *)invalue ) == 0 ) {
			LDAP_MUTEX_UNLOCK( &lo->ldo_mutex );
			return ( LDAP_OPT_SUCCESS );
		}
#endif
#ifdef HAVE_CYRUS_SASL
		if ( ldap_int_sasl_set_option( ld, option, (void *)invalue ) == 0 ) {
			LDAP_MUTEX_UNLOCK( &lo->ldo_mutex );
			return ( LDAP_OPT_SUCCESS );
		}
#endif
#ifdef HAVE_GSSAPI
		if ( ldap_int_gssapi_set_option( ld, option, (void *)invalue ) == 0 ) {
			LDAP_MUTEX_UNLOCK( &lo->ldo_mutex );
			return ( LDAP_OPT_SUCCESS );
		}
#endif
		/* bad param */
		break;	/* LDAP_OPT_ERROR */
	}

	/* options which cannot withstand invalue == NULL */

	switch(option) {
	case LDAP_OPT_DEREF:
		/* FIXME: check value for protocol compliance? */
		lo->ldo_deref = * (const int *) invalue;
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_SIZELIMIT:
		/* FIXME: check value for protocol compliance? */
		lo->ldo_sizelimit = * (const int *) invalue;
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_TIMELIMIT:
		/* FIXME: check value for protocol compliance? */
		lo->ldo_timelimit = * (const int *) invalue;
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_TIMEOUT: {
			const struct timeval *tv = 
				(const struct timeval *) invalue;

			lo->ldo_tm_api = *tv;
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_NETWORK_TIMEOUT: {
			const struct timeval *tv = 
				(const struct timeval *) invalue;

			lo->ldo_tm_net = *tv;
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_PROTOCOL_VERSION: {
			int vers = * (const int *) invalue;
			if (vers < LDAP_VERSION_MIN || vers > LDAP_VERSION_MAX) {
				/* not supported */
				break;
			}
			lo->ldo_version = vers;
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_RESULT_CODE: {
			int err = * (const int *) invalue;

			if(ld == NULL) {
				/* need a struct ldap */
				break;
			}

			ld->ld_errno = err;
		}
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_DEBUG_LEVEL:
		lo->ldo_debug = * (const int *) invalue;
		rc = LDAP_OPT_SUCCESS;
		break;

	case LDAP_OPT_CONNECT_CB:
		{
			/* setting pushes the callback */
			ldaplist *ll;
			ll = LDAP_MALLOC( sizeof( *ll ));
			ll->ll_data = (void *)invalue;
			ll->ll_next = lo->ldo_conn_cbs;
			lo->ldo_conn_cbs = ll;
		}
		rc = LDAP_OPT_SUCCESS;
		break;
	case LDAP_OPT_X_KEEPALIVE_IDLE:
		lo->ldo_keepalive_idle = * (const int *) invalue;
		rc = LDAP_OPT_SUCCESS;
		break;
	case LDAP_OPT_X_KEEPALIVE_PROBES :
		lo->ldo_keepalive_probes = * (const int *) invalue;
		rc = LDAP_OPT_SUCCESS;
		break;
	case LDAP_OPT_X_KEEPALIVE_INTERVAL :
		lo->ldo_keepalive_interval = * (const int *) invalue;
		rc = LDAP_OPT_SUCCESS;
		break;
	
	}
	LDAP_MUTEX_UNLOCK( &lo->ldo_mutex );
	return ( rc );
}