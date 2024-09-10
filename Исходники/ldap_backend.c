static void
ldapconnect(void)
{
    int rc;

/* On Windows ldap_start_tls_s is available starting from Windows XP, 
 * so we need to bind at run-time with the function entry point
 */
#ifdef _SQUID_MSWIN_
    if (use_tls) {

	HMODULE WLDAP32Handle;

	WLDAP32Handle = GetModuleHandle("wldap32");
	if ((Win32_ldap_start_tls_s = (PFldap_start_tls_s) GetProcAddress(WLDAP32Handle, LDAP_START_TLS_S)) == NULL) {
	    fprintf(stderr, PROGRAM_NAME ": ERROR: TLS (-Z) not supported on this platform.\n");
	    exit(1);
	}
    }
#endif

    if (ld == NULL) {
#if HAS_URI_SUPPORT
	if (strstr(ldapServer, "://") != NULL) {
	    rc = ldap_initialize(&ld, ldapServer);
	    if (rc != LDAP_SUCCESS) {
		fprintf(stderr, "\nUnable to connect to LDAPURI:%s\n", ldapServer);
	    }
	} else
#endif
#if NETSCAPE_SSL
	if (sslpath) {
	    if (!sslinit && (ldapssl_client_init(sslpath, NULL) != LDAP_SUCCESS)) {
		fprintf(stderr, "\nUnable to initialise SSL with cert path %s\n",
		    sslpath);
		exit(1);
	    } else {
		sslinit++;
	    }
	    if ((ld = ldapssl_init(ldapServer, port, 1)) == NULL) {
		fprintf(stderr, "\nUnable to connect to SSL LDAP server: %s port:%d\n",
		    ldapServer, port);
		exit(1);
	    }
	} else
#endif
	if ((ld = ldap_init(ldapServer, port)) == NULL) {
	    fprintf(stderr, "\nUnable to connect to LDAP server:%s port:%d\n", ldapServer, port);
	}
	if (connect_timeout)
	    squid_ldap_set_connect_timeout(connect_timeout);

#ifdef LDAP_VERSION3
	if (version == -1) {
	    version = LDAP_VERSION2;
	}
	if (ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version)
	    != LDAP_SUCCESS) {
	    fprintf(stderr, "Could not set LDAP_OPT_PROTOCOL_VERSION %d\n",
		version);
	    ldap_unbind(ld);
	    ld = NULL;
	}
	if (use_tls) {
#ifdef LDAP_OPT_X_TLS
	    if ((version == LDAP_VERSION3) && (ldap_start_tls_s(ld, NULL, NULL) == LDAP_SUCCESS)) {
		fprintf(stderr, "Could not Activate TLS connection\n");
		ldap_unbind(ld);
		ld = NULL;
	    }
#else
	    fprintf(stderr, "TLS not supported with your LDAP library\n");
	    ldap_unbind(ld);
	    ld = NULL;
#endif
	}
#endif
	squid_ldap_set_timelimit(timelimit);
	squid_ldap_set_referrals(!noreferrals);
	squid_ldap_set_aliasderef(aliasderef);
	if (binddn && bindpasswd && *binddn && *bindpasswd) {
	    rc = ldap_simple_bind_s(ld, binddn, bindpasswd);
	    if (rc != LDAP_SUCCESS) {
		fprintf(stderr, PROGRAM_NAME " WARNING, could not bind to binddn '%s'\n", ldap_err2string(rc));
		ldap_unbind(ld);
		ld = NULL;
	    }
	}
	if (debug)
	    fprintf(stderr, "Connected OK\n");
    }
}