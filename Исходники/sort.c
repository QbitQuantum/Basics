int
ldap_sort_entries(
    LDAP	*ld,
    LDAPMessage	**chain,
    LDAP_CONST char	*attr,		/* NULL => sort by DN */
    int		(*cmp) (LDAP_CONST  char *, LDAP_CONST char *)
)
{
	int			i, count = 0;
	struct entrything	*et;
	LDAPMessage		*e, *ehead = NULL, *etail = NULL;
	LDAPMessage		*ohead = NULL, *otail = NULL;
	LDAPMessage		**ep;

	assert( ld != NULL );

	/* Separate entries from non-entries */
	for ( e = *chain; e; e=e->lm_chain ) {
		if ( e->lm_msgtype == LDAP_RES_SEARCH_ENTRY ) {
			count++;
			if ( !ehead ) ehead = e;
			if ( etail ) etail->lm_chain = e;
			etail = e;
		} else {
			if ( !ohead ) ohead = e;
			if ( otail ) otail->lm_chain = e;
			otail = e;
		}
	}

	if ( count < 2 ) {
		/* zero or one entries -- already sorted! */
		if ( ehead ) {
			etail->lm_chain = ohead;
			*chain = ehead;
		} else {
			*chain = ohead;
		}
		return 0;
	}

	if ( (et = (struct entrything *) LDAP_MALLOC( count *
	    sizeof(struct entrything) )) == NULL ) {
		ld->ld_errno = LDAP_NO_MEMORY;
		return( -1 );
	}

	e = ehead;
	for ( i = 0; i < count; i++ ) {
		et[i].et_cmp_fn = cmp;
		et[i].et_msg = e;
		if ( attr == NULL ) {
			char	*dn;

			dn = ldap_get_dn( ld, e );
			et[i].et_vals = ldap_explode_dn( dn, 1 );
			LDAP_FREE( dn );
		} else {
			et[i].et_vals = ldap_get_values( ld, e, attr );
		}

		e = e->lm_chain;
	}

	qsort( et, count, sizeof(struct entrything), et_cmp );

	ep = chain;
	for ( i = 0; i < count; i++ ) {
		*ep = et[i].et_msg;
		ep = &(*ep)->lm_chain;

		LDAP_VFREE( et[i].et_vals );
	}
	*ep = ohead;
	(*chain)->lm_chain_tail = otail ? otail : etail;

	LDAP_FREE( (char *) et );

	return( 0 );
}