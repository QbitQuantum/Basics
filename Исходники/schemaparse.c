int
parse_at(
	struct config_args_s *c,
	AttributeType	**sat,
	AttributeType	*prev )
{
	LDAPAttributeType *at;
	int		code;
	const char	*err;
	char *line = strchr( c->line, '(' );

	at = ldap_str2attributetype( line, &code, &err, LDAP_SCHEMA_ALLOW_ALL );
	if ( !at ) {
		snprintf( c->cr_msg, sizeof( c->cr_msg ), "%s: %s before %s",
			c->argv[0], ldap_scherr2str(code), err );
		Debug( LDAP_DEBUG_CONFIG|LDAP_DEBUG_NONE,
			"%s %s\n", c->log, c->cr_msg );
		at_usage();
		return 1;
	}

	if ( at->at_oid == NULL ) {
		snprintf( c->cr_msg, sizeof( c->cr_msg ), "%s: OID is missing",
			c->argv[0] );
		Debug( LDAP_DEBUG_CONFIG|LDAP_DEBUG_NONE,
			"%s %s\n", c->log, c->cr_msg );
		at_usage();
		code = 1;
		goto done;
	}

	/* operational attributes should be defined internally */
	if ( at->at_usage ) {
		snprintf( c->cr_msg, sizeof( c->cr_msg ), "%s: \"%s\" is operational",
			c->argv[0], at->at_oid );
		Debug( LDAP_DEBUG_CONFIG|LDAP_DEBUG_NONE,
			"%s %s\n", c->log, c->cr_msg );
		code = 1;
		goto done;
	}

	code = at_add( at, 1, sat, prev, &err);
	if ( code ) {
		snprintf( c->cr_msg, sizeof( c->cr_msg ), "%s: %s: \"%s\"",
			c->argv[0], scherr2str(code), err);
		Debug( LDAP_DEBUG_CONFIG|LDAP_DEBUG_NONE,
			"%s %s\n", c->log, c->cr_msg );
		code = 1;
		goto done;
	}

done:;
	if ( code ) {
		ldap_attributetype_free( at );

	} else {
		ldap_memfree( at );
	}

	return code;
}