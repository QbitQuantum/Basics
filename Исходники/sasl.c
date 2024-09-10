ADS_STATUS ads_sasl_bind(ADS_STRUCT *ads)
{
	const char *attrs[] = {"supportedSASLMechanisms", NULL};
	char **values;
	ADS_STATUS status;
	int i, j;
	LDAPMessage *res;
	struct ads_saslwrap *wrap = &ads->ldap_wrap_data;

	/* get a list of supported SASL mechanisms */
	status = ads_do_search(ads, "", LDAP_SCOPE_BASE, "(objectclass=*)", attrs, &res);
	if (!ADS_ERR_OK(status)) return status;

	values = ldap_get_values(ads->ldap.ld, res, "supportedSASLMechanisms");

	if (ads->auth.flags & ADS_AUTH_SASL_SEAL) {
		wrap->wrap_type = ADS_SASLWRAP_TYPE_SEAL;
	} else if (ads->auth.flags & ADS_AUTH_SASL_SIGN) {
		wrap->wrap_type = ADS_SASLWRAP_TYPE_SIGN;
	} else {
		wrap->wrap_type = ADS_SASLWRAP_TYPE_PLAIN;
	}

	/* try our supported mechanisms in order */
	for (i=0;sasl_mechanisms[i].name;i++) {
		/* see if the server supports it */
		for (j=0;values && values[j];j++) {
			if (strcmp(values[j], sasl_mechanisms[i].name) == 0) {
				DEBUG(4,("Found SASL mechanism %s\n", values[j]));
retry:
				status = sasl_mechanisms[i].fn(ads);
				if (status.error_type == ENUM_ADS_ERROR_LDAP &&
				    status.err.rc == LDAP_STRONG_AUTH_REQUIRED &&
				    wrap->wrap_type == ADS_SASLWRAP_TYPE_PLAIN)
				{
					DEBUG(3,("SASL bin got LDAP_STRONG_AUTH_REQUIRED "
						 "retrying with signing enabled\n"));
					wrap->wrap_type = ADS_SASLWRAP_TYPE_SIGN;
					goto retry;
				}
				ldap_value_free(values);
				ldap_msgfree(res);
				return status;
			}
		}
	}

	ldap_value_free(values);
	ldap_msgfree(res);
	return ADS_ERROR(LDAP_AUTH_METHOD_NOT_SUPPORTED);
}