handler_t auth_ldap_init(server *srv, mod_auth_plugin_config *s) {
#ifdef USE_LDAP
	int ret;
#if 0
	if (s->auth_ldap_basedn->used == 0) {
		log_error_write(srv, __FILE__, __LINE__, "s", "ldap: auth.backend.ldap.base-dn has to be set");

		return HANDLER_ERROR;
	}
#endif

	if (s->auth_ldap_hostname->used) {
		/* free old context */
		if (NULL != s->ldap) ldap_unbind_s(s->ldap);

		if (NULL == (s->ldap = ldap_init(s->auth_ldap_hostname->ptr, LDAP_PORT))) {
			log_error_write(srv, __FILE__, __LINE__, "ss", "ldap ...", strerror(errno));

			return HANDLER_ERROR;
		}

		ret = LDAP_VERSION3;
		if (LDAP_OPT_SUCCESS != (ret = ldap_set_option(s->ldap, LDAP_OPT_PROTOCOL_VERSION, &ret))) {
			log_error_write(srv, __FILE__, __LINE__, "ss", "ldap:", ldap_err2string(ret));

			return HANDLER_ERROR;
		}

		if (s->auth_ldap_starttls) {
			/* if no CA file is given, it is ok, as we will use encryption
				* if the server requires a CAfile it will tell us */
			if (!buffer_is_empty(s->auth_ldap_cafile)) {
				if (LDAP_OPT_SUCCESS != (ret = ldap_set_option(NULL, LDAP_OPT_X_TLS_CACERTFILE,
								s->auth_ldap_cafile->ptr))) {
					log_error_write(srv, __FILE__, __LINE__, "ss",
							"Loading CA certificate failed:", ldap_err2string(ret));

					return HANDLER_ERROR;
				}
			}

			if (LDAP_OPT_SUCCESS != (ret = ldap_start_tls_s(s->ldap, NULL,  NULL))) {
				log_error_write(srv, __FILE__, __LINE__, "ss", "ldap startTLS failed:", ldap_err2string(ret));

				return HANDLER_ERROR;
			}
		}


		/* 1. */
		if (s->auth_ldap_binddn->used) {
			if (LDAP_SUCCESS != (ret = ldap_simple_bind_s(s->ldap, s->auth_ldap_binddn->ptr, s->auth_ldap_bindpw->ptr))) {
				log_error_write(srv, __FILE__, __LINE__, "ss", "ldap:", ldap_err2string(ret));

				return HANDLER_ERROR;
			}
		} else {
			if (LDAP_SUCCESS != (ret = ldap_simple_bind_s(s->ldap, NULL, NULL))) {
				log_error_write(srv, __FILE__, __LINE__, "ss", "ldap:", ldap_err2string(ret));

				return HANDLER_ERROR;
			}
		}
	}
	return HANDLER_GO_ON;
#else
	UNUSED(s);
	log_error_write(srv, __FILE__, __LINE__, "s", "no ldap support available");
	return HANDLER_ERROR;
#endif
}