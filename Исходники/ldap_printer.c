/*
  find a printer given the name and the hostname
    Note that results "res" may be allocated on return so that the
    results can be used.  It should be freed using ads_msgfree.
*/
 ADS_STATUS ads_find_printer_on_server(ADS_STRUCT *ads, LDAPMessage **res,
				       const char *printer,
				       const char *servername)
{
	ADS_STATUS status;
	char *srv_dn, **srv_cn, *s = NULL;
	const char *attrs[] = {"*", "nTSecurityDescriptor", NULL};

	status = ads_find_machine_acct(ads, res, servername);
	if (!ADS_ERR_OK(status)) {
		DEBUG(1, ("ads_find_printer_on_server: cannot find host %s in ads\n",
			  servername));
		return status;
	}
	if (ads_count_replies(ads, *res) != 1) {
		ads_msgfree(ads, *res);
		*res = NULL;
		return ADS_ERROR(LDAP_NO_SUCH_OBJECT);
	}
	srv_dn = ldap_get_dn(ads->ldap.ld, *res);
	if (srv_dn == NULL) {
		ads_msgfree(ads, *res);
		*res = NULL;
		return ADS_ERROR(LDAP_NO_MEMORY);
	}
	srv_cn = ldap_explode_dn(srv_dn, 1);
	if (srv_cn == NULL) {
		ldap_memfree(srv_dn);
		ads_msgfree(ads, *res);
		*res = NULL;
		return ADS_ERROR(LDAP_INVALID_DN_SYNTAX);
	}
	ads_msgfree(ads, *res);
	*res = NULL;

	if (asprintf(&s, "(cn=%s-%s)", srv_cn[0], printer) == -1) {
		ldap_memfree(srv_dn);
		return ADS_ERROR(LDAP_NO_MEMORY);
	}
	status = ads_search(ads, res, s, attrs);

	ldap_memfree(srv_dn);
	ldap_value_free(srv_cn);
	SAFE_FREE(s);
	return status;	
}