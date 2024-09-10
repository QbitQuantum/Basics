static int
CheckLDAPAuth(Port *port)
{
	char	   *passwd;
	char		server[128];
	char		basedn[128];
	char		prefix[128];
	char		suffix[128];
	LDAP	   *ldap;
	bool		ssl = false;
	int			r;
	int			ldapversion = LDAP_VERSION3;
	int			ldapport = LDAP_PORT;
	char		fulluser[NAMEDATALEN + 256 + 1];

	if (!port->auth_arg || port->auth_arg[0] == '\0')
	{
		ereport(LOG,
				(errmsg("LDAP configuration URL not specified")));
		return STATUS_ERROR;
	}

	/*
	 * Crack the LDAP url. We do a very trivial parse:
	 *
	 * ldap[s]://<server>[:<port>]/<basedn>[;prefix[;suffix]]
	 *
	 * This code originally used "%127s" for the suffix, but that doesn't
	 * work for embedded whitespace.  We know that tokens formed by
	 * hba.c won't include newlines, so we can use a "not newline" scanset
	 * instead.
	 */

	server[0] = '\0';
	basedn[0] = '\0';
	prefix[0] = '\0';
	suffix[0] = '\0';

	/* ldap, including port number */
	r = sscanf(port->auth_arg,
			   "ldap://%127[^:]:%d/%127[^;];%127[^;];%127[^\n]",
			   server, &ldapport, basedn, prefix, suffix);
	if (r < 3)
	{
		/* ldaps, including port number */
		r = sscanf(port->auth_arg,
				   "ldaps://%127[^:]:%d/%127[^;];%127[^;];%127[^\n]",
				   server, &ldapport, basedn, prefix, suffix);
		if (r >= 3)
			ssl = true;
	}
	if (r < 3)
	{
		/* ldap, no port number */
		r = sscanf(port->auth_arg,
				   "ldap://%127[^/]/%127[^;];%127[^;];%127[^\n]",
				   server, basedn, prefix, suffix);
	}
	if (r < 2)
	{
		/* ldaps, no port number */
		r = sscanf(port->auth_arg,
				   "ldaps://%127[^/]/%127[^;];%127[^;];%127[^\n]",
				   server, basedn, prefix, suffix);
		if (r >= 2)
			ssl = true;
	}
	if (r < 2)
	{
		ereport(LOG,
				(errmsg("invalid LDAP URL: \"%s\"",
						port->auth_arg)));
		return STATUS_ERROR;
	}

	sendAuthRequest(port, AUTH_REQ_PASSWORD);

	passwd = recv_password_packet(port);
	if (passwd == NULL)
		return STATUS_EOF;		/* client wouldn't send password */

	ldap = ldap_init(server, ldapport);
	if (!ldap)
	{
#ifndef WIN32
		ereport(LOG,
				(errmsg("could not initialize LDAP: error code %d",
						errno)));
#else
		ereport(LOG,
				(errmsg("could not initialize LDAP: error code %d",
						(int) LdapGetLastError())));
#endif
		return STATUS_ERROR;
	}

	if ((r = ldap_set_option(ldap, LDAP_OPT_PROTOCOL_VERSION, &ldapversion)) != LDAP_SUCCESS)
	{
		ldap_unbind(ldap);
		ereport(LOG,
		  (errmsg("could not set LDAP protocol version: error code %d", r)));
		return STATUS_ERROR;
	}

	if (ssl)
	{
#ifndef WIN32
		if ((r = ldap_start_tls_s(ldap, NULL, NULL)) != LDAP_SUCCESS)
#else
		static __ldap_start_tls_sA _ldap_start_tls_sA = NULL;

		if (_ldap_start_tls_sA == NULL)
		{
			/*
			 * Need to load this function dynamically because it does not
			 * exist on Windows 2000, and causes a load error for the whole
			 * exe if referenced.
			 */
			HANDLE		ldaphandle;

			ldaphandle = LoadLibrary("WLDAP32.DLL");
			if (ldaphandle == NULL)
			{
				/*
				 * should never happen since we import other files from
				 * wldap32, but check anyway
				 */
				ldap_unbind(ldap);
				ereport(LOG,
						(errmsg("could not load wldap32.dll")));
				return STATUS_ERROR;
			}
			_ldap_start_tls_sA = (__ldap_start_tls_sA) GetProcAddress(ldaphandle, "ldap_start_tls_sA");
			if (_ldap_start_tls_sA == NULL)
			{
				ldap_unbind(ldap);
				ereport(LOG,
						(errmsg("could not load function _ldap_start_tls_sA in wldap32.dll"),
						 errdetail("LDAP over SSL is not supported on this platform.")));
				return STATUS_ERROR;
			}

			/*
			 * Leak LDAP handle on purpose, because we need the library to
			 * stay open. This is ok because it will only ever be leaked once
			 * per process and is automatically cleaned up on process exit.
			 */
		}
		if ((r = _ldap_start_tls_sA(ldap, NULL, NULL, NULL, NULL)) != LDAP_SUCCESS)
#endif
		{
			ldap_unbind(ldap);
			ereport(LOG,
			 (errmsg("could not start LDAP TLS session: error code %d", r)));
			return STATUS_ERROR;
		}
	}

	snprintf(fulluser, sizeof(fulluser), "%s%s%s",
			 prefix, port->user_name, suffix);
	fulluser[sizeof(fulluser) - 1] = '\0';

	r = ldap_simple_bind_s(ldap, fulluser, passwd);
	ldap_unbind(ldap);

	if (r != LDAP_SUCCESS)
	{
		ereport(LOG,
				(errmsg("LDAP login failed for user \"%s\" on server \"%s\": error code %d",
						fulluser, server, r)));
		return STATUS_ERROR;
	}

	return STATUS_OK;
}