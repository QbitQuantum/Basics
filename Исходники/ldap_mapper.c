/**
* Get certificate from LDAP-Server.
*/
static int ldap_get_certificate(const char *login) {
	LDAP *ldap_connection;
	int entries;
	LDAPMessage *res;
	LDAPMessage *entry;
	struct berval **bvals = NULL;
	BerElement *ber = NULL;
	char *name = NULL;
	char filter_str[100];
	char *attrs[2];
	int rv = LDAP_SUCCESS;
	void *bv_val;

	char uri[4096];
	char uribuf[4096];
	char *uris[LDAP_CONFIG_URI_MAX + 1];
	const char *p;
	int current_uri = 0, start_uri = 0;

	char *buffer;
	size_t buflen;

	uris[0] = NULL;

	attrs[0] = (char *)attribute;
	attrs[1] = NULL;

	DBG1("ldap_get_certificate(): begin login = %s", login);

	/* Put the login to the %s in Filterstring */
	snprintf(filter_str, sizeof(filter_str), filter, login);

	DBG1("ldap_get_certificate(): filter_str = %s", filter_str);

	/* parse and split URI config entry */
	buffer = uribuf;
	buflen = sizeof (uribuf);

	strncpy(uri, ldapURI, sizeof (uri)-1);

	/* Add a space separated list of URIs */
	/* TODO: no spaces in one URI allowed => URL-encoding? */
	if(strncmp(ldapURI,"",1))
		for (p = uri; p != NULL; )
		{
			char *q = strchr (p, ' ');
			if (q != NULL)
				*q = '\0';

			if( strlen(p) > 1 ) /* SAW: don't add spaces */
				rv = ldap_add_uri (uris, p, &buffer, &buflen);

			p = (q != NULL) ? ++q : NULL;

			if (rv)
				break;
		}
    /* set the default port if no port is given */
  	if (ldapport == 0)
    {
		if (ssl_on == SSL_LDAPS)
		{
		  ldapport = LDAPS_PORT;
		}
		else
		{
		  ldapport = LDAP_PORT;
		}
	}

	/* add ldaphost to uris if set, nevermind "uri" is set in config */
	if( strlen(ldaphost) > 1 )
	{
		/* No port specified in URI and non-default port specified */
		snprintf (uri, sizeof (uri), "%s%s:%d",
		       ssl_on == SSL_LDAPS ? "ldaps://" : "ldap://",
		       ldaphost, ldapport);
		ldap_add_uri (uris, uri, &buffer, &buflen);
	}

  	if (uris[0] == NULL)
    {
		DBG("ldap_get_certificate(): Nor URI or usable Host entry found");
		return(-1);
    }

	/* Attempt to connect to specified URI in order until do_open succeed */
	start_uri = current_uri;
	do
	{
		if(uris[current_uri] != NULL)
			DBG1("ldap_get_certificate(): try do_open for %s", uris[current_uri]);
		rv = do_open(&ldap_connection, uris[current_uri], ldapport, ssl_on);
		/* hot-fix, because in some circumstances an LDAP_SERVER_DOWN is returned */
		if (rv != LDAP_UNAVAILABLE && rv != LDAP_SERVER_DOWN)
			break;
		current_uri++;

		if (uris[current_uri] == NULL)
			current_uri = 0;
	}
	while (current_uri != start_uri);

	if( rv != LDAP_SUCCESS )
	{
		DBG("ldap_get_certificate(): do_open failed");
		return(-2);
	}

	/* TODO: (1) The problem: if an working uri is found it is used
    	     and if there is an (SSL-)error, no other one is tried
    	     (2) There is no session, so we don't know which LDAP_Server
    	     is the last with a successful connection. So we try the same
    	     server again. Perhaps create a state file/smem/etc. ?
    */

	rv = ldap_search_s(
				ldap_connection,
				base,
				sscope[scope],
				filter_str,
				attrs,
				0,
				&res);
	if ( rv != LDAP_SUCCESS ) {
		DBG1("ldap_search_s() failed: %s", ldap_err2string(rv));
		ldap_unbind_s(ldap_connection);
		return(-3);
	} else {
		entries = ldap_count_entries(ldap_connection, res);
		DBG1("ldap_get_certificate(): entries = %d", entries);

		if( entries > 1 ) {
			DBG("!  Warning, more than one entry found. Please choose \"filter\" and");
			DBG("!  \"attribute\" in ldap mapper config section of your config,");
			DBG("!  that only one entry with one attribute is matched");
			DBG("!  Maybe there is another problem in ldap with not unique user");
			DBG("!  entries in your LDAP server.");
		}

		/* Only first entry is used. "filter" and "attribute"
		 *  should be choosen, so that only one entry with
		 * one attribute is returned */
		if ( NULL == (entry = ldap_first_entry(ldap_connection, res))){
			DBG("ldap_first_entry() failed: %s");
			ldap_unbind_s(ldap_connection);
			return(-4);
		}

		/* Only first attribute is used. See comment above... */
		if ( NULL == (name = ldap_first_attribute(ldap_connection, res, &ber))){
			DBG("ldap_first_attribute() failed (rc=%d)");
			ldap_unbind_s(ldap_connection);
			return(-5);
		}
		DBG1("attribute name = %s", name);

		bvals = ldap_get_values_len(ldap_connection, entry, name);
		certcnt = ldap_count_values_len(bvals);

		DBG1("number of user certificates = %d", certcnt);

		ldap_x509 = malloc(sizeof(X509*) * certcnt );
		if (NULL == ldap_x509)
		{
			DBG("not enough memory");
			return(-7);
		}

		rv = 0;
		while(rv < certcnt )
		{
			/* SaW: not nifty, but otherwise gcc doesn't optimize */
			bv_val = &bvals[rv]->bv_val;
#ifdef HAVE_NSS
			{
				SECItem derdata;
				derdata.data = bv_val;
				derdata.len = bvals[rv]->bv_len;

				ldap_x509[rv] = CERT_NewTempCertificate(CERT_GetDefaultCertDB(),
					&derdata, NULL, 0, 1);
			}
#else
			ldap_x509[rv] = d2i_X509(NULL, ((const unsigned char **) bv_val), bvals[rv]->bv_len);
#endif
			if (NULL == ldap_x509[rv]) {
				DBG1("d2i_X509() failed for certificate %d", rv);
				free(ldap_x509);
#ifdef HAVE_NSS
				{
					for (rv=0; rv<certcnt; rv++)
						if (ldap_x509[rv])
							CERT_DestroyCertificate(ldap_x509[rv]);
				}
#endif
				certcnt=0;
				ldap_msgfree(res);
				ldap_unbind_s(ldap_connection);
				return(-6);
			}else {
				DBG1("d2i_X509(): success for certificate %d", rv);
			}
			rv++;
		}
		ldap_msgfree(res);
		/* TODO: this leads to a segfault, but the doc said ... */
		/* ldap_value_free_len(bvals); */
	}
	if ( 0 != ldap_unbind_s(ldap_connection)) {
		DBG("ldap_unbind_s() failed.");
		ldap_perror(ldap_connection, "ldap_unbind_s() failed.");
		return(-1);
	};

	DBG("ldap_get_certificate(): end");
	return 1;
}