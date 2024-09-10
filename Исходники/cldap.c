static int
cldap_result( LDAP *ld, int msgid, LDAPMessage **res,
	struct cldap_retinfo *crip, char *base )
{
    Sockbuf 		*sb;
    BerElement		ber;
    char		*logdn;
    int			ret, id, fromaddr, i;
    struct timeval	tv;

#if defined( SUN ) && defined( _REENTRANT )
    LOCK_LDAP(ld);
#endif	

    sb = &ld->ld_sb;
    fromaddr = -1;

    if ( crip->cri_try == 0 ) {
	crip->cri_maxtries = ld->ld_cldaptries * sb->sb_naddr;
	crip->cri_timeout = ld->ld_cldaptimeout;
	crip->cri_useaddr = 0;
	Debug( LDAP_DEBUG_TRACE, catgets(slapdcat, 1, 117, "cldap_result tries %1$d timeout %2$d\n"),
		ld->ld_cldaptries, ld->ld_cldaptimeout, 0 );
    }

    if ((tv.tv_sec = crip->cri_timeout / sb->sb_naddr) < 1 ) {
	tv.tv_sec = 1;
    }
    tv.tv_usec = 0;

    Debug( LDAP_DEBUG_TRACE,
	    catgets(slapdcat, 1, 118, "cldap_result waiting up to %d seconds for a response\n"),
	    tv.tv_sec, 0, 0 );
    ber_zero_init( &ber, 0 );
    set_ber_options( ld, &ber );

    if ( cldap_getmsg( ld, &tv, &ber ) == -1 ) {
	ret = ld->ld_errno;
	Debug( LDAP_DEBUG_TRACE, catgets(slapdcat, 1, 119, "cldap_getmsg returned -1 (%d)\n"),
		ret, 0, 0 );
    } else if ( ld->ld_errno == LDAP_TIMEOUT ) {
	Debug( LDAP_DEBUG_TRACE,
	    catgets(slapdcat, 1, 120, "cldap_result timed out\n"), 0, 0, 0 );
	/*
	 * It timed out; is it time to give up?
	 */
	if ( ++crip->cri_try >= crip->cri_maxtries ) {
	    ret = LDAP_TIMEOUT;
	    --crip->cri_try;
	} else {
	    if ( ++crip->cri_useaddr >= sb->sb_naddr ) {
		/*
		 * new round: reset address to first one and
		 * double the timeout
		 */
		crip->cri_useaddr = 0;
		crip->cri_timeout <<= 1;
	    }
	    ret = -1;
	}

    } else {
	/*
	 * Got a response.  It should look like:
	 * { msgid, logdn, { searchresponse...}}
	 */
	logdn = NULL;

	if ( ber_scanf( &ber, "ia", &id, &logdn ) == LBER_ERROR ) {
	    free( ber.ber_buf );	/* gack! */
	    ret = LDAP_DECODING_ERROR;
	    Debug( LDAP_DEBUG_TRACE,
		    catgets(slapdcat, 1, 121, "cldap_result: ber_scanf returned LBER_ERROR (%d)\n"),
		    ret, 0, 0 );
	} else if ( id != msgid ) {
	    free( ber.ber_buf );	/* gack! */
	    Debug( LDAP_DEBUG_TRACE,
		    catgets(slapdcat, 1, 122, "cldap_result: looking for msgid %1$d; got %2$d\n"),
		    msgid, id, 0 );
	    ret = -1;	/* ignore and keep looking */
	} else {
	    /*
	     * got a result: determine which server it came from
	     * decode into ldap message chain
	     */
	    for ( fromaddr = 0; fromaddr < sb->sb_naddr; ++fromaddr ) {
		    if ( memcmp( &((struct sockaddr_in *)
			    sb->sb_addrs[ fromaddr ])->sin_addr,
			    &((struct sockaddr_in *)sb->sb_fromaddr)->sin_addr,
			    sizeof( struct in_addr )) == 0 ) {
			break;
		    }
	    }
	    ret = cldap_parsemsg( ld, msgid, &ber, res, base );
	    free( ber.ber_buf );	/* gack! */
	    Debug( LDAP_DEBUG_TRACE,
		catgets(slapdcat, 1, 123, "cldap_result got result (%d)\n"), ret, 0, 0 );
	}

	if ( logdn != NULL ) {
		free( logdn );
	}
    }
    

    /*
     * If we are giving up (successfully or otherwise) then 
     * abandon any outstanding requests.
     */
    if ( ret != -1 ) {
	i = crip->cri_try;
	if ( i >= sb->sb_naddr ) {
	    i = sb->sb_naddr - 1;
	}

	for ( ; i >= 0; --i ) {
	    if ( i == fromaddr ) {
		continue;
	    }
	    sb->sb_useaddr = sb->sb_addrs[ i ];
	    Debug( LDAP_DEBUG_TRACE, catgets(slapdcat, 1, 124, "cldap_result abandoning id %1$d (to %2$s)\n"),
		msgid, inet_ntoa( ((struct sockaddr_in *)
		sb->sb_useaddr)->sin_addr ), 0 );
	    (void) ldap_abandon( ld, msgid );
	}
    }

#if defined( SUN ) && defined( _REENTRANT )
    UNLOCK_LDAP(ld);
#endif
    return( ld->ld_errno = ret );
}