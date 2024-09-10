int ldap_compare_ext_s(LDAP *ld, char *dn, char *attr, struct berval *bvalue,
					   LDAPControl ** serverctrls, LDAPControl **clientctrls)
{
	int		msgid, retcode = LDAP_SUCCESS;
	LDAPMessage	*res;

	if ( (retcode = ldap_compare_ext( ld, dn, attr, bvalue, serverctrls, clientctrls, &msgid )) != LDAP_SUCCESS )
		return( retcode );

	if ( ldap_result( ld, msgid, 1, (struct timeval *) NULL, &res ) == -1 )
		return( ld->ld_errno );

#ifdef _REENTRANT
	LOCK_LDAP(ld);
#endif
	retcode = ldap_parse_result( ld, res,  &ld->ld_errno, &ld->ld_matched, &ld->ld_error,
								 &ld->ld_referrals, &ld->ld_ret_ctrls, 1);
	if (retcode == LDAP_SUCCESS)
		retcode = ld->ld_errno;
#ifdef _REENTRANT
	UNLOCK_LDAP(ld);
#endif
	return (retcode);
}