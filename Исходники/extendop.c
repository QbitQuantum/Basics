/*
 * ldap_extended_operation_s - perform an arbitrary ldapv3 extended operation.
 * the oid and data of the extended operation are supplied. LDAP_SUCCESS
 * is returned upon success, the ldap error code otherwise.
 *
 * Example:
 *	struct berval	exdata, exretval;
 *	char		*exoid;
 *	int		rc;
 *	... fill in oid and data ...
 *	rc = ldap_extended_operation_s( ld, exoid, &exdata, &exretval );
 */
int
LDAP_CALL
ldap_extended_operation_s(
    LDAP		*ld,
    const char		*requestoid,
    const struct berval	*requestdata,
    LDAPControl		**serverctrls,
    LDAPControl		**clientctrls,
    char		**retoidp,
    struct berval	**retdatap
)
{
	int		err, msgid;
	LDAPMessage	*result;

	if (( err = ldap_extended_operation( ld, requestoid, requestdata,
	    serverctrls, clientctrls, &msgid )) != LDAP_SUCCESS ) {
		return( err );
	}

	if ( ldap_result( ld, msgid, 1, (struct timeval *) 0, &result )
	    == -1 ) {
		return( LDAP_GET_LDERRNO( ld, NULL, NULL ) );
	}

	if (( err = ldap_parse_extended_result( ld, result, retoidp, retdatap,
		0 )) != LDAP_SUCCESS ) {
	    ldap_msgfree( result );
	    return( err );
	}

	return( ldap_result2error( ld, result, 1 ) );
}