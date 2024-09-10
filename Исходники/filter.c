static int
put_simple_filter(
	BerElement *ber,
	char *str )
{
	char		*s;
	char		*value;
	ber_tag_t	ftype;
	int		rc = -1;

	Debug( LDAP_DEBUG_TRACE, "put_simple_filter: \"%s\"\n",
		str, 0, 0 );

	str = LDAP_STRDUP( str );
	if( str == NULL ) return -1;

	if ( (s = strchr( str, '=' )) == NULL ) {
		goto done;
	}

	value = s + 1;
	*s-- = '\0';

	switch ( *s ) {
	case '<':
		ftype = LDAP_FILTER_LE;
		*s = '\0';
		break;

	case '>':
		ftype = LDAP_FILTER_GE;
		*s = '\0';
		break;

	case '~':
		ftype = LDAP_FILTER_APPROX;
		*s = '\0';
		break;

	case ':':
		/* RFC 4515 extensible filters are off the form:
		 *		type [:dn] [:rule] := value
		 * or	[:dn]:rule := value		
		 */
		ftype = LDAP_FILTER_EXT;
		*s = '\0';

		{
			char *dn = strchr( str, ':' );
			char *rule = NULL;

			if( dn != NULL ) {
				*dn++ = '\0';
				rule = strchr( dn, ':' );

				if( rule == NULL ) {
					/* one colon */
					if ( strcasecmp(dn, "dn") == 0 ) {
						/* must have attribute */
						if( !ldap_is_desc( str ) ) {
							goto done;
						}

						rule = "";

					} else {
					  rule = dn;
					  dn = NULL;
					}
				
				} else {
					/* two colons */
					*rule++ = '\0';

					if ( strcasecmp(dn, "dn") != 0 ) {
						/* must have "dn" */
						goto done;
					}
				}

			}

			if ( *str == '\0' && ( !rule || *rule == '\0' ) ) {
				/* must have either type or rule */
				goto done;
			}

			if ( *str != '\0' && !ldap_is_desc( str ) ) {
				goto done;
			}

			if ( rule && *rule != '\0' && !ldap_is_oid( rule ) ) {
				goto done;
			}

			rc = ber_printf( ber, "t{" /*"}"*/, ftype );

			if( rc != -1 && rule && *rule != '\0' ) {
				rc = ber_printf( ber, "ts", LDAP_FILTER_EXT_OID, rule );
			}

			if( rc != -1 && *str != '\0' ) {
				rc = ber_printf( ber, "ts", LDAP_FILTER_EXT_TYPE, str );
			}

			if( rc != -1 ) {
				ber_slen_t len = ldap_pvt_filter_value_unescape( value );

				if( len >= 0 ) {
					rc = ber_printf( ber, "to",
						LDAP_FILTER_EXT_VALUE, value, len );
				} else {
					rc = -1;
				}
			}

			if( rc != -1 && dn ) {
				rc = ber_printf( ber, "tb",
					LDAP_FILTER_EXT_DNATTRS, (ber_int_t) 1 );
			}

			if( rc != -1 ) { 
				rc = ber_printf( ber, /*"{"*/ "N}" );
			}
		}
		goto done;

	default:
		if( !ldap_is_desc( str ) ) {
			goto done;

		} else {
			char *nextstar = ldap_pvt_find_wildcard( value );

			if ( nextstar == NULL ) {
				goto done;

			} else if ( *nextstar == '\0' ) {
				ftype = LDAP_FILTER_EQUALITY;

			} else if ( strcmp( value, "*" ) == 0 ) {
				ftype = LDAP_FILTER_PRESENT;

			} else {
				rc = put_substring_filter( ber, str, value, nextstar );
				goto done;
			}
		} break;
	}

	if( !ldap_is_desc( str ) ) goto done;

	if ( ftype == LDAP_FILTER_PRESENT ) {
		rc = ber_printf( ber, "ts", ftype, str );

	} else {
		ber_slen_t len = ldap_pvt_filter_value_unescape( value );

		if( len >= 0 ) {
			rc = ber_printf( ber, "t{soN}",
				ftype, str, value, len );
		}
	}

done:
	if( rc != -1 ) rc = 0;
	LDAP_FREE( str );
	return rc;
}