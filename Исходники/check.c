int	check_challenge(scep_t *scep) {
	X509_REQ	*req;
	char		*challenge, *dn;
	X509_NAME	*subject;
	LDAP		*ldap = NULL;

	/* the clientreq field in the scep structure contains the 	*/
	/* request, even for getcertinitial messages where the request	*/
	/* does not contain the data originally sent with the request	*/
	req = scep->clientreq;
	if (debug)
		BIO_printf(bio_err, "%s:%d: checking challenge password in "
			"request %p\n", __FILE__, __LINE__, req);

	/* check whether is at all challenge password in the request	*/
	if (NULL == (challenge = get_challenge(scep))) {
		BIO_printf(bio_err, "%s:%d: no challenge password found\n",
			__FILE__, __LINE__);
		goto err;
	}
	if (debug)
		BIO_printf(bio_err, "%s:%d: challenge Password '%s'\n",
			__FILE__, __LINE__, challenge);

	/* a challenge password of zero length is not authenticable	*/
	if (strlen(challenge) == 0) {
		if (debug)
			BIO_printf(bio_err, "%s:%d: zero challenge\n",
				__FILE__, __LINE__);
		goto err;
	}

	/* get the client distinguished name				*/
	subject = X509_REQ_get_subject_name(req);
	if (debug) {
		char	name[1024];
		X509_NAME_oneline(subject, name, sizeof(name));
		BIO_printf(bio_err, "%s:%d: requestor: %s\n", __FILE__,
			__LINE__, name);
	}

	/* map to a suitable LDAP distinguished name			*/
	dn = x509_to_ldap(scep, subject);
	if (debug)
		BIO_printf(bio_err, "%s:%d: mapped requestor to LDAP DN '%s'\n",
			__FILE__, __LINE__, dn);

	/* connect to the ldap directory				*/
	ldap = ldap_open(scep->l.ldaphost, scep->l.ldapport);
	if (ldap == NULL) {
		BIO_printf(bio_err, "%s:%d: cannot connect to %s:%d\n",
			__FILE__, __LINE__, scep->l.ldaphost, scep->l.ldapport);
		goto err;
	}

	/* authenticate the LDAP DN in the directory			*/
	if (ldap_simple_bind_s(ldap, dn, challenge) != LDAP_SUCCESS && 0) {
		BIO_printf(bio_err, "%s:%d: cannot ldap_simple_bind_s\n",
			__FILE__, __LINE__);
		syslog(LOG_ERR, "LDAP authentication for %s failed", dn);
		goto err;
	}

	/* clean up any ldap connection					*/
	ldap_unbind(ldap);

	/* if we get to this point, then authentication was successful	*/
	BIO_printf(bio_err, "%s:%d: check successful\n", __FILE__, __LINE__);
	return 0;
err:
	/* XXX should do some cleanup here to prevent memory leaks	*/
	if (ldap) ldap_unbind(ldap);
	ERR_print_errors(bio_err);
	return -1;
}