static WERROR nt_printer_dn_lookup(TALLOC_CTX *mem_ctx,
				   ADS_STRUCT *ads,
				   const char *printer,
				   char **pprinter_dn)
{
	char *printer_dn = NULL;
	char *srv_dn = NULL;
	char *srv_cn_0 = NULL;
	char *srv_cn_escaped = NULL;
	char *sharename_escaped = NULL;
	char *srv_dn_utf8 = NULL;
	char **srv_cn_utf8 = NULL;
	size_t converted_size;
	ADS_STATUS ads_status;
	LDAPMessage *res;
	WERROR result;
	bool ok;

	ads_status = ads_find_machine_acct(ads, &res, lp_netbios_name());
	if (!ADS_ERR_OK(ads_status)) {
		DEBUG(2, ("Failed to find machine account for %s\n",
			  lp_netbios_name()));
		result = WERR_NOT_FOUND;
		goto err_out;
	}

	/*
	 * We use ldap_get_dn here as we need the answer in utf8 to call
	 * ldap_explode_dn(). JRA.
	 */
	srv_dn_utf8 = ldap_get_dn((LDAP *)ads->ldap.ld, (LDAPMessage *)res);
	ads_msgfree(ads, res);
	if (srv_dn_utf8 == NULL) {
		result = WERR_SERVER_UNAVAILABLE;
		goto err_out;
	}

	srv_cn_utf8 = ldap_explode_dn(srv_dn_utf8, 1);
	if (srv_cn_utf8 == NULL) {
		ldap_memfree(srv_dn_utf8);
		result = WERR_SERVER_UNAVAILABLE;
		goto err_out;
	}

	/* Now convert to CH_UNIX. */
	ok = pull_utf8_talloc(mem_ctx, &srv_dn, srv_dn_utf8, &converted_size);
	ldap_memfree(srv_dn_utf8);
	if (!ok) {
		ldap_memfree(srv_cn_utf8);
		result = WERR_SERVER_UNAVAILABLE;
		goto err_out;
	}

	ok = pull_utf8_talloc(mem_ctx, &srv_cn_0, srv_cn_utf8[0], &converted_size);
	ldap_memfree(srv_cn_utf8);
	if (!ok) {
		result = WERR_SERVER_UNAVAILABLE;
		goto err_out;
	}

	srv_cn_escaped = escape_rdn_val_string_alloc(srv_cn_0);
	if (srv_cn_escaped == NULL) {
		result = WERR_SERVER_UNAVAILABLE;
		goto err_out;
	}

	sharename_escaped = escape_rdn_val_string_alloc(printer);
	if (sharename_escaped == NULL) {
		result = WERR_SERVER_UNAVAILABLE;
		goto err_out;
	}

	printer_dn = talloc_asprintf(mem_ctx,
				     "cn=%s-%s,%s",
				     srv_cn_escaped,
				     sharename_escaped,
				     srv_dn);
	if (printer_dn == NULL) {
		result = WERR_NOMEM;
		goto err_out;
	}

	*pprinter_dn = printer_dn;

	result = WERR_OK;
err_out:
	SAFE_FREE(sharename_escaped);
	SAFE_FREE(srv_cn_escaped);
	TALLOC_FREE(srv_cn_0);
	TALLOC_FREE(srv_dn);
	return result;
}