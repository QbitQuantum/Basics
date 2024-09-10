/* 
	This function scans the array of controls and updates the Repl_Agmt's 
	Dirsync_Private if the dirsync control is found. 

*/
void windows_private_update_dirsync_control(const Repl_Agmt *ra,LDAPControl **controls )
{

	Dirsync_Private *dp;
    int foundDirsyncControl;
	int i;
	LDAPControl *dirsync = NULL;
	BerElement *ber = NULL;
	ber_int_t hasMoreData;
	ber_int_t maxAttributeCount;
	BerValue  *serverCookie = NULL;
#ifdef FOR_DEBUGGING
	int return_value = LDAP_SUCCESS;
#endif

	LDAPDebug0Args( LDAP_DEBUG_TRACE, "=> windows_private_update_dirsync_control\n" );

    PR_ASSERT(ra);

	dp = (Dirsync_Private *) agmt_get_priv(ra);
	PR_ASSERT (dp);
	
	if (NULL != controls )
	{
		foundDirsyncControl = 0;
		for ( i = 0; (( controls[i] != NULL ) && ( !foundDirsyncControl )); i++ ) {
			foundDirsyncControl = !strcmp( controls[i]->ldctl_oid, REPL_DIRSYNC_CONTROL_OID );
		}

		if ( !foundDirsyncControl )
		{
#ifdef FOR_DEBUGGING
			return_value = LDAP_CONTROL_NOT_FOUND;
#endif
			goto choke;
		}
		else if (!controls[i-1]->ldctl_value.bv_val) {
#ifdef FOR_DEBUGGING
			return_value = LDAP_CONTROL_NOT_FOUND;
#endif
			goto choke;
		}
		else
		{
			dirsync = slapi_dup_control( controls[i-1]);
		}

		ber = ber_init( &dirsync->ldctl_value ) ;

		if (ber_scanf( ber, "{iiO}", &hasMoreData, &maxAttributeCount, &serverCookie) == LBER_ERROR)
		{
#ifdef FOR_DEBUGGING
			return_value =  LDAP_CONTROL_NOT_FOUND;
#endif
			goto choke;
		}

		slapi_ch_free_string(&dp->dirsync_cookie);
		dp->dirsync_cookie = ( char* ) slapi_ch_malloc(serverCookie->bv_len + 1);

		memcpy(dp->dirsync_cookie, serverCookie->bv_val, serverCookie->bv_len);
		dp->dirsync_cookie_len = (int) serverCookie->bv_len; /* XXX shouldn't cast? */

		/* dp->dirsync_maxattributecount = maxAttributeCount; We don't need to keep this */
		dp->dirsync_cookie_has_more = hasMoreData;

choke:
		ber_bvfree(serverCookie);
		ber_free(ber,1);
		ldap_control_free(dirsync);
	}
	else
	{
#ifdef FOR_DEBUGGING
		return_value = LDAP_CONTROL_NOT_FOUND;
#endif
	}

#ifdef FOR_DEBUGGING
	LDAPDebug1Arg( LDAP_DEBUG_TRACE, "<= windows_private_update_dirsync_control: rc=%d\n", return_value);
#else
	LDAPDebug0Args( LDAP_DEBUG_TRACE, "<= windows_private_update_dirsync_control\n" );
#endif
}