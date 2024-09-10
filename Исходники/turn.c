int
ldap_turn(
	LDAP *ld,
	int mutual,
	LDAP_CONST char* identifier,
	LDAPControl **sctrls,
	LDAPControl **cctrls,
	int *msgidp )
{
#ifdef LDAP_EXOP_X_TURN
	BerElement *turnvalber = NULL;
	struct berval *turnvalp = NULL;
	int rc;

	turnvalber = ber_alloc_t( LBER_USE_DER );
	if( mutual ) {
		ber_printf( turnvalber, "{bs}", mutual, identifier );
	} else {
		ber_printf( turnvalber, "{s}", identifier );
	}
	ber_flatten( turnvalber, &turnvalp );

	rc = ldap_extended_operation( ld, LDAP_EXOP_X_TURN,
			turnvalp, sctrls, cctrls, msgidp );
	ber_free( turnvalber, 1 );
	return rc;
#else
	return LDAP_CONTROL_NOT_FOUND;
#endif
}