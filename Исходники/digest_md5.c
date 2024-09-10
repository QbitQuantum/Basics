static int
sasl_digest_md5_bind_2(
	LDAP *ld,
	char *user_name,
	struct berval *cred,
	LDAPControl **serverctrls,
	LDAPControl **clientctrls,
	LDAPMessage *result,
	int *msgidp)
{
	struct berval	*challenge = NULL;
	struct berval	resp;
	int		errnum;
	char		*digest = NULL;
	int		err;

	if (ld == NULL || user_name == NULL || cred == NULL ||
	    cred->bv_val == NULL || result == NULL || msgidp == NULL)
		return (LDAP_PARAM_ERROR);

	if (ld->ld_version < LDAP_VERSION3)
		return (LDAP_PARAM_ERROR);

	err = ldap_result2error(ld, result, 0);
	if (err != LDAP_SASL_BIND_IN_PROGRESS)
		return (err);

	if ((err = ldap_parse_sasl_bind_result(ld, result, &challenge, 0))
			!= LDAP_SUCCESS)
		return (err);
	if (challenge == NULL)
		return (LDAP_NO_MEMORY);

	err = ldap_digest_md5_encode(challenge->bv_val,
			user_name, cred->bv_val, &digest);
	ber_bvfree(challenge);

	if (err == LDAP_SUCCESS) {
		resp.bv_val = digest;
		resp.bv_len = strlen(digest);
		LDAPDebug(LDAP_DEBUG_TRACE, "SASL reply: %s\n",
			digest, 0, 0);
		err = ldap_sasl_bind(ld, NULL, LDAP_SASL_DIGEST_MD5,
			&resp, serverctrls, clientctrls, msgidp);
		free(digest);
	}
	return (err);
}