static ngx_int_t ngx_http_auth_ldap_authenticate(ngx_http_request_t *r, ngx_http_auth_ldap_ctx_t *ctx,
        ngx_str_t *passwd, ngx_http_auth_ldap_loc_conf_t *conf) {

    LDAP *ld;
    LDAPMessage *searchResult;
    LDAPURLDesc *ludpp = conf->ludpp;
    int version = LDAP_VERSION3;
    struct berval bvalue;
    struct timeval timeOut = { 10, 0 };
    int reqcert = LDAP_OPT_X_TLS_ALLOW;

    int rc;
    ngx_uint_t i;
    ngx_ldap_require_t *value;
    ngx_ldap_userinfo *uinfo;

    ngx_flag_t pass = NGX_CONF_UNSET;

    char *dn;
    u_char *p, *filter;

    if (conf->ludpp == NULL) {
	return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    uinfo = ngx_http_auth_ldap_get_user_info(r);
    if (uinfo == NULL) {
	return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

	if (uinfo->password.len == 0)
	{
		return ngx_http_auth_ldap_set_realm(r, &conf->realm);
	}

    /// Set LDAP version to 3 and set connection timeout.
    ldap_set_option(NULL, LDAP_OPT_PROTOCOL_VERSION, &version);
    ldap_set_option(NULL, LDAP_OPT_NETWORK_TIMEOUT, &timeOut);

    rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_REQUIRE_CERT, &reqcert);
    if (rc != LDAP_OPT_SUCCESS) {
	ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "LDAP: unable to set require cert option: %s",
	        ldap_err2string(rc));
	return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "LDAP: URL: %s", conf->url.data);

    rc = ldap_initialize(&ld, (const char*) conf->url.data);
    if (rc != LDAP_SUCCESS) {
	ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "LDAP: Session initializing failed: %d, %s, (%s)", rc,
	        ldap_err2string(rc), (const char*) conf->url.data);
	return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "LDAP: Session initialized", NULL);

    /// Bind to the server
    rc = ldap_simple_bind_s(ld, (const char *) conf->bind_dn.data, (const char *) conf->bind_dn_passwd.data);
    if (rc != LDAP_SUCCESS) {
	ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "LDAP: ldap_simple_bind_s error: %d, %s", rc,
	        ldap_err2string(rc));
	ldap_unbind_s(ld);
	return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "LDAP: Bind successful", NULL);

    /// Create filter for search users by uid
    filter = ngx_pcalloc(
	    r->pool,
	    (ludpp->lud_filter != NULL ? ngx_strlen(ludpp->lud_filter) : ngx_strlen("(objectClass=*)")) + ngx_strlen("(&(=))")  + ngx_strlen(ludpp->lud_attrs[0])
               + uinfo->username.len + 1);
    p = ngx_sprintf(filter, "(&%s(%s=%s))", ludpp->lud_filter != NULL ? ludpp->lud_filter : "(objectClass=*)", ludpp->lud_attrs[0], uinfo->username.data);
    *p = 0;
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "LDAP: filter %s", (const char*) filter);

    /// Search the directory
    rc = ldap_search_ext_s(ld, ludpp->lud_dn, ludpp->lud_scope, (const char*) filter, NULL, 0, NULL, NULL, &timeOut, 0,
	    &searchResult);

    if (rc != LDAP_SUCCESS) {
	ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "LDAP: ldap_search_ext_s: %d, %s", rc, ldap_err2string(rc));
	ldap_msgfree(searchResult);
	ldap_unbind_s(ld);
	return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    if (ldap_count_entries(ld, searchResult) > 0) {
	dn = ldap_get_dn(ld, searchResult);
	if (dn != NULL) {
	    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "LDAP: result DN %s", dn);

	    /// Check require user
	    if (conf->require_user != NULL) {
		value = conf->require_user->elts;
		for (i = 0; i < conf->require_user->nelts; i++) {
		    ngx_str_t val;
		    if (value[i].lengths == NULL)
		    {
			val = value[i].value;
		    }
		    else
		    {
			if (ngx_http_script_run(r, &val, value[i].lengths->elts, 0,
				value[i].values->elts) == NULL)
			{
			    ldap_memfree(dn);
			    ldap_msgfree(searchResult);
			    ldap_unbind_s(ld);
			    return NGX_HTTP_INTERNAL_SERVER_ERROR;
			}
			val.data[val.len] = '\0';
		    }

		    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "LDAP: compare with: %s", val.data);
		    if (ngx_strncmp(val.data, dn, val.len) == 0) {
			pass = 1;
			if (conf->satisfy_all == 0) {
			    break;
			}
		    } else {
			if (conf->satisfy_all == 1) {
			    ldap_memfree(dn);
			    ldap_msgfree(searchResult);
			    ldap_unbind_s(ld);
			    return ngx_http_auth_ldap_set_realm(r, &conf->realm);
			}
		    }
		}
	    }

	    /// Check require group
	    if (conf->require_group != NULL) {
		if (conf->group_attribute_dn == 1) {
		    bvalue.bv_val = dn;
		    bvalue.bv_len = ngx_strlen(dn);
		} else {
		    bvalue.bv_val = (char*) uinfo->username.data;
		    bvalue.bv_len = uinfo->username.len;
		}

		value = conf->require_group->elts;

		for (i = 0; i < conf->require_group->nelts; i++) {
		    ngx_str_t val;
		    if (value[i].lengths == NULL)
		    {
			val = value[i].value;
		    }
		    else
		    {
			if (ngx_http_script_run(r, &val, value[i].lengths->elts, 0,
				value[i].values->elts) == NULL)
			{
			    ldap_memfree(dn);
			    ldap_msgfree(searchResult);
			    ldap_unbind_s(ld);
			    return NGX_HTTP_INTERNAL_SERVER_ERROR;
			}
			val.data[val.len] = '\0';
		    }

		    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "LDAP: group compare with: %s", val.data);

		    rc = ldap_compare_ext_s(ld, (const char*) val.data, (const char*) conf->group_attribute.data,
			    &bvalue, NULL, NULL);

		    /*if (rc != LDAP_COMPARE_TRUE && rc != LDAP_COMPARE_FALSE && rc != LDAP_NO_SUCH_ATTRIBUTE ) {
			ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "LDAP: ldap_search_ext_s: %d, %s", rc,
			        ldap_err2string(rc));
			ldap_memfree(dn);
			ldap_msgfree(searchResult);
			ldap_unbind_s(ld);
			return NGX_HTTP_INTERNAL_SERVER_ERROR;
		    }*/

		    if (rc == LDAP_COMPARE_TRUE) {
			pass = 1;
			if (conf->satisfy_all == 0) {
			    break;
			}
		    } else {
			if (conf->satisfy_all == 1) {
			    pass = 0;
			    break;
			}
		    }
		}
	    }

	    /// Check valid user
	    if ( pass != 0 || (conf->require_valid_user == 1 && conf->satisfy_all == 0 && pass == 0)) {
		/// Bind user to the server
		rc = ldap_simple_bind_s(ld, dn, (const char *) uinfo->password.data);
		if (rc != LDAP_SUCCESS) {
		    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "LDAP: ldap_simple_bind_s error: %d, %s", rc,
			    ldap_err2string(rc));
		    pass = 0;
		} else {
		    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "LDAP: User bind successful", NULL);
		    if (conf->require_valid_user == 1)
			pass = 1;
		}
	    }

	}
	ldap_memfree(dn);
    }

    ldap_msgfree(searchResult);
    ldap_unbind_s(ld);

    if (pass == 1) {
	return NGX_OK;
    }

    return ngx_http_auth_ldap_set_realm(r, &conf->realm);
}