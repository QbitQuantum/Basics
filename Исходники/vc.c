int
ldap_verify_credentials(LDAP *ld,
	struct berval	*cookie,
	LDAP_CONST char *dn,
	LDAP_CONST char *mechanism,
	struct berval	*cred,
    LDAPControl		**vcctrls,
	LDAPControl		**sctrls,
	LDAPControl		**cctrls,
	int				*msgidp)
{
	int rc;
	BerElement *ber;
	struct berval reqdata;

	assert(ld != NULL);
	assert(LDAP_VALID(ld));
	assert(msgidp != NULL);

	ber = ber_alloc_t(LBER_USE_DER);
	if (dn == NULL) dn = "";

	if (mechanism == LDAP_SASL_SIMPLE) {
		assert(!cookie);

		rc = ber_printf(ber, "{stO" /*"}"*/,
			dn, LDAP_AUTH_SIMPLE, cred);

	} else {
		if (!cred || BER_BVISNULL(cred)) {
			if (cookie) {
				rc = ber_printf(ber, "{tOst{sN}" /*"}"*/,
					LDAP_TAG_EXOP_VERIFY_CREDENTIALS_COOKIE, cookie,
					dn, LDAP_AUTH_SASL, mechanism);
			} else {
				rc = ber_printf(ber, "{st{sN}N" /*"}"*/,
					dn, LDAP_AUTH_SASL, mechanism);
			}
		} else {
			if (cookie) {
				rc = ber_printf(ber, "{tOst{sON}" /*"}"*/,
					LDAP_TAG_EXOP_VERIFY_CREDENTIALS_COOKIE, cookie,
					dn, LDAP_AUTH_SASL, mechanism, cred);
			} else {
				rc = ber_printf(ber, "{st{sON}" /*"}"*/,
					dn, LDAP_AUTH_SASL, mechanism, cred);
			}
		}
	}

	if (rc < 0) {
		rc = ld->ld_errno = LDAP_ENCODING_ERROR;
		goto done;
	}

	if (vcctrls && *vcctrls) {
		LDAPControl *const *c;

		rc = ber_printf(ber, "t{" /*"}"*/, LDAP_TAG_EXOP_VERIFY_CREDENTIALS_CONTROLS);

		for (c=vcctrls; *c; c++) {
			rc = ldap_pvt_put_control(*c, ber);
			if (rc != LDAP_SUCCESS) {
				rc = ld->ld_errno = LDAP_ENCODING_ERROR;
				goto done;
			}
		}

		rc = ber_printf(ber, /*"{{"*/ "}N}");

	} else {
		rc = ber_printf(ber, /*"{"*/ "N}");
	}

	if (rc < 0) {
		rc = ld->ld_errno = LDAP_ENCODING_ERROR;
		goto done;
	}


	rc = ber_flatten2(ber, &reqdata, 0);
	if (rc < 0) {
		rc = ld->ld_errno = LDAP_ENCODING_ERROR;
		goto done;
	}

	rc = ldap_extended_operation(ld, LDAP_EXOP_VERIFY_CREDENTIALS,
		&reqdata, sctrls, cctrls, msgidp);

done:
	ber_free(ber, 1);
	return rc;
}